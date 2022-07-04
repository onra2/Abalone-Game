include(../defaults.pri)

TEMPLATE = lib
TARGET = libmetier
DESTDIR = ../lib

HEADERS += \
    board.h \
    config.h \
    direction.h \
    game.h \
    iObservable.h \
    iObserver.h \
    marble.h \
    position.h \
    score.h \
    test.h

SOURCES += \
    board.cpp \
    direction.cpp \
    game.cpp \
    marble.cpp \
    position.cpp \
    score.cpp \
