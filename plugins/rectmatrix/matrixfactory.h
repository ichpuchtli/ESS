#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H

#include <QtCore/QtPlugin>

#include "../../src/AbstractPeripheralFactory.h"

class MatrixFactory : public AbstractPeripheralFactory
{

  Q_OBJECT

  Q_PLUGIN_METADATA( IID "15x7 LED Matrix" )

  Q_INTERFACES( AbstractPeripheralFactory )

public:

  MatrixFactory() {}
  ~MatrixFactory() {}

  Peripheral getPeripheral( void );

  QString getDescription( void ) {
    return QString( "15x7 LED Matrix" );
  }

  QString getVersion( void ) {
    return QString( "1.0" );
  }

};

#endif
