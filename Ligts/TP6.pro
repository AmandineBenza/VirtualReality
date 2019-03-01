#-------------------------------------------------
#
# Project created by QtCreator 2019-01-09T20:06:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP6
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
windows:LIBS += -lopengl32

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    widgetopengl.cpp \
    camera.cpp \
    drawable.cpp \
    cube.cpp \
    cubetex.cpp \
    deAJouer.cpp \
    skybox.cpp \
    cameraspherique.cpp \
    cubeeclaire.cpp \
    light.cpp

HEADERS += \
        mainwindow.h \
    widgetopengl.h \
    camera.h \
    camera.h \
    drawable.h \
    cube.h \
    cubetex.h \
    deAJouer.h \
    skybox.h \
    cameraspherique.h \
    cubeeclaire.h \
    light.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
