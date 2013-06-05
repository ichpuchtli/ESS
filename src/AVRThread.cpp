#include <QApplication>

#include <QDebug>

#include "AVRThread.h"

#include <sys/time.h>

#include <stdint.h>

#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"

typedef struct {
  port_t port;
  pin_t  pin;
  char   type;
} PinState_t;

typedef char port_t;
typedef char pin_t;

static AVRThread* class_instance;

void non_mem_irq_handler(struct avr_irq_t* irq, uint32_t value, void* param){

  class_instance->irq_handler(irq,value,param);

}


AVRThread::AVRThread(){

  char* filename = "src/avr/main.axf";

  elf_firmware_t firmware_bin;

  elf_read_firmware(filename, &firmware_bin);

  qDebug() << "AVRThread: firmware " << filename << " freq "
    << firmware_bin.frequency << " mmcu " << firmware_bin.mmcu; 

  this->avr = avr_make_mcu_by_name(firmware_bin.mmcu);

  avr_init(this->avr);

  avr_load_firmware(this->avr, &firmware_bin);

  this->verbose = true;

  this->status = cpu_Running;

  this->connect_irqs();

}

AVRThread::AVRThread(avr_t* avr){

  this->avr = avr;
  
  qDebug() << "AVRThread: freq " << this->avr->frequency << " mmcu " << this->avr->mmcu;

  this->verbose = false;

  this->status = cpu_Running;
}

AVRThread::AVRThread(QString filename){

  elf_firmware_t firmware_bin;

  elf_read_firmware(filename.toLatin1().data(), &firmware_bin);

  qDebug() << "AVRThread: firmware " << filename.toLatin1() << " freq "
    << firmware_bin.frequency << " mmcu " << firmware_bin.mmcu;

  this->avr = avr_make_mcu_by_name(firmware_bin.mmcu);

  avr_init(this->avr);

  avr_load_firmware(this->avr, &firmware_bin);

  this->verbose = false;

  this->status = cpu_Running;

  //this->frequency = 8000000; // 8 MHz
}

AVRThread::AVRThread(QString filename, QString mmcu, unsigned int frequency){

  elf_firmware_t firmware_bin;

  elf_read_firmware(filename.toLatin1(), &firmware_bin);

  firmware_bin.frequency = frequency;

  memcpy(firmware_bin.mmcu, filename.toLatin1(), filename.size() );

  qDebug() << "AVRThread: firmware " << filename.toLatin1() << " freq "
    << firmware_bin.frequency << " mmcu " << firmware_bin.mmcu;

  this->avr = avr_make_mcu_by_name(firmware_bin.mmcu);

  avr_init(this->avr);

  avr_load_firmware(this->avr, &firmware_bin);

  this->verbose = false;

  this->status = cpu_Running;

  //this->frequency = 8000000; // 8 MHz
}

AVRThread::AVRThread(const AVRThread& rhs){}

void AVRThread::loop_delay(long count){

  if( count < 0 ) return;

  //TODO "nop" may not be portable
  while(count--) asm("nop");

}


void AVRThread::irq_handler(struct avr_irq_t* irq, uint32_t value, void* param){

  // Suppress unused variable warnings
  (void) irq;
  (void) value;

  PinState_t* pinState = (PinState_t*) &param;

  //qDebug() << pinState->port << (int)(pinState->pin);

  //emit this->pinChange(pinState->port, pinState->pin);

  // if PortNPin->type == DDR_PORT_TYPE)
    //emit this->ddChange(PortNPin->port, PortNPin->pin);
}

void AVRThread::connect_irqs(void){

  PinState_t pinState;
  void* param;
  struct avr_irq_t* irq;

  class_instance = this;

  for(uint8_t i = 0; i < NUM_AVR_PORTS; i++){

    for(uint8_t pin = 0; pin < 8; pin++){

      // PortF:Pin0 = ('F' << 8 | 0)
      //PortNPin = (PortPin_t) ( (ports[i] << 8) | j );

      // Pray this is packed tight
      pinState.port = AVR_PORT[i];
      pinState.pin = pin;

      memcpy((void*) &param, (void*) &pinState, sizeof(void*));

      irq = avr_io_getirq(this->avr, AVR_IOCTL_IOPORT_GETIRQ(AVR_PORT[i]), pin);

      avr_irq_register_notify(irq, non_mem_irq_handler, param );
    }
  }
}


// Slots
////////////////////////////////////////////////////////////////////////////////

void AVRThread::RESET(void){}

void setFrequency(int frequency){}

void andPort(port_t port, pin_t pin){}
void orPort(port_t port, pin_t pin){}
void xorPort(port_t port, pin_t pin){}

void mutePort(port_t port, pin_t pin){}
void unMutePort(port_t port, pin_t pin){}

void AVRThread::run(void){
  //TODO variable loop speed recalculation instead 1 sec
  //TODO variable loop speep
  //TODO usleep() instead of loop_delay()

  struct timeval t1, t2;

  unsigned int dt = 0;
  unsigned int cycles = 0;
  uint64_t last_cycle_count = 0;

  int cfactor = 0;

  int loop_count = 20;

  gettimeofday(&t1, NULL);

  while ((this->status != cpu_Done) && (this->status != cpu_Crashed)) {

    gettimeofday(&t2, NULL);

    last_cycle_count = avr->cycle;

    this->status = avr_run(this->avr);

    cycles += (unsigned int) (this->avr->cycle - last_cycle_count);

    dt = (t2.tv_sec - t1.tv_sec)*10000 + (t2.tv_usec - t1.tv_usec);

    /* One Second has passed, adjust loop speed */
    if( dt >= 10000 ){

      //cfactor = cycles - this->frequency;
      cfactor = cycles - 80000;

      /* TODO consider log(cfactor) or sqrt(cfactor)*/
      loop_count += cfactor / 655;

      if(loop_count < 0) loop_count = 0;

      if(this->verbose){

        qDebug() << "AVRThread: Loop Count:" << loop_count << "cFactor:"
          << cfactor << "Freq:" << cycles;
      }

      cycles = 0;

      gettimeofday(&t1, NULL);

      QCoreApplication::processEvents();

    }

    AVRThread::loop_delay(loop_count);

  }

}
