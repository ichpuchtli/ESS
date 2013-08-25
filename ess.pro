TEMPLATE = app
TARGET = ess

MOC_DIR = bin
OBJECTS_DIR = bin

#INCLUDEPATH += /usr/include/simavr/sim
#LIBS += /usr/lib/libsimavr.a

INCLUDEPATH += include/simavr/simavr/sim
LIBS += include/simavr/simavr/libsimavr.a

LIBS += -lelf

win32: LIBS += -lws2_32

FORMS = src/mainwindow.ui
UI_DIR = src

HEADERS += src/*.h
SOURCES += src/*.cpp

CONFIG += qt5
QT += widgets

RESOURCES += resources.qrc
