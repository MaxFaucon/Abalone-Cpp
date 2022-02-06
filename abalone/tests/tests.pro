TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

win32-g++* {
     #Work around "too many sections" bug in MinGW
     #This comes from the catch2 header only file being gargantuan.
    QMAKE_CXXFLAGS += -Wa,-mbig-obj
}

include(../config.pri)

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="../libs/"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

SOURCES +=     main.cpp     tst_board.cpp

HEADERS +=
