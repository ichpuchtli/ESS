#include "RectMatrixLogic.h"

#include "RectMatrix.h"

void RectMatrixLogic::connect(AVRIOAdapter* io){

  QObject::connect(&io->getGPIOPin('A',0), &AbstractPin::levelChange, this, &RectMatrixLogic::setCol);

}

void RectMatrixLogic::disconnect(){}

void RectMatrixLogic::RESET(){}
