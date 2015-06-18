TEMPLATE = subdirs

CONFIG += c++11

SUBDIRS += \
    libqsanitizer \
    tests \
    gui

tests.depends = libqsanitizer
gui.depends = libqsanitizer
