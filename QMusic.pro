#-------------------------------------------------
#
# Project created by QtCreator 2018-08-19T15:31:02
#
#-------------------------------------------------

QT       += core gui sql network multimedia
CONFIG += c++11

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

INCLUDEPATH +=$$PWD singleApplication
include(singleApplication/qsingleapplication.pri)

INCLUDEPATH +=$$PWD playingWidget
include(playingWidget/playingWidget.pri)

INCLUDEPATH +=$$PWD musicPlayer
include(musicPlayer/musicPlayer.pri)

INCLUDEPATH +=$$PWD netWork
include(netWork/netWork.pri)

INCLUDEPATH +=$$PWD pythonUtils
include(pythonUtils/pythonUtils.pri)

INCLUDEPATH += F:\Python32bit\include
DEPENDPATH += F:\Python32bit\libs
LIBS += -LF:\Python32bit\libs -lpython36

LIBS += -LF:\Python32bit\libs\
-l_tkinter\
-lpython3\
-lpython36



OTHER_FILES += Debug/__init__.py
OTHER_FILES += Debug/api.py
OTHER_FILES += Debug/config.py
OTHER_FILES += Debug/const.py
OTHER_FILES += Debug/encryptpy
OTHER_FILES += Debug/logger.py
OTHER_FILES += Debug/NeteaseAPI.py
OTHER_FILES += Debug/singleton.py
OTHER_FILES += Debug/storage.py
OTHER_FILES += Debug/utils.py
OTHER_FILES += Debug/QQMusicAPI.py


RESOURCES += \
    image.qrc

RC_FILE = images/ico/setIcon.rc
