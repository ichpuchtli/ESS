TEMPLATE = app
TARGET = ess

MOC_DIR = bin
OBJECTS_DIR = bin

# link against existing simavr installation
#INCLUDEPATH += /usr/include/simavr/sim
#LIBS += /usr/lib/libsimavr.a

# link against local simavr
INCLUDEPATH += include/simavr/simavr/sim
LIBS += include/simavr/simavr/libsimavr.a

# Windows and Linux
win32|linux-g++: LIBS += -lelf

# Homebrew's libelf
macx-clang: LIBS += /usr/local/lib/libelf.a

win32: LIBS += -lws2_32

FORMS = src/mainwindow.ui
UI_DIR = src

HEADERS += src/*.h
SOURCES += src/*.cpp

CONFIG += qt5
macx-clang: CONFIG += app_bundle

QT += widgets

RESOURCES += resources.qrc
