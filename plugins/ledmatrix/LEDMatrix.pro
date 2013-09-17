######################################################################
# 15x7 LED Matrix Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(ledmatrix)
DESTDIR = ..

HEADERS += factory.h LEDMatrixWidget.h LEDMatrixLogic.h

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h

SOURCES = LEDMatrixWidget.cpp LEDMatrixLogic.cpp

QMAKE_CXXFLAGS += -std=c++0x

CONFIG  += plugin qt5
QT      += widgets
