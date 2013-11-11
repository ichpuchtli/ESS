######################################################################
# CerebtII LEDs Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(cerebotleds)
DESTDIR = ..

HEADERS += factory.h CerebotIILEDWidget.h CerebotIILEDLogic.h ../utils/PolledLEDLogic.h

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h

SOURCES = CerebotIILEDWidget.cpp CerebotIILEDLogic.cpp ../utils/PolledLEDLogic.cpp

CONFIG  += plugin qt5
QT      += widgets
