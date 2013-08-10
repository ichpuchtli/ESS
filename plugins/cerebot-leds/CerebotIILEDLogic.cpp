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

#define LED_PORT ('E')

#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7

CerebotIILEDLogic::CerebotIILEDLogic()
{
}

CerebotIILEDLogic::~CerebotIILEDLogic()
{
}

void CerebotIILEDLogic::attach( AVRIOAdapter* io )
{

  for ( int i = 0; i < 4; i++ ) {

    leds[i] = new PolledLEDLogic( i, &io->getGPIOPin( LED_PORT, i + LED1 ) );

    connect( leds[i], SIGNAL( LEDOff( int ) ), this, SIGNAL( turnOffLED( int ) ) );
    connect( leds[i], SIGNAL( LEDOn( int ) ), this, SIGNAL( turnOnLED( int ) ) );

  }
}

void CerebotIILEDLogic::detach()
{

  for ( int i = 0; i < 4; i++ ) {

    leds[i]->stopPolling();

    disconnect( leds[ i ] );

    delete leds[i];

  }

}

void CerebotIILEDLogic::RESET()
{

  for ( int i = 0; i < 4; i++ ) {

    leds[i]->stopPolling();

    leds[i]->startPolling();

  }

}
