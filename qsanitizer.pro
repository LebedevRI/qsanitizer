#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T03:47:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qsanitizer
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    leaklistmodel.cc

HEADERS  += mainwindow.h \
    leaklistmodel.h

FORMS    += mainwindow.ui
