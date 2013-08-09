######################################################################
# Pmod Push Buttons Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(PmodPushButtons)
DESTDIR = ..

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h \

HEADERS += factory.h PmodPushButtonLogic.h

SOURCES = PmodPushButtonLogic.cpp

QMAKE_CXXFLAGS += -std=c++0x

CONFIG  += plugin qt5
QT      += widgets
