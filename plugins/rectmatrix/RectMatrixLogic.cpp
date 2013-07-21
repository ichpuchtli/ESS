#include "RectMatrixLogic.h"

#include "RectMatrix.h"

void RectMatrixLogic::connect(AbstractPinFactory* pins){

  QObject::connect(&pins->getGPIOPin('A',0), &AbstractPin::levelChange, this, &RectMatrixLogic::setCol);

}

void RectMatrixLogic::connect(avr_t* avr){}

void RectMatrixLogic::disconnect(){}

void RectMatrixLogic::RESET(){}
