#include "RectMatrixLogic.h"

#include <QtCore/QDebug>
#include <sys/time.h>

#define ROW_PORT      'G'
#define ROW_MASK      0x07

#define COL_PORT_LOW  'A'
#define COL_MASK_LOW  0xFF

#define COL_PORT_HIGH 'C'
#define COL_MASK_HIGH  0x7F

typedef char port_t;
typedef char pin_t;

enum {
  DDR_PORT,
  OUT_PORT
};

struct callbackdata_t {

  RectMatrixLogic* instance;

  char port;

  char pin;

};

RectMatrixLogic::RectMatrixLogic() {

  this->avr = NULL;

  this->init();

}

void RectMatrixLogic::init(void){

  this->colCache = 0;
  this->rowCache = 0;

}

void RectMatrixLogic::attach(avr_t* avr){

  this->avr = avr;

  avr_irq_t* irq;

  struct callbackdata_t* data;

  for ( uint8_t i = 0; i < 8; i++ ) {

    if ( ROW_MASK & ( 1 << i ) ){

      data = new struct callbackdata_t;
      data->instance = this;
      data->port = ROW_PORT;
      data->pin = i;

      irq = avr_io_getirq(this->avr, AVR_IOCTL_IOPORT_GETIRQ(ROW_PORT), i);

      avr_irq_register_notify(irq, RectMatrixLogic::pin_change_hook, data );
    }

  }

  for ( uint8_t i = 0; i < 8; i++ ) {

    if ( COL_MASK_LOW & ( 1 << i ) ){

      data = new struct callbackdata_t;
      data->instance = this;
      data->port = COL_PORT_LOW;
      data->pin = i;

      irq = avr_io_getirq(this->avr, AVR_IOCTL_IOPORT_GETIRQ(COL_PORT_LOW), i);

      avr_irq_register_notify(irq, RectMatrixLogic::pin_change_hook, data );
    }

  }

  for ( uint8_t i = 0; i < 8; i++ ) {

    if ( COL_MASK_HIGH & ( 1 << i ) ){

      data = new struct callbackdata_t;
      data->instance = this;
      data->port = COL_PORT_HIGH;
      data->pin = i;

      irq = avr_io_getirq(this->avr, AVR_IOCTL_IOPORT_GETIRQ(COL_PORT_HIGH), i);

      avr_irq_register_notify(irq, RectMatrixLogic::pin_change_hook, data );
    }

  }
}

void RectMatrixLogic::pin_change_hook( struct avr_irq_t* irq, uint32_t value, void* param ){

  struct callbackdata_t* data = ( struct callbackdata_t* ) param;

  if ( data->port == ROW_PORT ){

    data->instance->rowCache ^= ( 1 << data->pin );
    emit data->instance->setRow( data->instance->rowCache );

  }

  if ( data->port == COL_PORT_LOW ){

    data->instance->colCache ^= ( 1 << data->pin );
    emit data->instance->setCol( data->instance->colCache );

  }

  if ( data->port == COL_PORT_HIGH ){

    data->instance->colCache ^= ( 1 << ( data->pin + 8 ));
    emit data->instance->setCol( data->instance->colCache );

  }

}
