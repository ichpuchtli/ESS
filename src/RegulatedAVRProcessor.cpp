/**
 * \file RegulatedAVRProcessor.cpp
 * \brief a processor strategy using loop delays to achieve accurate speeds
 * \author Sam Macpherson
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "RegulatedAVRProcessor.h"

#include <QtCore/QDebug>

#include <sys/time.h>
#include "math.h"

#include <stdint.h>

void RegulatedAVRProcessor::run(){

  struct timeval t1, t2;

  unsigned int dt = 0;
  unsigned int cycles = 0;
  uint64_t last_cycle_count = 0;

  int cfactor = 0;

  int loop_count = 100;

  unsigned int updateSpeed = 4; // 4 Hz

  if ( !this->avr ){
    qDebug() << "RegulatedAVRProcessor: no firmware loaded exiting run thread\n";
    return;
  }

  emit this->RESET(this->avr);

  avr_reset(this->avr);

  int status = cpu_Running;

  emit this->avrStateChange(status);

  gettimeofday(&t1, NULL);

  while (AVRProcessor::avrRunnable(status)) {

    gettimeofday(&t2, NULL);

    last_cycle_count = avr->cycle;

    status = avr_run(this->avr);

    cycles += (unsigned int) (this->avr->cycle - last_cycle_count);

    dt = (t2.tv_sec - t1.tv_sec)*1000000U + (t2.tv_usec - t1.tv_usec);

    /* One Second has passed, adjust loop speed */
    if( dt >= 1000000U/updateSpeed ){

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

      qDebug() << "RegulatedAVRProcessor: Loop Count:" << loop_count << "Freq:" << updateSpeed*cycles << "MHz";

      cycles = 0;

      gettimeofday(&t1, NULL);

    }

    RegulatedAVRProcessor::loop_delay((unsigned int) loop_count);

  }

  emit this->avrStateChange(status);

  emit this->finished();

}
