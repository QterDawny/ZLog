#-------------------------------------------------
#
# Project created by QtCreator 2015-05-02T17:11:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZLog
TEMPLATE = app

DEFINES += CMD_DEBUG

include(./log4qt/log4qt.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    zlog.cpp

HEADERS  += mainwindow.h \
    zlog.h

FORMS    += mainwindow.ui
