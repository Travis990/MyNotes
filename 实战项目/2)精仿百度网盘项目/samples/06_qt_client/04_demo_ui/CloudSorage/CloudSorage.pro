#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T12:20:17
#
#-------------------------------------------------

QT       += core gui
QT += network
CONFIG += c++11

RC_ICONS = disk.ico #windows 制作图标

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CloudSorage
TEMPLATE = app


SOURCES += main.cpp\
        loginwidget.cpp \
    logininfoinstance.cpp \
    mainwidget.cpp \
    mainwidgetbutton.cpp \
    common.cpp

HEADERS  += loginwidget.h \
    logininfoinstance.h \
    mainwidget.h \
    mainwidgetbutton.h \
    common.h

FORMS    += loginwidget.ui \
    mainwidget.ui \
    mainwidgetbutton.ui

RESOURCES += \
    image.qrc
