######################################################################
# Pmod Seven Segment Display Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pmodsevenseg)
DESTDIR = ..

HEADERS += factory.h PmodSevenSegWidget.h PmodSevenSegLogic.h

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h

SOURCES = PmodSevenSegWidget.cpp PmodSevenSegLogic.cpp

CONFIG  += plugin qt5
QT      += widgets
