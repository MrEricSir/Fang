#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T12:50:05
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

# TidyLib
VPATH += ../../tidylib ../../tidylib/include
INCLUDEPATH += ../../tidylib ../../tidylib/include
include(../../tidylib/tidylib.pri)


TARGET = tst_testwebpagegrabber
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testwebpagegrabber.cpp \
    ../../src/utilities/WebPageGrabber.cpp \
    ../../src/FangObject.cpp \
    ../../src/utilities/SimpleHTTPDownloader.cpp \
    ../../src/network/FangNetworkAccessManager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/WebPageGrabber.h \
    ../../src/FangObject.h \
    ../../src/utilities/SimpleHTTPDownloader.h \
    ../../src/network/FangNetworkAccessManager.h
