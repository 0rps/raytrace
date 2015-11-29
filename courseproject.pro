#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T19:19:54
#
#-------------------------------------------------

QT       += core gui

TARGET = courseproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AABB.cpp \
    VectorActions.cpp \
    Scene.cpp \
    Primitives.cpp \
    MyVector3.cpp \
    MatrixOperations.cpp \
    Material.cpp \
    LightRay.cpp \
    Intersection.cpp \
    BVHTree.cpp \
    mypicture.cpp \
    tabwidgettools.cpp \
    colorwidget.cpp \
    Checkers.cpp \
    RWObjects.cpp \
    hiform.cpp

HEADERS  += mainwindow.h \
    VectorActions.h \
    Scene.h \
    Primitives.h \
    MyVector3.h \
    MatrixOperations.h \
    Material.h \
    LightRay.h \
    Light.h \
    Intersection.h \
    ConstMaterial.h \
    Constants.h \
    Camera.h \
    BVHTree.h \
    AABB.h \
    mypicture.h \
    tabwidgettools.h \
    colorwidget.h \
    Checkers.h \
    RWObjects.h \
    hiform.h

FORMS    += mainwindow.ui \
    tabwidgettools.ui \
    hiform.ui
