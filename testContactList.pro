#-------------------------------------------------
#
# Project created by QtCreator 2016-07-16T17:32:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testContactList
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    contactdelegate.cpp \
    contactmodel.cpp \
    contactdata.cpp \
    recentcontactdelegate.cpp

HEADERS  += widget.h \
    contactdelegate.h \
    contactmodel.h \
    contactdata.h \
    recentcontactdelegate.h

FORMS    += widget.ui
