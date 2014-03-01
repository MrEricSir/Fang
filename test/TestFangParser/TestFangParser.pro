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
    feeds/slashdot.org.rss \
    feeds/sfist.com.rss \
    feeds/theonion.com.rss \
    feeds/fark.com.rss \
    feeds/laughingsquid.com.rss \
    feeds/bbc.co.uk.rss \
    feeds/zaphos.wordpress.com.rss \
    feeds/theregister.co.uk.atom \
    feeds/sfweekly.com.rss \
    feeds/sports.people.com.cn.rss \
    feeds/science.economist.com.rss \
    feeds/npr.org.rss \
    feeds/thesmokinggun.com.rss \
    feeds/lifehacker.com.rss \
    feeds/missionmission.feedburner.rss \
    feeds/uptownalmanac.com.rss \
    feeds/mirror.co.uk.rss \
    feeds/donga.com.rss \
    feeds/lokmat.com.rss
