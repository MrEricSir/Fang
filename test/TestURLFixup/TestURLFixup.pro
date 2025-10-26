QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../src/utilities/NetworkUtilities.cpp \
    tst_urlfixup.cpp

HEADERS += \
    ../../src/utilities/NetworkUtilities.h
