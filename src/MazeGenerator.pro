#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T21:19:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mazewidget.cpp \
    myview.cpp \
    mazegeneratorthread.cpp

HEADERS  += mainwindow.h \
    mazewidget.h \
    myview.h \
    mazegeneratorthread.h

RESOURCES += \
    resourses.qrc

QMAKE_CXXFLAGS += -std=c++11
