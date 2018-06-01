#ifndef AGABSTRACTHYPERIMAGEPRIVATE_H
#define AGABSTRACTHYPERIMAGEPRIVATE_H

#include "aghyperglobal.h"
#include "agabstracthyperimage.h"

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QRect>
#include <QtGui/QImage>

class AAbstractHyperImagePrivate
{
        Q_DECLARE_PUBLIC(AAbstractHyperImage)
        
    public:
        AAbstractHyperImage *q_ptr;
        
    public:
        bool isLoaded;
        QString fileFullPath;
        QString fileCompleteBaseName;
        int lines;
        int samples;
        int bands;
        AAbstractHyperImage::FileType fileType;
        AAbstractHyperImage::DataType dataType;
        AAbstractHyperImage::SensorType sensorType;
        AAbstractHyperImage::WavelengthUnit wavelengthUnit;
        arma::vec wavelength;
        
    public:
        explicit AAbstractHyperImagePrivate(AAbstractHyperImage *qq);
        virtual ~AAbstractHyperImagePrivate();
        
    public:
        virtual void unload();
        virtual bool load(const QString &fileName) = 0;
        virtual arma::vec spectrum(const QRect &area, const arma::mat &weight) const = 0;
        virtual arma::mat slice(const arma::uvec &bandSelection, const arma::vec &weight) const = 0;
        QImage image(const arma::uvec &redBand, const arma::vec &redWeight, const arma::uvec &greenBand, const arma::vec &greenWeight, const arma::uvec &blueBand, const arma::vec &blueWeight) const;
        
    protected:
        qint64 dataSize() const;
};

#endif // AGABSTRACTHYPERIMAGEPRIVATE_H
