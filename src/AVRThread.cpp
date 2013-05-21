#include <QApplication>

#include <QDebug>

#include "AVRThread.h"

#include <sys/time.h>
#include <stdint.h>

AVRThread::AVRThread(){

  char* filename = "src/avr/main.axf";

  elf_firmware_t firmware_bin;

  elf_read_firmware(filename, &firmware_bin);

  qDebug() << "AVRThread: firmware " << filename << " freq "
    << firmware_bin.frequency << " mmcu " << firmware_bin.mmcu; 

  this->avr = avr_make_mcu_by_name(firmware_bin.mmcu);

  avr_init(this->avr);

  avr_load_firmware(this->avr, &firmware_bin);

  this->verbose = false;

  this->status = cpu_Running;
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
}

void AVRThread::loop_delay(long count){

  if( count < 0 ) return;

  while(count--) asm("nop");

}

avr_t* AVRThread::getAVR(void){
  return this->avr;
}

void AVRThread::RESET(void){}

void AVRThread::run(void){

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

    dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

    /* One Second has passed, adjust loop speed */
    if( dt >= 1000000 ){

      cfactor = cycles - 8000000;

      /* TODO consider log(cfactor) or sqrt(cfactor)*/
      loop_count += cfactor / 65536; 

      if(loop_count < 0) loop_count = 0;

      if(verbose){

        qDebug() << "AVRThread: Loop Count:" << loop_count << "cFactor:"
          << cfactor << "Freq:" << cycles;
      }

      cycles = 0;

      gettimeofday(&t1, NULL);

    }

    AVRThread::loop_delay(loop_count);

  }

}
