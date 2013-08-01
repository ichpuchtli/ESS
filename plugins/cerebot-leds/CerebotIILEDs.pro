######################################################################
# CerebtII LEDs Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(CerebotIILEDs)
DESTDIR = ..

HEADERS += factory.h CerebotIILEDWidget.h CerebotIILEDLogic.h ../utils/LEDLogic.h

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AbstractPeripheralWidget.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h

SOURCES = CerebotIILEDWidget.cpp CerebotIILEDLogic.cpp ../utils/LEDLogic.cpp

CONFIG  += plugin qt5
QT      += widgets
