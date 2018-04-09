#-------------------------------------------------
#
# Project created by QtCreator 2018-02-14T17:49:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# all warnings turned off
CONFIG += warn_off

SOURCES += \
        mainwindow.cpp \
    Dot.cpp \
    area.cpp \
    inv.cpp \
    ship.cpp \
    lookwindow.cpp \
    areamanager.cpp \
    section.cpp \
    item.cpp \
    launchdialog.cpp \
    start.cpp \
    enddialog.cpp \
    exactitem.cpp

HEADERS += \
        mainwindow.h \
    Dot.h \
    area.h \
    inv.h \
    ship.h \
    lookwindow.h \
    areamanager.h \
    section.h \
    item.h \
    launchdialog.h \
    start.h \
    enddialog.h \
    exactitem.h

RESOURCES += \
    images.qrc

FORMS += \
    area.ui \
    inv.ui \
    ship.ui \
    lookwindow.ui \
    launchdialog.ui \
    start.ui \
    enddialog.ui

DISTFILES +=

