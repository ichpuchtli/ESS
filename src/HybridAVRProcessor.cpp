/**
 * \file HybridAVRProcessor.cpp
 * \brief A simulation stategy using bundled execuation at frequent intervals
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
#include "HybridAVRProcessor.h"

#include <QtCore/QDebug>

/**
 * \def UPDATE_FREQUENCY
 * the frequency to process a batch of avr operations in milliseconds
 */
#define UPDATE_FREQUENCY 10

void HybridAVRProcessor::run()
{

  this->timer = new QTimer( this );

  QObject::connect( this->timer, &QTimer::timeout, this,
                    &HybridAVRProcessor::update );

  emit this->RESET();

  avr_reset( this->avr );

  emit this->avrStateChange( cpu_Running );

  timer->start( UPDATE_FREQUENCY );
}

/**
 * \brief method tied to timer to process bulk avr cycles
 */
void HybridAVRProcessor::update( void )
{

  static int status = cpu_Running;

  unsigned long new_cycles = this->avr->cycle + this->frequency /
                             ( 1000 / UPDATE_FREQUENCY );

  while ( isRunning && avrRunnable( status )
          && ( this->avr->cycle < new_cycles ) ) {

    status = avr_run( this->avr );

  }


  if ( !avrRunnable( status ) ) {

    emit this->avrStateChange( status );

    this->timer->stop();

    free( this->timer );

    emit this->stopped();

  }

}
