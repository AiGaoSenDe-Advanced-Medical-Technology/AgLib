#include "agabstracthyperimage.h"
#include "agabstracthyperimageprivate.h"

AAbstractHyperImage::~AAbstractHyperImage()
{
    
}

bool AAbstractHyperImage::isLoaded() const
{
    Q_D(const AAbstractHyperImage);
    return d->isLoaded;
}

int AAbstractHyperImage::lines() const
{
    Q_D(const AAbstractHyperImage);
    return d->lines;
}

int AAbstractHyperImage::samples() const
{
    Q_D(const AAbstractHyperImage);
    return d->samples;
}

int AAbstractHyperImage::bands() const
{
    Q_D(const AAbstractHyperImage);
    return d->bands;
}

AAbstractHyperImage::FileType AAbstractHyperImage::fileType() const
{
    Q_D(const AAbstractHyperImage);
    return d->fileType;
}

AAbstractHyperImage::DataType AAbstractHyperImage::dataType() const
{
    Q_D(const AAbstractHyperImage);
    return d->dataType;
}

AAbstractHyperImage::SensorType AAbstractHyperImage::sensorType() const
{
    Q_D(const AAbstractHyperImage);
    return d->sensorType;
}

const arma::vec &AAbstractHyperImage::wavelength() const
{
    Q_D(const AAbstractHyperImage);
    return d->wavelength;
}

AAbstractHyperImage::WavelengthUnit AAbstractHyperImage::wavelengthUnit() const
{
    Q_D(const AAbstractHyperImage);
    return d->wavelengthUnit;
}

bool AAbstractHyperImage::load(const QString &fileName)
{
    Q_D(AAbstractHyperImage);
    return d->load(fileName);
}

arma::vec AAbstractHyperImage::spectrum(int x, int y) const
{
    Q_D(const AAbstractHyperImage);
    QRect rect(x, y, 1, 1);
    arma::mat weight = arma::ones<arma::mat>(1, 1);
    return d->spectrum(rect, weight);
}

arma::vec AAbstractHyperImage::spectrum(const QPoint &point) const
{
    Q_D(const AAbstractHyperImage);
    QRect rect(point, point);
    arma::mat weight = arma::ones<arma::mat>(1, 1);
    return d->spectrum(rect, weight);
}

arma::vec AAbstractHyperImage::spectrum(int x, int y, int w, int h) const
{
    Q_D(const AAbstractHyperImage);
    QRect rect(x, y, 2*w + 1, 2*h + 1);
    rect.moveCenter(QPoint(x, y));
    arma::mat weight = arma::ones<arma::mat>(2*w + 1, 2*h + 1)/((2*w + 1)*(2*h + 1));
    return d->spectrum(rect, weight);
}

arma::vec AAbstractHyperImage::spectrum(const QPoint &center, const QSize &halfWidth) const
{
    Q_D(const AAbstractHyperImage);
    QSize size = 2*halfWidth + QSize(1, 1);
    QRect rect(center.x(), center.y(), size.width(), size.height());
    rect.moveCenter(center);
    arma::mat weight = arma::ones<arma::mat>(rect.width(), rect.height())/(rect.width()*rect.height());
    return d->spectrum(rect, weight);
}

arma::mat AAbstractHyperImage::slice(int z) const
{
    Q_D(const AAbstractHyperImage);
    arma::uvec bandSelection = z*arma::ones<arma::uvec>(1);
    arma::vec weight = arma::ones<arma::vec>(1);
    return d->slice(bandSelection, weight);
}

QImage AAbstractHyperImage::image(int r, int g, int b) const
{
    Q_D(const AAbstractHyperImage);
    arma::uvec redBands = r*arma::ones<arma::uvec>(1);
    arma::vec redWeight = arma::ones<arma::vec>(1);
    arma::uvec greenBands = g*arma::ones<arma::uvec>(1);
    arma::vec greenWeight = arma::ones<arma::vec>(1);
    arma::uvec blueBands = b*arma::ones<arma::uvec>(1);
    arma::vec blueWeight = arma::ones<arma::vec>(1);
    return d->image(redBands, redWeight, greenBands, greenWeight, blueBands, blueWeight);
}

AAbstractHyperImage::AAbstractHyperImage(AAbstractHyperImagePrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    
}
