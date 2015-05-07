#-------------------------------------------------
#
# Project created by QtCreator 2014-07-04T16:53:16
#
#-------------------------------------------------

QT       += network testlib xml

TARGET = tst_testrawfeedrewritertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

VPATH += ../../tidylib ../../tidylib/include
INCLUDEPATH += ../../tidylib ../../tidylib/include
include(../../tidylib/tidylib.pri)


SOURCES += tst_testrawfeedrewritertest.cpp \
    ../../src/utilities/RawFeedRewriter.cpp \
    ../../src/utilities/ImageGrabber.cpp \
    ../../src/FangObject.cpp \
    ../../src/parser/RawNews.cpp \
    ../../src/network/FangNetworkAccessManager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/RawFeedRewriter.h \
    ../../src/utilities/ImageGrabber.h \
    ../../src/FangObject.h \
    ../../src/parser/RawNews.h \
    ../../src/network/FangNetworkAccessManager.h
