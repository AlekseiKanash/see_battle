#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T01:10:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    battlescene.cpp \
    sheep.cpp \
    sheeppart.cpp

HEADERS  += mainwindow.h \
    battlescene.h \
    sheep.h \
    sceneparameters.h \
    ghostsheep.h \
    sheeppart.h

FORMS    += mainwindow.ui
