#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T23:32:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trabalhoGrafos
TEMPLATE = app


SOURCES += main.cpp\
    grafo.cpp \
    maincontroller.cpp \
    no.cpp \
    gmlparser.cpp \
    graphmlparser.cpp \
    grafobuilder.cpp \
    geradorgraphml.cpp \
    cluster.cpp \
    kmeans.cpp \
    centroid.cpp

HEADERS  += \
    grafo.h \
    maincontroller.h \
    no.h \
    gmlparser.h \
    graphmlparser.h \
    grafotipo.h \
    grafobuilder.h \
    geradorgraphml.h \
    cluster.h \
    kmeans.h \
    centroid.h \
    kmeansmodo.h \
    iteradorgrafo.h

FORMS    += mainwindow.ui
