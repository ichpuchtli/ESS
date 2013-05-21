#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QDebug>
#include <QPainter>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"

#include "RectMatrix.h"
#include "AVRThread.h"

#define ROW_PORT      'G'
#define ROW_MASK      0x07

#define COL_PORT_LOW  'A'
#define COL_MASK_LOW  0xFF

#define COL_PORT_HIGH 'C'
#define COL_MASK_HIGH  0x7F

int rowBitVector = 0x0;
int colBitVector = 0x0;

RectMatrix* g_Matrix;
avr_t* g_AVR;

void timer0_hook(struct avr_irq_t* irq, uint32_t value, void* param){

  static struct timeval t1, t2;
  static unsigned long count = 0;
  long long dt = 0;

  gettimeofday(&t2, NULL);

  dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

  fprintf(stderr, "Timer0 Interrupt: Period: %dms, Count: %d\r\n", dt/1000, count++);

  gettimeofday(&t1, NULL);
}

void timer1_hook(struct avr_irq_t* irq, uint32_t value, void* param){

  static struct timeval t1, t2;
  static unsigned long count = 0;
  long long dt = 0;

  gettimeofday(&t2, NULL);

  dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

  fprintf(stderr, "Timer1 Interrupt: Period: %dms, Count: %d\r\n", dt/1000, count++);

  gettimeofday(&t1, NULL);
}

void timer2_hook(struct avr_irq_t* irq, uint32_t value, void* param){

  static struct timeval t1, t2;
  static unsigned long count = 0;
  long long dt = 0;

  gettimeofday(&t2, NULL);

  dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

  fprintf(stderr, "Timer2 Interrupt: Period: %dms, Count: %d\r\n", dt/1000, count++);

  gettimeofday(&t1, NULL);
}

void update_matrix(void){

  // TODO qt signals/slots mechanisms need to be used here 
  // e.g. emit updateDisplaySet(row,col)

  g_Matrix->clearAll();

  int row = rowBitVector & 7;

  for(int i = 0; i < LM_NUM_COLS; i++){

    if( colBitVector & (1 << i) ){
      g_Matrix->set(row,i);
    }

  }

}

void matrix_col_change_hook(struct avr_irq_t* irq, uint32_t value, void* param){

  (void)(irq);
  (void)(value);

  long i = (long) param;

  colBitVector ^= (1 << i);

  update_matrix();

 // qDebug() << "Col Port Change:" << i;

}

void matrix_row_change_hook(struct avr_irq_t* irq, uint32_t value, void* param){

  (void)(irq);
  (void)(value);

  long i = (long) param;

  rowBitVector ^= (1 << i);

  update_matrix();

//  qDebug() << "Row Port Change:" << (rowBitVector & 7);

}

void chain_irq_hooks(avr_t* avr){

  for(uint8_t i = 0; i < 8; i++){

    if( ROW_MASK & (1 << i))
      avr_irq_register_notify(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(ROW_PORT), i), matrix_row_change_hook, (void*) (long) i);

    if( COL_MASK_LOW & (1 << i))
      avr_irq_register_notify(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(COL_PORT_LOW), i), matrix_col_change_hook, (void*) (long) i);

    if( COL_MASK_HIGH & (1 << i))
      avr_irq_register_notify(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(COL_PORT_HIGH), i), matrix_col_change_hook, (void*) (long) (i + 8) );

  }

}

int main(int argc, char** argv){

  QApplication app(argc, argv);
  
  AVRThread avr_worker;

  g_AVR = avr_worker.getAVR();

  RectMatrix MatrixWidget(20);

  g_Matrix = &MatrixWidget;
  
  MatrixWidget.show();

  g_Matrix->set(0,0);

  chain_irq_hooks(avr_worker.getAVR());

  //avr_irq_register_notify(avr_io_getirq(g_AVR, AVR_IOCTL_IOPORT_GETIRQ('F'), 1), timer0_hook, NULL);
  //avr_irq_register_notify(avr_io_getirq(g_AVR, AVR_IOCTL_IOPORT_GETIRQ('F'), 2), timer1_hook, NULL);

  avr_worker.start();

  return app.exec();
  
}
