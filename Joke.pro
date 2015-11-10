#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T17:22:37
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Joke
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    request.cpp \
    response.cpp \
    json.cpp \
    netmanager.cpp \
    jokelistwidget.cpp \

HEADERS  += dialog.h \
    request.h \
    response.h \
    json.h \
    netmanager.h \
    jokelistwidget.h \

FORMS    += dialog.ui
