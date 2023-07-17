#-------------------------------------------------
#
# Project created by QtCreator 2023-07-05T16:02:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommunicationMonitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR += $$PWD/bin_vs
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(./Log/Log.pri)
include(./Utils/Utils.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    iputils.cpp \
    tcpmonitor.cpp \
    tcpclient.cpp \
    tcpclientmanager.cpp

HEADERS += \
        mainwindow.h \
    iputils.h \
    tcpmonitor.h \
    tcpclient.h \
    tcpclientmanager.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    CommunicationManager.json

srcFile1 = $$PWD/CommunicationManager.json
srcFile2 = $$PWD/CommunicationManager.json
dstDir = $$PWD/bin_vs/Config/CommunicationManager.json
##windows上需要转换路径斜杠 其他系统不需要
srcFile1 = $$replace(srcFile1, /, \\);
#srcFile2 = $$replace(srcFile2, /, \\);
dstDir = $$replace(dstDir, /, \\);
