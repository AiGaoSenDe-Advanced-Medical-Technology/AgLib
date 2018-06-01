#include "agenvihyperimage.h"
#include "agenvihyperimageprivate.h"

AEnviHyperImage::AEnviHyperImage(QObject *parent) :
    AAbstractHyperImage(*new AEnviHyperImagePrivate(this), parent)
{
    
}

AEnviHyperImage::~AEnviHyperImage()
{
    
}

qint64 AEnviHyperImage::headerOffset() const
{
    Q_D(const AEnviHyperImage);
    return d->headerOffset;
}

AEnviHyperImage::InterLeave AEnviHyperImage::interLeave() const
{
    Q_D(const AEnviHyperImage);
    return d->interLeave;
}

const QPair<int, int> &AEnviHyperImage::binning() const
{
    Q_D(const AEnviHyperImage);
    return d->binning;
}
