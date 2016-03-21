#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T18:59:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLocalServerSample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adapter.cpp

HEADERS  += mainwindow.h \
    adapter.h

FORMS    += mainwindow.ui
