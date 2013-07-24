#include "matrixfactory.h"

#include "RectMatrixLogic.h"
#include "RectMatrix.h"

Peripheral MatrixFactory::getPeripheral()
{

  RectMatrixLogic* logic = new RectMatrixLogic();

  RectMatrix* widget = new RectMatrix( 20 );

  Peripheral periph = { logic, widget };

  connect( logic, &RectMatrixLogic::setCol, widget, &RectMatrix::setCol );
  connect( logic, &RectMatrixLogic::setRow, widget, &RectMatrix::setRow );

  return periph;

}
