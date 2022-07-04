include(../defaults.pri)

TEMPLATE = app
CONFIG += console

LIBS += -L../lib -lmetier

HEADERS += \
    color.h \
    mainController.h \
    textview.h

SOURCES += \
    mainController.cpp \
    textview.cpp \
    main.cpp \
    color.cpp

