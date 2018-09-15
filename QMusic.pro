#-------------------------------------------------
#
# Project created by QtCreator 2018-08-19T15:31:02
#
#-------------------------------------------------

QT       += core gui sql network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMusic
TEMPLATE = app


SOURCES += \


HEADERS  +=

INCLUDEPATH +=$$PWD mainWindows
include(mainWindows/mainWindows.pri)

INCLUDEPATH +=$$PWD PersonFiles
include(PersonFiles/PersonFiles.pri)

INCLUDEPATH +=$$PWD buttomWidget
include(buttomWidget/bottomWidget.pri)

INCLUDEPATH +=$$PWD topWidget
include(topWidget/topWidget.pri)

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

INCLUDEPATH +=$$PWD playListWidget
include(playListWidget/playListWidget.pri)

INLCUDEPATH +=$$PWD singleApplication
include(singleApplication/qsingleapplication.pri)


RESOURCES += \
    image.qrc

RC_FILE = images/ico/setIcon.rc
