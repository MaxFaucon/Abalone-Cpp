CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

OTHER_FILES += abalonecore.pri

include(../../config.pri)

SOURCES += \
    model/board.cpp \
    model/game.cpp \
    model/player.cpp \
    model/position.cpp \
    observer/subject.cpp
HEADERS += \
    model/board.h \
    model/color.h \
    model/game.h \
    model/hexagon.h \
    model/player.h \
    model/position.h \
    observer/observer.h \
    observer/subject.h

DISTFILES += \
    libabalonecore.a
