QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/playlist.cpp \
    src/spotifyapi.cpp \
    src/track.cpp

HEADERS += \
    src/mainwindow.h \
    src/playlist.h \
    src/secrets.h \
    src/secrets.h.tpl \
    src/spotifyapi.h \
    src/track.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
