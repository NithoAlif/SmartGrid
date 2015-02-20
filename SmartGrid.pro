#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T23:59:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SmartGrid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    barang.cpp \
    smartgriddata.cpp \
    qcustomplot.cpp \
    greedy.cpp

HEADERS  += mainwindow.h \
    barang.h \
    smartgriddata.h \
    qcustomplot.h \
    greedy.h

FORMS    += mainwindow.ui \

RESOURCES += \
    resource.qrc
