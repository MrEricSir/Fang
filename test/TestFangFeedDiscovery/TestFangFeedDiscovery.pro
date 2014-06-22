#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T22:19:20
#
#-------------------------------------------------

QT       += network webkit webkitwidgets xml testlib

QT       -= gui

TARGET = tst_testfangfeeddiscovery
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testfangfeeddiscovery.cpp \
    ../../src/utilities/FeedDiscovery.cpp \
    ../../src/utilities/SimpleStateMachine.cpp \
    ../../src/utilities/WebPageGrabber.cpp \
    ../../src/parser/OPMLParser.cpp \
    ../../src/parser/Parser.cpp \
    ../../src/parser/ParserInterface.cpp \
    ../../src/parser/RawFeed.cpp \
    ../../src/parser/RawNews.cpp \
    ../../src/utilities/NetworkUtilities.cpp \
    ../../src/FangObject.cpp \
    ../../src/parser/ParserXMLWorker.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/FeedDiscovery.h \
    ../../src/utilities/SimpleStateMachine.h \
    ../../src/utilities/WebPageGrabber.h \
    ../../src/parser/OPMLParser.h \
    ../../src/parser/Parser.h \
    ../../src/parser/ParserInterface.h \
    ../../src/parser/RawFeed.h \
    ../../src/parser/RawNews.h \
    ../../src/utilities/NetworkUtilities.h \
    ../../src/FangObject.h \
    ../../src/parser/ParserXMLWorker.h
