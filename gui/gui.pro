#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T11:25:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qsanitizer
TEMPLATE = app

CONFIG  += c++11

SOURCES += main.cc\
		mainwindow.cc \
    ignoredobjectsdialog.cc \
    ignoredobjectstablemodel.cc

HEADERS  += mainwindow.h \
    ignoredobjectsdialog.h \
    ignoredobjectstablemodel.h

FORMS    += mainwindow.ui \
    ignoredobjectsdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libqsanitizer/release/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../libqsanitizer/release/
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libqsanitizer/debug/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../libqsanitizer/debug/
else:unix: LIBS += -L$$OUT_PWD/../libqsanitizer/ -lqsanitizer -Wl,-rpath=$$OUT_PWD/../libqsanitizer/

INCLUDEPATH += $$PWD/../libqsanitizer
DEPENDPATH += $$PWD/../libqsanitizer
