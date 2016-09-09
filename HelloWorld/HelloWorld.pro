#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T13:35:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWorld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spectrum.cpp \
    linear.cpp \
    kernel.cpp \
    image.cpp \
    gqueue.cpp \
    comptime.cpp \
    common.cpp \
    adjacency.cpp \
    slicer.cpp \
    displaymanager.cpp

HEADERS  += mainwindow.h \
    spectrum.h \
    mc920.h \
    linear.h \
    kernel.h \
    image.h \
    comptime.h \
    common.h \
    adjacency.h \
    gqueue.h \
    slicer.h \
    displaymanager.h

FORMS    += mainwindow.ui
