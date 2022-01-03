QT       += core widgets
QT       += widgets
QT       += network widgets
QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = MirrorGUI
TEMPLATE = app 
SOURCES += *.cpp
HEADERS += *.h
RESOURCES += \
    resources.qrc
LIBS += 