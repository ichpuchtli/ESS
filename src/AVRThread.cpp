/**
 * @file AVRThread.cpp
 * @brief avr execution thread handler
 * @author Sam Macpherson
 *
 * Copyright 2013 - Sam Macpherson <sam.mack91@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <QApplication>

#include <QDebug>

#include "AVRThread.h"

#include <sys/time.h>

#include <stdint.h>

#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"

#define AVR_RUNNABLE(status) (status != cpu_Crashed && status != cpu_Done)

/**
 * @brief main contructor
 */
AVRThread::AVRThread(){

    this->frequency = 0;
    this->avr = NULL;

    this->unlimited = false;

}
/**
 * @brief load an avr firmware binary by filname, desired mmcu and frequency
 *
 * @param filename the filename of the firmware binary to load
 * @param mmcu the target avr core (atmega64,atmega128,...)
 * @param frequency the desired frequency of the simulation generally 8MHz
 */
void AVRThread::load(QString filename, QString mmcu, unsigned int frequency){

  this->filename = QString(filename);

  this->mmcu = QString(mmcu);

  this->frequency = frequency;

  elf_read_firmware(filename.toLatin1(), &this->firmware);

  this->firmware.frequency = frequency;

  memcpy(this->firmware.mmcu, mmcu.toLatin1(), mmcu.size() );

  qDebug() << "AVRThread: firmware " << filename.toLatin1() << " freq "
    << frequency << " mmcu " << mmcu.toLatin1();

  this->avr = avr_make_mcu_by_name(mmcu.toLatin1());

  if(!this->avr){
      qDebug() << "AVRThread: possible memory allocation error\n";
      return;
  }

  avr_init(this->avr);

  avr_load_firmware(this->avr, &this->firmware);

  emit this->loaded(this->avr);
}

/**
 * @brief reset the avr state and restart the thread
 */
void AVRThread::restart(){

  if (!this->avr) {
      return;
  }

  emit this->RESET();

  //TODO stop thread
  //TODO free any data that can be safely free'd

  // lock
  avr_reset(this->avr);
  // unlock

  //TODO start thread
}

/**
 * @brief the function to be run upon starting this thread
 */
void AVRThread::run(){


  if ( !this->avr ){
    qDebug() << "AVRThread: no firmware loaded exiting run thread\n";
    return;
  }

  if (this->unlimited){

    this->runUnlimited();

  }else{

    this->runRegulated();

  }

}

/**
 * @brief execuate avr instructions as fast as possible, ie. instructions per second
 */
void AVRThread::runUnlimited(void){

  int status = cpu_Running;

  emit this->avrStateChange(status);

  while ( AVR_RUNNABLE( status ) ) {

    status = avr_run(this->avr);

  }

  emit this->avrStateChange(status);

}

/**
 * @brief execuate avr instructions at desired frequency specified upon loading firmware
 */
void AVRThread::runRegulated(void){

  //TODO variable loop speed recalculation instead 1 sec
  //TODO variable loop speep
  //TODO usleep() instead of loop_delay()

  struct timeval t1, t2;

  unsigned int dt = 0;
  unsigned int cycles = 0;
  uint64_t last_cycle_count = 0;

  int cfactor = 0;

  int loop_count = 20;

  int status = cpu_Running;

  emit this->avrStateChange(status);

  gettimeofday(&t1, NULL);

  while (AVR_RUNNABLE(status)) {

    gettimeofday(&t2, NULL);

    last_cycle_count = avr->cycle;

    status = avr_run(this->avr);

    cycles += (unsigned int) (this->avr->cycle - last_cycle_count);

    dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

    /* One Second has passed, adjust loop speed */
    if( dt >= 1000000 ){

      //cfactor = cycles - this->frequency;
      cfactor = cycles - 8000000;

      /* TODO consider log(cfactor) or sqrt(cfactor)*/
      loop_count += cfactor >> 18;

      if(loop_count < 0) loop_count = 0;

      qDebug() << "AVRThread: Loop Count:" << loop_count << "cFactor:" << (cfactor >> 18) << "Freq:" << cycles;

      cycles = 0;

      gettimeofday(&t1, NULL);

    }

    AVRThread::loop_delay((unsigned int) loop_count);

  }

  emit this->avrStateChange(status);

}

/**
 * @brief simple loop delay (spin delay, spin couter, etc)
 *
 * @param count the number of "nop" to execute, to create a significat delay
 */
void AVRThread::loop_delay(unsigned int count){

  while(count--) asm("nop");

}
