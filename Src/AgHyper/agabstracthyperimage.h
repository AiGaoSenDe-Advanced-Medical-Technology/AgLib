#ifndef AGABSTRACTHYPERIMAGE_H
#define AGABSTRACTHYPERIMAGE_H

#include "aghyperglobal.h"
#include <armadillo>
#include <QtCore/QObject>
#include <QtGui/QImage>

class AAbstractHyperImagePrivate;

class AAbstractHyperImage : public QObject
{
        Q_OBJECT
        Q_DECLARE_PRIVATE(AAbstractHyperImage)
        
    public:
        enum class FileType
        {
            Unknown = -1,
            ENVI = 0
        };
        Q_ENUM(FileType)
        enum class DataType
        {
            Unknown = -1,
            UnsignedShort = 12
        };
        Q_ENUM(DataType)
        enum class SensorType
        {
            Unknown = -1
        };
        Q_ENUM(SensorType)
        enum class WavelengthUnit
        {
            Unknown = 999,
            NanoMeter = -9
        };
        Q_ENUM(WavelengthUnit)
        
    public:
        virtual ~AAbstractHyperImage();
        
    public:
        bool isLoaded() const;
        int lines() const;
        int samples() const;
        int bands() const;
        AAbstractHyperImage::FileType fileType() const;
        AAbstractHyperImage::DataType dataType() const;
        AAbstractHyperImage::SensorType sensorType() const;
        AAbstractHyperImage::WavelengthUnit wavelengthUnit() const;
        const arma::vec &wavelength() const;
        
    public:
        bool load(const QString &fileName);
        
    public:
        arma::vec spectrum(int x, int y) const;
        arma::vec spectrum(const QPoint &point) const;
        arma::vec spectrum(int x, int y, int w, int h) const;
        arma::vec spectrum(const QPoint &center, const QSize &halfWidth) const;
        
    public:
        arma::mat slice(int z) const;
        
    public:
        QImage image(int r, int g, int b) const;
        
    protected:
        explicit AAbstractHyperImage(AAbstractHyperImagePrivate &dd, QObject *parent = Q_NULLPTR);
        
    protected:
        QScopedPointer<AAbstractHyperImagePrivate> d_ptr;
};

#endif // AGABSTRACTHYPERIMAGE_H
