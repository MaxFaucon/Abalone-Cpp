CONFIG += c++17

CONFIG -= debug_and_release debug_and_release_target

include($${PWD}/src/abalonecore/abalonecore.pri)

QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors -Wall -Wuninitialized
