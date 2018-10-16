#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T22:29:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_libcurl
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

LIBS += -L/usr/local/lib -lcurl
