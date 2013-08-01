/**
 * \file LEDLogic.cpp
 * \brief a simple LED logic implementation
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
#include "LEDLogic.h"

/**
 * \brief frequency calculations assume a time base in microseconds
 */
static const double ONE_SECOND = 1000000.0f;

void LEDLogic::update( int level, long long time )
{

  if ( lowFrequency ) {
    ( flash = !flash ) ? emit LEDOff( num ) : emit LEDOn( num );
  }

  history[ index ].level = level;
  history[ index ].time = time;

  if ( index == 2 ) {

    double timeHigh;
    double totalTime = double( history[2].time - history[0].time );

    if ( history[0].level ) {
      timeHigh = double( history[1].time - history[0].time );
    } else {
      timeHigh = double( history[2].time - history[1].time );
    }

    dutyCycle = timeHigh / totalTime;

    frequency = ONE_SECOND / totalTime;

    lowFrequency = false;

    if ( dutyCycle > 0.95 ) {

      if ( !on ) {
        emit LEDOn( num );
        on = true;
      }

    } else if ( dutyCycle < 0.05 ) {

      if ( on ) {
        emit LEDOff( num );
        on = false;
      }

    } else if ( frequency >= 30.0 ) {

      if ( !on ) {
        emit LEDOn( num );
        on = true;
      }

    } else if ( frequency < 30.0 ) {
      lowFrequency = true;
    }
  }

  ( index >= 2 ) ? index = 0 : index++;

}
