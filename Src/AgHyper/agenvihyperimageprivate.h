#ifndef AGHYPERIMAGEPRIVATE_H
#define AGHYPERIMAGEPRIVATE_H

#include "aghyperglobal.h"
#include "agabstracthyperimageprivate.h"
#include "agenvihyperimage.h"

#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>

class AEnviHyperImagePrivate : public AAbstractHyperImagePrivate
{
        Q_DECLARE_PUBLIC(AEnviHyperImage)
        
    public:
        static QVector<QString> keyList;
        
    public:
        qint64 headerOffset;
        AEnviHyperImage::InterLeave interLeave;
        QPair<int, int> binning;
        
    public:
        explicit AEnviHyperImagePrivate(AEnviHyperImage *qq);
        virtual ~AEnviHyperImagePrivate();
        
    public:
        virtual void unload();
        virtual bool load(const QString &fileName);
        virtual arma::vec spectrum(const QRect &area, const arma::mat &weight) const;
        virtual arma::mat slice(const arma::uvec &bandSelection, const arma::vec &weight) const;
        
    private:
        bool loadHdr(const QString &fileName);
        bool checkRawAvailibility(QFile &file) const;
        qint64 getOffset(int x, int y, int z) const;
        void spectrumUnsignedShortBil(QDataStream &stream, const QRect &area, const arma::mat &weight, arma::vec &out) const;
        void sliceUnsignedShortBil(QDataStream &stream, const arma::uvec &bandSelection, const arma::vec &weight, arma::mat &s) const;
};

#endif // AGHYPERIMAGEPRIVATE_H
