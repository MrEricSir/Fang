#-------------------------------------------------
#
# Project created by QtCreator 2014-07-04T16:53:16
#
#-------------------------------------------------

QT       += network webkit testlib webkitwidgets

TARGET = tst_testrawfeedrewritertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testrawfeedrewritertest.cpp \
    ../../src/utilities/RawFeedRewriter.cpp \
    ../../src/utilities/ImageGrabber.cpp \
    ../../src/utilities/WebImageSizeRewriter.cpp \
    ../../src/utilities/WebPageGrabber.cpp \
    ../../src/FangObject.cpp \
    ../../src/parser/RawNews.cpp \
    ../../src/network/FangNetworkAccessManager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/RawFeedRewriter.h \
    ../../src/utilities/ImageGrabber.h \
    ../../src/utilities/WebImageSizeRewriter.h \
    ../../src/utilities/WebPageGrabber.h \
    ../../src/FangObject.h \
    ../../src/parser/RawNews.h \
    ../../src/network/FangNetworkAccessManager.h
