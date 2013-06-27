#ifndef RECTMATRIXLOGIC_H
#define RECTMATRIXLOGIC_H

#include <QtCore/QObject>

#include "sim_avr.h"

#include "avr_ioport.h"
#include "sim_irq.h"

class RectMatrixLogic : public QObject {

  Q_OBJECT

public:
  RectMatrixLogic();
  int colCache;
  int rowCache;

public slots:

  void attach(avr_t* avr);

  void init(void);

signals:

  void setRow(int bitfield);
  void setCol(int bitfield);

private:

  static void pin_change_hook(struct avr_irq_t* irq, uint32_t value, void* param);

  avr_t* avr;

};

#endif // RECTMATRIXLOGIC_H
