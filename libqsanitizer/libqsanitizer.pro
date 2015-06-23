#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T11:23:15
#
#-------------------------------------------------

QT       -= gui

TARGET = qsanitizer
TEMPLATE = lib

CONFIG  += c++11

DEFINES += LIBQSANITIZER_LIBRARY

SOURCES += qsanitizer.cc \
    leakitem.cc \
    stackitem.cc \
    leakdescription.cc \
    leaklistmodel.cc \
    stackitemparserxml.cc \
    abstractstackitem.cc \
    stackitemparserdefault.cc \
    leaklist.cc \
    leaklistsortfilterproxymodel.cc

HEADERS += qsanitizer.h\
		libqsanitizer_global.h \
    leakitem.h \
    stackitem.h \
    leakdescription.h \
    leaklistmodel.h \
    stackitemparserxml.h \
    abstractstackitem.h \
    stackitemparserdefault.h \
    leaklist.h \
    leaklistsortfilterproxymodel.h

unix {
	target.path = /usr/lib
	INSTALLS += target
}
