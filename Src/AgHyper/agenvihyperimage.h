#ifndef AGHYPERIMAGE_H
#define AGHYPERIMAGE_H

#include "aghyperglobal.h"
#include "agabstracthyperimage.h"
#include <QtCore/QPair>

class AEnviHyperImagePrivate;

class AG_HYPER_SHARED AEnviHyperImage : public AAbstractHyperImage
{
        Q_OBJECT
        Q_DECLARE_PRIVATE(AEnviHyperImage)
        
    public:
        enum class InterLeave
        {
            Unknown = -1,
            Bil = 0
        };
        Q_ENUM(InterLeave)
        
    public:
        explicit AEnviHyperImage(QObject *parent = Q_NULLPTR);
        virtual ~AEnviHyperImage();
        
    public:
        qint64 headerOffset() const;
        InterLeave interLeave() const;
        const QPair<int, int> &binning() const;
};

#endif // AGHYPERIMAGE_H
