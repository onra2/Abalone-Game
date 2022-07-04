include(../defaults.pri)

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

LIBS += -L../lib -lmetier

TEMPLATE = app

SOURCES +=  tst_test.cpp
