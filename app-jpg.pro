QT += core
QT -= gui

TARGET = app-jpg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

LIBS += -L /usr/lib -ljpeg

QMAKE_CXXFLAGS += -std=c++0x

