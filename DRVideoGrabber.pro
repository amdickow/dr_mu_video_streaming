#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T18:28:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DRVideoGrabber.out
TEMPLATE = app

QMAKE_CFLAGS_DEBUG += -g
QMAKE_CFLAGS_RELEASE +=


LIBS +=

SOURCES += main.cpp\
        MainWindow.cpp \
    DRHttpSession.cpp \
    JsonHandlerBase.cpp \
    JsonHandlerSlug.cpp \
    JsonHandlerResource.cpp \
    JsonHandlerVideo.cpp \
    MainUiController.cpp

HEADERS  += MainWindow.h \
    JsonHandlerBase.h \
    JsonHandlerSlug.h \
    JsonHandlerResource.h \
    JsonHandlerVideo.h \
    MainUiController.h \
    DRHttpSession.h


FORMS    += MainWindow.ui
