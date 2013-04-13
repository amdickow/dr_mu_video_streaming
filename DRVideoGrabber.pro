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
    MainController.cpp \
    VideoModel.cpp \
    SlugModel.cpp \
    ResourceModel.cpp \
    DRSession.cpp \
    JsonHandlerBase.cpp

HEADERS  += MainWindow.h \
    MainController.h \
    VideoModel.h \
    SlugModel.h \
    ResourceModel.h \
    DRSession.h \
    JsonHandlerBase.h


FORMS    += MainWindow.ui
