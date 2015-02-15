#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T23:59:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartGrid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smartgrid.cpp \
    barang.cpp

HEADERS  += mainwindow.h \
    smartgrid.h \
    barang.h

FORMS    += mainwindow.ui \

RESOURCES += \
    resource.qrc
