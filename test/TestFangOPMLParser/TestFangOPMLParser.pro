#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T21:29:42
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testfangopmlparser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testfangopmlparser.cpp \
    ../../src/parser/OPMLParser.cpp \
    ../../src/parser/RawFeed.cpp \
    ../../src/parser/RawNews.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/parser/OPMLParser.h \
    ../../src/parser/RawFeed.h \
    ../../src/parser/RawNews.h

OTHER_FILES += \
    opml/feeddeemon.opml \
    opml/rssowl.opml
