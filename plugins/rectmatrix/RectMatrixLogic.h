#ifndef RECTMATRIXLOGIC_H
#define RECTMATRIXLOGIC_H

#include <QtCore/QObject>

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

class RectMatrixLogic : public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  RectMatrixLogic() {}
  ~RectMatrixLogic() {}

public slots:

  void connect( AVRIOAdapter* io );

  void disconnect();

  void RESET();

signals:

  void error( QString error );

  void setRow( int bitfield );
  void setCol( int bitfield );

private:

  int colCache;
  int rowCache;

};

#endif // RECTMATRIXLOGIC_H
