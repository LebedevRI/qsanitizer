#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T19:43:08
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_leakitemtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_leakitemtest.cc ../../leakitem.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"
