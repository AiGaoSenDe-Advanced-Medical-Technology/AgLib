QT += core gui

TEMPLATE = lib
TARGET = Hyper

include($$PWD/../../Config/Config.prf)

HEADERS += \
    agabstracthyperimage.h \
    agabstracthyperimageprivate.h \
    agenvihyperimage.h \
    agenvihyperimageprivate.h

SOURCES += \
    agabstracthyperimage.cpp \
    agabstracthyperimageprivate.cpp \
    agenvihyperimage.cpp \
    agenvihyperimageprivate.cpp

HEADERS += \
    aghyperglobal.h \
    AAbstractHyperImage \
    AEnviHyperImage

include($$PWD/Depends.prf)
