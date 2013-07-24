/**
 * \file RRAVRProcessor.cpp
 * \brief a simple Round Robin simulation strategy
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
#include "RRAVRProcessor.h"
#include <QtCore/QThread>

#include <QtCore/QDebug>

void RRAVRProcessor::run()
{

  emit this->RESET();

  avr_reset( this->avr );

  int status = cpu_Running;

  emit this->avrStateChange( status );

  this->isRunning = true;

  qDebug() << "RRAVRProcessor: running";

  while ( AVRProcessor::avrRunnable( status ) ) {

    status = avr_run( this->avr );
  }

  qDebug() << "RRAVRProcessor: stopped";

  emit this->avrStateChange( status );

  emit this->stopped();

}
