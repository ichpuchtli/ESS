/**
 * @file RRAVRProcessor.cpp
 * @brief a Round Robin processor strategy i.e. fatest possible strategy
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
#include "RRAVRProcessor.h"

#include <QtCore/QDebug>

/**
 * @brief the function to be run upon starting this thread
 */
void RRAVRProcessor::run(){

  if ( !this->avr ){
    qDebug() << "RRAVRProcessor: no firmware loaded exiting run thread\n";
    return;
  }

  emit this->RESET(this->avr);

  avr_reset(this->avr);

  int status = cpu_Running;

  emit this->avrStateChange(status);

  while ( AVRProcessor::avrRunnable( status ) ) {

    status = avr_run(this->avr);

  }

  emit this->avrStateChange(status);

  emit this->finished();

}
