#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T21:30:02
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MARKDOWN_COMPILER
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileexplorerwidget.cpp

HEADERS  += mainwindow.h \
    fileexplorerwidget.h

FORMS    += mainwindow.ui \
    fileexplorerwidget.ui
