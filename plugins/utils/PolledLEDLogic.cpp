/**
 * \file PolledLEDLogic.cpp
 * \brief a simple polled LED logic implementation
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

#include "PolledLEDLogic.h"

PolledLEDLogic::PolledLEDLogic( int num, AbstractPin* pin ) :  num( num ),
  pin( pin ), timer( new QTimer( this ) ), lowFrequency( true ),
  dutyCycle( 0.0f ), frequency( 0.0f ), index( 0 )
{
  connect( timer, SIGNAL( timeout() ), this, SLOT( poll() ) );
}

PolledLEDLogic::~PolledLEDLogic()
{

  stopPolling();

  delete timer;

}

void PolledLEDLogic::startPolling()
{
  timer->start( POLL_PERIOD );
}

void PolledLEDLogic::stopPolling()
{
  timer->stop();
}

void PolledLEDLogic::poll()
{

  int level = pin->getLevel();

  if ( lowFrequency ) {
    ( level ) ? emit LEDOn( num ) : emit LEDOff( num );
  }

  history[index] = ( level == 1 );

  if ( index == ( HISTORY_SIZE - 1 ) ) {
    updateCache();
  }

  // Advance index
  index = ( index + 1 ) & ( HISTORY_SIZE - 1 );

}

void PolledLEDLogic::updateCache()
{

  int highs = 1;

  for ( int i = 0; i < HISTORY_SIZE; i++ ) {
    if ( history[i] ) {
      highs++;
    }
  }

  double dutyCycle = double( highs ) / double( HISTORY_SIZE );

  if ( dutyCycle < 0.05 ) {
    emit LEDOff( num );
    lowFrequency = false;
    return;
  }

  if ( dutyCycle > 0.95 ) {
    emit LEDOn( num );
    lowFrequency = false;
    return;
  }

  // Find first rising/falling edge
  int firstEdge = this->findNearestEdge( 0 );

  if ( firstEdge == 0 ) { // No Edge in this window!
    lowFrequency = true;
    return;
  }

  int nextEdge;

  if ( history[firstEdge] ) { // Rising Edge
    nextEdge = findRisingEdge( firstEdge );
  } else { // Falling Edge
    nextEdge = findFallingEdge( firstEdge );
  }

  if ( nextEdge == 0 ) { // No recurring Edge in this window!
    lowFrequency = true;
    return;
  }

  double frequency = 1000.0 / ( double( nextEdge - firstEdge ) * POLL_PERIOD );

  if ( frequency > FREQUENCY_THRESHOLD ) {
    emit LEDOn( num );
    lowFrequency = false;
  } else {
    lowFrequency = true;
  }

}

int PolledLEDLogic::findNearestEdge( int offset )
{

  bool last = history[offset];

  for ( int i = offset; i < ( HISTORY_SIZE - offset ); i++ ) {

    if ( ( !last && history[i] ) || ( last && !history[i] ) ) {
      return i;
    }
  }

  return 0;
}

int PolledLEDLogic::findRisingEdge( int offset )
{

  bool last = history[offset];

  for ( int i = offset; i < ( HISTORY_SIZE - offset ); i++ ) {

    if ( !last && history[i] ) { // Rising Edge
      return i;
    }

    last = history[i];
  }

  return 0;
}

int PolledLEDLogic::findFallingEdge( int offset )
{

  bool last = history[offset];

  for ( int i = offset; i < ( HISTORY_SIZE - offset ); i++ ) {

    if ( last && !history[i] ) { // Falling Edge
      return i;
    }

    last = history[i];
  }

  return 0;

}
