TEMPLATE = subdirs

CONFIG += c++11

SUBDIRS += \
    libqsanitizer \
    tests \
    gui

gui.depends = libqsanitizer
tests.depends = libqsanitizer
