#-------------------------------------------------
#
# Project created by QtCreator 2018-07-30T20:36:32
#
#-------------------------------------------------
#QT工程引入core gui模块
QT       += core gui
#如果QT版本大于4，那么就引入widgets模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#生成的目标文件的名字
TARGET = hello
#应用程序
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#如果使用了废弃的接口，就报警告
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h
