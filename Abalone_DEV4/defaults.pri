INCLUDEPATH += $$PWD/metier

SRC_DIR = $$PWD

CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17 \
                -Wpedantic \
                -Werror
