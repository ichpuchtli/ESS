######################################################################
# Matrix Plugin
######################################################################

TEMPLATE = lib
TARGET   = $$qtLibraryTarget(matrixfactory)
DESTDIR = .

HEADERS = RectMatrix.h \
    matrixfactory.h \
    RectMatrixLogic.h \
    RectMatrix.h \
    ../../src/AbstractPeripheralFactory.h \
    ../../src/AbstractPin.h \
    ../../src/AbstractPeripheralLogic.h \
    ../../src/AbstractPeripheralWidget.h \
    ../../src/AbstractPinFactory.h \
    ../../src/AbstractAVRProcessor.h
SOURCES = RectMatrix.cpp \
    matrixfactory.cpp \
    RectMatrixLogic.cpp
    RectMatrix.cpp

CONFIG  += plugin qt5 debug
QT      += widgets
