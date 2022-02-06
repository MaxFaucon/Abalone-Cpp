TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../../config.pri)

SOURCES += \
        controller/controller.cpp \
        main/main.cpp \
        view/tui.cpp

HEADERS += \
    controller/controller.h \
    view/tui.h

DISTFILES += \
    tui
