#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T20:21:44
#
#-------------------------------------------------

QT       += xml testlib network

QT       -= gui

TARGET = tst_fangparser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_fangparser.cpp \
    ../../src/parser/Parser.cpp \
    ../../src/parser/ParserInterface.cpp \
    ../../src/parser/RawFeed.cpp \
    ../../src/parser/RawNews.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/parser/Parser.h \
    ../../src/parser/ParserInterface.h \
    ../../src/parser/RawFeed.h \
    ../../src/parser/RawNews.h

OTHER_FILES += \
    feeds/mrericsir.com.rss \
    feeds/slashdot.org.rss
