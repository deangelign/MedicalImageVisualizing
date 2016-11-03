#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T13:35:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWorld
TEMPLATE = app

#QMAKE_CXXFLAGS_RELEASE = -O1 -g

SOURCES += main.cpp\
        mainwindow.cpp \
    spectrum.cpp \
    linear.cpp \
    kernel.cpp \
    image.cpp \
    gqueue.cpp \
    comptime.cpp \
    common.cpp \
    adjacency.cpp \
    slicer.cpp \
    displaymanager.cpp \
    eventmanager.cpp \
    brightcontrastdialog.cpp \
    atlas.cpp \
    iftMatrix.cpp \
    refactformdialog.cpp \
    createvolumedialogform.cpp

HEADERS  += mainwindow.h \
    spectrum.h \
    mc920.h \
    linear.h \
    kernel.h \
    image.h \
    comptime.h \
    common.h \
    adjacency.h \
    gqueue.h \
    slicer.h \
    displaymanager.h \
    eventmanager.h \
    brightcontrastdialog.h \
    atlas.h \
    iftMatrix.h \
    matrixfeia.h \
    refactformdialog.h \
    createvolumedialogform.h

FORMS    += mainwindow.ui \
    brightcontrastdialog.ui \
    refactformdialog.ui \
    createvolumedialogform.ui

unix:!macx: LIBS += -lpng
#-fsanitize=address

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/lapack/release/ -llapack
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/lapack/debug/ -llapack
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/lapack/ -llapack

INCLUDEPATH += $$PWD/../../../../../usr/lib/lapack
DEPENDPATH += $$PWD/../../../../../usr/lib/lapack

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/lapack/release/liblapack.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/lapack/debug/liblapack.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/lapack/release/lapack.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/lapack/debug/lapack.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/lapack/liblapack.a

unix|win32: LIBS += -llapack

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/libblas/release/ -lblas
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/libblas/debug/ -lblas
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/libblas/ -lblas

INCLUDEPATH += $$PWD/../../../../../usr/lib/libblas
DEPENDPATH += $$PWD/../../../../../usr/lib/libblas

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/libblas/release/libblas.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/libblas/debug/libblas.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/libblas/release/blas.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/libblas/debug/blas.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/libblas/libblas.a
