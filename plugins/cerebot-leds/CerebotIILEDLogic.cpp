/**
 * \file CerebotIILEDLogic.cpp
 * \brief The logic implementation for the cerebotII onboard led's
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
#include "CerebotIILEDLogic.h"

#include <sys/time.h>

#define LED_PORT ('E')

#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7

CerebotIILEDLogic::CerebotIILEDLogic()
{
  for ( int i = 0; i < 4; i++ ) {
    leds[i] = new LEDLogic( i );
  }
}

CerebotIILEDLogic::~CerebotIILEDLogic()
{
  for ( int i = 0; i < 4; i++ ) {
    delete leds[i];
  }
}

void CerebotIILEDLogic::connect( AVRIOAdapter* io )
{

  for ( int i = LED1; i <= LED4; i++ ) {

    // Connect our signal router to appropriate IO pin signals
    QObject::connect( &io->getGPIOPin( LED_PORT, i ), &AbstractPin::levelChange,
                      this, &CerebotIILEDLogic::router );

    // Echo internal LEDLogic signals to allow logic -> widget connections
    QObject::connect( leds[i - LED1], &LEDLogic::LEDOn, this,
                      &CerebotIILEDLogic::turnOnLED );
    QObject::connect( leds[i - LED1], &LEDLogic::LEDOff, this,
                      &CerebotIILEDLogic::turnOffLED );
  }

  this->io = io;
}

void CerebotIILEDLogic::disconnect()
{

  for ( int i = LED1; i <= LED4; i++ ) {

    // Disconnect the router from gpio pins
    QObject::disconnect( &this->io->getGPIOPin( LED_PORT, i ), 0, this, 0 );

    // Disconnect the LEDLogic signals from this Logic signals
    QObject::disconnect( this->leds[i - LED1], 0, this, 0 );

  }

}

void CerebotIILEDLogic::RESET() {}

void CerebotIILEDLogic::router( int voltage, char port, char pin )
{

  ( void ) port;

  long long now;

  struct timeval t;

  // TODO use avr cycles for time base
  gettimeofday( &t, NULL );

  now = t.tv_sec * 1000000U + t.tv_usec;

  this->leds[ pin - LED1 ]->update( voltage, now );

}
