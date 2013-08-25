######################################################################
# CerebtII LEDs Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(oscilloscope1ch)
DESTDIR = ..

HEADERS += factory.h OscilloscopeLogic.h OscilloscopeWidget.h

HEADERS += \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AVRIOAdapter.h \
    ../../src/AbstractAVRProcessor.h \
    include/qcustomplot/qcustomplot.h

SOURCES = OscilloscopeWidget.cpp OscilloscopeLogic.cpp include/qcustomplot/qcustomplot.cpp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG  += plugin qt5
