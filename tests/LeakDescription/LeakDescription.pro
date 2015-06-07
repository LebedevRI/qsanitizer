#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T21:59:09
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_leakdescription
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG   += c++11
CONFIG   += testcase

SOURCES += tst_leakdescription.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libqsanitizer/release/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../../libqsanitizer/release/
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libqsanitizer/debug/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../../libqsanitizer/debug/
else:unix: LIBS += -L$$OUT_PWD/../../libqsanitizer/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../../libqsanitizer/

INCLUDEPATH += $$PWD/../../libqsanitizer
DEPENDPATH += $$PWD/../../libqsanitizer

INCLUDEPATH += $$PWD/../LeakDescription
DEPENDPATH += $$PWD/../LeakDescription

HEADERS += \
	tst_leakdescription.h
