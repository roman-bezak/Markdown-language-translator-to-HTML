#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T21:30:02
#
#-------------------------------------------------

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MARKDOWN_COMPILER
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mdeditor.cpp \
    writecontenttofile.cpp \
    reloadwebview.cpp \
    options.cpp


HEADERS  += mainwindow.h \
    mdeditor.h \
    writecontenttofile.h \
    reloadwebview.h \
    options.h


FORMS    += mainwindow.ui \
    options.ui
