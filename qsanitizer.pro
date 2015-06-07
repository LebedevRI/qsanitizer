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
    leaklistmodel.cc \
    leakitem.cc \
    stackitem.cc 

HEADERS  += mainwindow.h \
    leaklistmodel.h \
    leakitem.h \
    stackitem.h 

FORMS    += mainwindow.ui
