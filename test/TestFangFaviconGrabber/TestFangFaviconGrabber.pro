#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T19:38:04
#
#-------------------------------------------------

QT       += network webkit webkitwidgets xml testlib

QT       -= gui

TARGET = tst_testfangfavicongrabbertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testfangfavicongrabbertest.cpp \
    ../../src/utilities/FaviconGrabber.cpp \
    ../../src/utilities/WebPageGrabber.cpp \
    ../../src/utilities/SimpleStateMachine.cpp \
    ../../src/FangObject.cpp \
    ../../src/network/FangNetworkAccessManager.cpp \
    ../../src/utilities/NetworkUtilities.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/FaviconGrabber.h \
    ../../src/utilities/WebPageGrabber.h \
    ../../src/utilities/SimpleStateMachine.h \
    ../../src/FangObject.h \
    ../../src/network/FangNetworkAccessManager.h \
    ../../src/utilities/NetworkUtilities.h
