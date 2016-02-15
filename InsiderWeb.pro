#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T21:26:15
#
#-------------------------------------------------

QT       += core gui network webkitwidgets
QT += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InsiderWeb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp \
    buildtypedialog.cpp \
    insiderwebdialog.cpp

HEADERS  += mainwindow.h \
    utils.h \
    buildtypedialog.h \
    insiderwebdialog.h

FORMS    += mainwindow.ui \
    buildtypedialog.ui \
    insiderwebdialog.ui

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc
