QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 #console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    movie/src/MovieWidget.cpp \
    movie/src/DecodeThread.cpp \
    movie/src/VideoThread.cpp \
    movie/src/AudioThread.cpp \
    movie/src/AVInfo.cpp \
    movie/src/AVStreamSeperate.cpp
HEADERS += \
    BtnObj/inc/AVSeparateBtn.h \
    mainwindow.h \
    MacroDefine.h \
    movie/inc/AVInfo.h \
    movie/inc/AudioThread.h \
    movie/inc/DecodeThread.h \
    movie/inc/MovieWidget.h \
    movie/inc/VideoThread.h \
    movie/inc/AVStreamSeperate.h

HEADERS += \
    BtnObj/inc/BtnObj.h \
    BtnObj/inc/Pause.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    ffmpeg/include  \
    movie/inc
   # frame

TRANSLATIONS += \
    XPlayer_zh_CN.ts

DESTDIR = $$PWD/out

LIBS += -L$$PWD/ffmpeg/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale


QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
