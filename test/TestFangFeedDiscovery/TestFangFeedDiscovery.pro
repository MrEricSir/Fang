#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T22:19:20
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = tst_testfangfeeddiscovery
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

# TidyLib
VPATH += ../../tidylib ../../tidylib/include
INCLUDEPATH += ../../tidylib ../../tidylib/include
include(../../tidylib/tidylib.pri)


SOURCES += tst_testfangfeeddiscovery.cpp \
    ../../src/utilities/FeedDiscovery.cpp \
    ../../src/utilities/SimpleStateMachine.cpp \
    ../../src/utilities/WebPageGrabber.cpp \
    ../../src/parser/OPMLParser.cpp \
    ../../src/parser/NewsParser.cpp \
    ../../src/parser/ParserInterface.cpp \
    ../../src/parser/RawFeed.cpp \
    ../../src/parser/RawNews.cpp \
    ../../src/FangObject.cpp \
    ../../src/parser/ParserXMLWorker.cpp \
    ../../src/network/FangNetworkAccessManager.cpp \
    ../../src/utilities/SimpleHTTPDownloader.cpp \
    ../../src/utilities/NetworkUtilities.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/FeedDiscovery.h \
    ../../src/utilities/SimpleStateMachine.h \
    ../../src/utilities/WebPageGrabber.h \
    ../../src/parser/OPMLParser.h \
    ../../src/parser/NewsParser.h \
    ../../src/parser/ParserInterface.h \
    ../../src/parser/RawFeed.h \
    ../../src/parser/RawNews.h \
    ../../src/FangObject.h \
    ../../src/parser/ParserXMLWorker.h \
    ../../src/network/FangNetworkAccessManager.h \
    ../../src/utilities/SimpleHTTPDownloader.h \
    ../../src/utilities/NetworkUtilities.h
