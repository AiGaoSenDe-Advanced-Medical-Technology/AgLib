TEMPLATE = subdirs

HEADERS += \
    Src/agglobal.hpp \
    Src/agdebug.hpp

Hyper.subdir = Src/AgHyper
SUBDIRS += Hyper

Main.subdir = Src/Main
Main.depends += Hyper
SUBDIRS += Main
