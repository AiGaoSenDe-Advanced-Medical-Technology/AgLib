QT += core gui widgets printsupport

TEMPLATE = app
TARGET = Main

include($$PWD/../../Config/Config.prf)
TARGET = Main

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp

FORMS += \
    mainwindow.ui

include($$PWD/Depends.prf)
