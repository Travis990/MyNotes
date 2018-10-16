#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T09:29:20
#
#-------------------------------------------------

QT       += core gui
QT += network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = upload
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
