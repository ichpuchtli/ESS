######################################################################
# Pmod Push Buttons Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(pmodpushbuttons)
DESTDIR = ..

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h \

HEADERS += factory.h PmodPushButtonLogic.h PmodPushButtonWidget.h

SOURCES = PmodPushButtonLogic.cpp PmodPushButtonWidget.cpp

CONFIG  += plugin qt5
QT      += widgets
