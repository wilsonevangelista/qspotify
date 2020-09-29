QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSpotify

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    playlistmanagerdialog.cpp

HEADERS += \
    mainwindow.h \
    playlistmanagerdialog.h \

include(src.pri)

FORMS += \
    mainwindow.ui \
    playlistmanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
