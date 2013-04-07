#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T18:28:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DRVideoGrabber.out
TEMPLATE = app

QMAKE_CFLAGS_DEBUG += -g
QMAKE_CFLAGS_RELEASE +=


LIBS +=

SOURCES += main.cpp\
        MainWindow.cpp \
    VideoModel.cpp \
    SlugModel.cpp \
    ResourceModel.cpp \
    DRSession.cpp \
    BaseModel.cpp \
    MainController.cpp \
    LoaderThread.cpp

HEADERS  += MainWindow.h \
    VideoModel.h \
    SlugModel.h \
    ResourceModel.h \
    DRSession.h \
    BaseModel.h \
    MainController.h \
    IMainController.h \
    LoaderThread.h


FORMS    += MainWindow.ui

## automatically added when statically linking to libjson
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -ljson
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -ljson
else:symbian: LIBS += -ljson
else:unix: LIBS += -L/usr/lib/ -ljson

INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/release/json.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/debug/json.lib
else:unix:!symbian: PRE_TARGETDEPS += /usr/lib/libjson.a

## automatically added when statically linking to libcurl
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lcurl
else:symbian: LIBS += -lcurl
else:unix: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lcurl

INCLUDEPATH += /usr/lib/x86_64-linux-gnu
DEPENDPATH += /usr/lib/x86_64-linux-gnu

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/release/curl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/curl.lib
else:unix:!symbian: PRE_TARGETDEPS += /usr/lib/x86_64-linux-gnu/libcurl.a
