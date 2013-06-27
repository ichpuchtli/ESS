/**
 * @file AVRProcessor.cpp
 * @brief avr execution thread handler
 * @author Sam Macpherson
 *
 * Copyright 2013  Sam Macpherson <sam.mack91@gmail.com>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets/QApplication>

#include <QtCore/QDebug>

#include "AVRProcessor.h"

#include <sys/time.h>
#include "math.h"

#include <stdint.h>

#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"

#define AVR_RUNNABLE(status) (status != cpu_Crashed && status != cpu_Done)

/**
 * @brief main constructor
 */
AVRProcessor::AVRProcessor(){

   /*
   * do no allocate any heap objects here since thread affinity will be
   * determined after object is initiated
   */

  this->frequency = 0;
  this->avr = NULL;

  this->unlimited = false;

}

AVRProcessor::~AVRProcessor(){

  if(this->avr){

    free(this->avr);
  }

}

/**
 * @brief load an avr firmware binary by filename, desired mmcu and frequency
 *
 * @param filename the filename of the firmware binary to load
 * @param mmcu the target avr core (atmega64,atmega128,...)
 * @param frequency the desired frequency of the simulation generally 8MHz
 */
void AVRProcessor::load(QString filename, QString mmcu, unsigned int frequency){

  this->filename = QString(filename);

  this->mmcu = QString(mmcu);

  this->frequency = frequency;

  elf_read_firmware(filename.toLatin1(), &this->firmware);

  this->firmware.frequency = frequency;

  memcpy(this->firmware.mmcu, mmcu.toLatin1(), mmcu.size() );

  qDebug() << "AVRProcessor: firmware " << filename.toLatin1() << " freq "
    << frequency << " mmcu " << mmcu.toLatin1();

  this->avr = avr_make_mcu_by_name(mmcu.toLatin1());

  if(!this->avr){
      qDebug() << "AVRProcessor: possible memory allocation error\n";
      return;
  }

  avr_init(this->avr);

  avr_load_firmware(this->avr, &this->firmware);

  fflush(stdout);

  emit this->loaded(this->avr);
}

/**
 * @brief the function to be run upon starting this thread
 */
void AVRProcessor::run(){

  if ( !this->avr ){
    qDebug() << "AVRProcessor: no firmware loaded exiting run thread\n";
    return;
  }

  avr_reset(this->avr);

  emit this->RESET();

  if (this->unlimited){

    this->runUnlimited();

  }else{

    this->runRegulated();

  }

  emit this->finished();

}

/**
 * @brief execute avr instructions as fast as possible, ie. instructions per second
 */
void AVRProcessor::runUnlimited(void){

  int status = cpu_Running;

  emit this->avrStateChange(status);

  while ( AVR_RUNNABLE( status ) ) {

    status = avr_run(this->avr);

  }

  emit this->avrStateChange(status);

}

/**
 * @brief execute avr instructions at desired frequency specified upon loading firmware
 */
void AVRProcessor::runRegulated(void){

  struct timeval t1, t2;

  unsigned int dt = 0;
  unsigned int cycles = 0;
  uint64_t last_cycle_count = 0;

  int cfactor = 0;

  int loop_count = 100;

  int status = cpu_Running;

  int updateSpeed = 1; // 4 Hz

  emit this->avrStateChange(status);

  gettimeofday(&t1, NULL);

  while (AVR_RUNNABLE(status)) {

    gettimeofday(&t2, NULL);

    last_cycle_count = avr->cycle;

    status = avr_run(this->avr);

    cycles += (unsigned int) (this->avr->cycle - last_cycle_count);

    dt = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec);

    /* One Second has passed, adjust loop speed */
    if( dt >= 1000000/updateSpeed ){

      // correction factor to apply to loop delay
      cfactor = cycles - this->frequency/updateSpeed;

      // divide here to depreciate smaller errors
      cfactor /= ((float)this->frequency/1024);

      if(cfactor < 0 ){
        loop_count -= log(abs(cfactor));
      } else if (cfactor > 0 ) {
        loop_count += log(cfactor);
      }

      if(loop_count < 0) loop_count = 0;

      qDebug() << "AVRProcessor: Loop Count:" << loop_count << "Freq:" << updateSpeed*cycles << "MHz";

      cycles = 0;

      gettimeofday(&t1, NULL);

    }

    AVRProcessor::loop_delay((unsigned int) loop_count);

  }

  emit this->avrStateChange(status);

}

/**
 * @brief simple loop delay (spin delay, spin counter, etc)
 *
 * @param count the number of "nop" to execute, to create a significant delay
 */
inline void AVRProcessor::loop_delay(unsigned int count){

  while(count--) asm("nop");

}
