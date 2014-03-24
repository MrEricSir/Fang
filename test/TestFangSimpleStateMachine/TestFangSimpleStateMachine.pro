#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T18:24:01
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testfangsimplestatemachine
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testfangsimplestatemachine.cpp \
    ../../src/utilities/SimpleStateMachine.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utilities/SimpleStateMachine.h
