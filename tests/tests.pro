QT += testlib
QT += gui widgets network
CONFIG += qt warn_on depend_includepath testcase

include($$PWD/../src/src.pri)

TEMPLATE = app

SOURCES +=  tst_qspotifytest.cpp

