#include "agabstracthyperimageprivate.h"

AAbstractHyperImagePrivate::AAbstractHyperImagePrivate(AAbstractHyperImage *qq) :
    q_ptr(qq)
{
    
}

AAbstractHyperImagePrivate::~AAbstractHyperImagePrivate()
{
    
}

void AAbstractHyperImagePrivate::unload()
{
    isLoaded = false;
    fileFullPath.clear();
    fileCompleteBaseName.clear();
    lines = 0;
    samples = 0;
    bands = 0;
    fileType = AAbstractHyperImage::FileType::Unknown;
    dataType = AAbstractHyperImage::DataType::Unknown;
    sensorType = AAbstractHyperImage::SensorType::Unknown;
    wavelengthUnit = AAbstractHyperImage::WavelengthUnit::Unknown;
    wavelength.clear();
}

QImage AAbstractHyperImagePrivate::image(const arma::uvec &redBand, const arma::vec &redWeight, const arma::uvec &greenBand, const arma::vec &greenWeight, const arma::uvec &blueBand, const arma::vec &blueWeight) const
{
    QImage out;
    arma::mat redSlice = slice(redBand, redWeight);
    if (redSlice.is_empty()) return out;
    arma::mat greenSlice = slice(greenBand, greenWeight);
    if (greenSlice.is_empty()) return out;
    arma::mat blueSlice = slice(blueBand, blueWeight);
    if (blueSlice.is_empty()) return out;
    
    redSlice.elem(arma::find(redSlice > 1.0)).fill(1.0);
    redSlice.elem(arma::find(redSlice < 0.0)).fill(0.0);
    greenSlice.elem(arma::find(greenSlice > 1.0)).fill(1.0);
    greenSlice.elem(arma::find(greenSlice < 0.0)).fill(0.0);
    blueSlice.elem(arma::find(blueSlice > 1.0)).fill(1.0);
    blueSlice.elem(arma::find(blueSlice < 0.0)).fill(0.0);
    
    out = QImage(lines, samples, QImage::Format_RGB32);
    QColor color;
    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < samples; ++j)
        {
            color.setRgbF(redSlice.at(i, j), greenSlice.at(i, j), blueSlice.at(i, j));
            out.setPixelColor(i, j, color);
        }
    }
    
    return out;
}

qint64 AAbstractHyperImagePrivate::dataSize() const
{
    switch (dataType)
    {
        case AAbstractHyperImage::DataType::UnsignedShort:
            return 2;
        default:
            return -1;
    }
}
