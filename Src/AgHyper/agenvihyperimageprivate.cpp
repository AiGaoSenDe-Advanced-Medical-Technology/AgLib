#include "agenvihyperimageprivate.h"

QVector<QString> AEnviHyperImagePrivate::keyList = QVector<QString>() << "lines" << "samples" << "bands" << "header offset" << "file type" << "data type" << "interleave" << "sensor type" << "wavelength units" << "binning" << "wavelength";

AEnviHyperImagePrivate::AEnviHyperImagePrivate(AEnviHyperImage *qq) :
    AAbstractHyperImagePrivate(qq)
{
    unload();
}

AEnviHyperImagePrivate::~AEnviHyperImagePrivate()
{
    
}

void AEnviHyperImagePrivate::unload()
{
    AAbstractHyperImagePrivate::unload();
    headerOffset = 0;
    interLeave = AEnviHyperImage::InterLeave::Unknown;
    binning = QPair<int, int>(1, 1);
}

bool AEnviHyperImagePrivate::load(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString hdrFileName = QString("%1/%2.hdr").arg(fileInfo.absolutePath()).arg(fileInfo.completeBaseName());
    if (!loadHdr(hdrFileName))
    {
        unload();
        return false;
    }
    QString rawFileName = QString("%1/%2.raw").arg(fileInfo.absolutePath()).arg(fileInfo.completeBaseName());
    QFile file(rawFileName);
    if (!checkRawAvailibility(file))
    {
        unload();
        return false;
    }
    file.close();
    isLoaded = true;
    fileFullPath = fileInfo.absolutePath();
    fileCompleteBaseName = fileInfo.completeBaseName();
    return true;
}

arma::vec AEnviHyperImagePrivate::spectrum(const QRect &area, const arma::mat &weight) const
{
    arma::vec out;
    if (!isLoaded) return out;
    if (!area.isValid()) return out;
    QRect rect(0, 0, lines, samples);
    if (!rect.contains(area)) return out;
    if (weight.n_rows != static_cast<arma::uword>(area.height()) || weight.n_cols != static_cast<arma::uword>(area.width())) return out;
    if (std::abs(arma::accu(weight) - 1.0) > 1e-6) return out;
    QString fileName = QString("%1/%2.raw").arg(fileFullPath).arg(fileCompleteBaseName);
    QFile file(fileName);
    if (!checkRawAvailibility(file)) return out;
    QDataStream stream(&file);
    int choice = (static_cast<int>(AEnviHyperImage::DataType::UnsignedShort) << 4) & static_cast<int>(AEnviHyperImage::InterLeave::Bil);
    switch (choice) {
        case 0:
            spectrumUnsignedShortBil(stream, area, weight, out);
            break;
        default:
            break;
    }
    file.close();
    return out;
}

arma::mat AEnviHyperImagePrivate::slice(const arma::uvec &bandSelection, const arma::vec &weight) const
{
    arma::mat out;
    if (!isLoaded) return out;
    if (arma::any(bandSelection >= static_cast<arma::sword>(bands))) return out;
    if (bandSelection.n_elem != weight.n_elem) return out;
    if (std::abs(arma::accu(weight) - 1.0) > 1e-6) return out;
    QString fileName = QString("%1/%2.raw").arg(fileFullPath).arg(fileCompleteBaseName);
    QFile file(fileName);
    if (!checkRawAvailibility(file)) return out;
    QDataStream stream(&file);
    int choice = (static_cast<int>(AEnviHyperImage::DataType::UnsignedShort) << 4) & static_cast<int>(AEnviHyperImage::InterLeave::Bil);
    switch (choice) {
        case 0:
            sliceUnsignedShortBil(stream, bandSelection, weight, out);
            break;
        default:
            break;
    }
    file.close();
    return out;
}

bool AEnviHyperImagePrivate::loadHdr(const QString &fileName)
{
    QFile file(fileName);
    if (!file.exists()) return false;
    if (!file.open(QFile::ReadOnly)) return false;
    QTextStream stream(&file);
    
    QString text = stream.readLine();
    if (text.simplified() != "ENVI") return false;
    QString key, value;
    QList<QString> pair;
    while (!stream.atEnd())
    {
        text = stream.readLine();
        if (!text.contains("=")) continue;
        pair = text.split("=");
        key = pair.first().simplified().toLower();
        value = pair.last().simplified().toLower();
        switch (keyList.indexOf(key))
        {
            case 0:
                lines = value.toInt();
                break;
            case 1:
                samples = value.toInt();
                break;
            case 2:
                bands = value.toInt();
                break;
            case 3:
                headerOffset = value.toInt();
                break;
            case 4:
                if (value == "envi standard") fileType = AEnviHyperImage::FileType::ENVI;
                break;
            case 5:
                dataType = static_cast<AEnviHyperImage::DataType>(value.toInt());
                break;
            case 6:
                if (value == "bil") interLeave = AEnviHyperImage::InterLeave::Bil;
            case 7:
                break;
            case 8:
                if (value == "nm") wavelengthUnit = AEnviHyperImage::WavelengthUnit::NanoMeter;
                break;
            case 9:
                pair = value.split(",");
                binning.first = pair.first().replace("{", "").simplified().toInt();
                binning.second = pair.first().replace("}", "").simplified().toInt();
                break;
            case 10:
                if (bands <= 0)
                {
                    file.close();
                    return false;
                }
                wavelength.set_size(bands);
                for (arma::uword i = 0; i < static_cast<arma::uword>(bands) && !stream.atEnd(); ++i)
                {
                    text = stream.readLine();
                    value = text;
                    value = value.replace(",", "").replace(";", "").replace("}", "").simplified();
                    wavelength[i] = value.toDouble();
                    if (text.contains("}")) break;
                }
                break;
            default:
                break;
        }
    }
    file.close();
    if (lines <= 0 || samples <= 0 || bands <= 0 || headerOffset < 0
            || fileType != AEnviHyperImage::FileType::ENVI
            || dataType == AEnviHyperImage::DataType::Unknown
            || interLeave == AEnviHyperImage::InterLeave::Unknown
            || wavelengthUnit == AEnviHyperImage::WavelengthUnit::Unknown
            || binning.first <= 0 || binning.second <= 0
            || wavelength.n_elem != static_cast<arma::uword>(bands) || !wavelength.is_finite() || arma::any(wavelength <= 0.0))
    {
        return false;
    }
    return true;
}

bool AEnviHyperImagePrivate::checkRawAvailibility(QFile &file) const
{
    if (!file.exists()) return false;
    qint64 fileSize = static_cast<qint64>(lines)*samples*bands*dataSize();
    if (file.size() != fileSize) return false;
    if (!file.open(QFile::ReadOnly)) return false;
    return true;
}

qint64 AEnviHyperImagePrivate::getOffset(int x, int y, int z) const
{
    switch (interLeave) {
        case AEnviHyperImage::InterLeave::Bil:
            return (static_cast<qint64>(y) + static_cast<qint64>(z)*samples + static_cast<qint64>(x)*samples*bands)*dataSize();
        default:
            return -1;
    }
}

void AEnviHyperImagePrivate::spectrumUnsignedShortBil(QDataStream &stream, const QRect &area, const arma::mat &weight, arma::vec &out) const
{
    arma::Col<unsigned short int> aux(static_cast<arma::uword>(area.height()));
    int x = area.left();
    int size = area.height()*dataSize();
    if (size <= 0) return;
    out.set_size(static_cast<arma::uword>(bands));
    out.fill(0.0);
    for (int i = 0; i < area.width(); ++i)
    {
        for (int z = 0; z < bands; ++z)
        {
            stream.device()->seek(getOffset(x, area.top(), z));
            stream.readRawData(reinterpret_cast<char *>(aux.memptr()), size);
            out[z] += arma::accu(arma::conv_to<arma::vec>::from(aux) % weight.col(i));
        }
        ++x;
    }
    out /= 65535.0;
}

void AEnviHyperImagePrivate::sliceUnsignedShortBil(QDataStream &stream, const arma::uvec &bandSelection, const arma::vec &weight, arma::mat &out) const
{
    arma::Row<unsigned short int> aux(samples);
    int size = samples*dataSize();
    if (size <= 0) return;
    out.set_size(lines, samples);
    out.fill(0.0);
    for (int x = 0; x < lines; ++x)
    {
        for (arma::uword k = 0; k < bandSelection.n_elem; ++k)
        {
            int z = static_cast<int>(bandSelection[k]);
            qint64 offset = getOffset(x, 0, z);
            if (offset < 0ll)
            {
                out.clear();
                return;
            }
            stream.device()->seek(offset);
            stream.readRawData(reinterpret_cast<char *>(aux.memptr()), size);
            out.row(x) += weight[k]*arma::conv_to<arma::rowvec>::from(aux);
        }
    }
    out /= 65535.0;
}
