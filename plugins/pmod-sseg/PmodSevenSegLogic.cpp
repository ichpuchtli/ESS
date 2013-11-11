/**
 * \file PmodSevenSegLogic.cpp
 * \brief The logic implementation for the pmod seven segment display
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
#include "PmodSevenSegLogic.h"

#include <QtCore/QRegularExpression>

#define POLL_PERIOD 10

static uint8_t getMode( uint8_t list[], int length, int max )
{

  int freq[128] = {0};

  for ( int i = 0; i < length; i++ ) {
    ++freq[list[i]];
  }

  uint8_t mode = 0;

  for ( int i = 0; i < max; i++ ) {
    if ( freq[i] > mode ) {
      mode = i;
    }
  }

  return mode;
}

PmodSevenSegLogic::PmodSevenSegLogic() : timer( new QTimer( this ) ),
  index1( 0 ), index2( 0 )
{

  memset( ( void* ) pins, 0, 8 * sizeof( void* ) );
  memset( ( void* ) history1, '\0', 5 * sizeof( uint8_t ) );
  memset( ( void* ) history2, '\0', 5 * sizeof( uint8_t ) );

  nets << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "CAT";

  connect( timer, SIGNAL( timeout() ), this, SLOT( poll() ) );
}

void PmodSevenSegLogic::poll()
{

  int a = pins[0] ? pins[0]->getLevel() : 0;
  int b = pins[1] ? pins[1]->getLevel() : 0;
  int c = pins[2] ? pins[2]->getLevel() : 0;
  int d = pins[3] ? pins[3]->getLevel() : 0;
  int e = pins[4] ? pins[4]->getLevel() : 0;
  int f = pins[5] ? pins[5]->getLevel() : 0;
  int g = pins[6] ? pins[6]->getLevel() : 0;
  int cat = pins[7] ? pins[7]->getLevel() : 0;

  uint8_t code = d << 6 | c << 5 | b << 4 | a << 3 | g << 2 | f << 1 | e;

  if ( cat == 1 ) {

    history1[index1++ & 3] = code;

    uint8_t mode = getMode( history1, 4, 128 );

    if ( history1[4] != mode ) {
      emit segmentChange( ( int )( 0x80 | mode ) );
    }

    history1[4] = mode;

  } else {

    history2[index2++ & 3] = code;

    uint8_t mode = getMode( history2, 4, 128 );

    if ( history2[4] != mode ) {
      emit segmentChange( ( int ) mode );
    }

    history2[4] = mode;
  }

}

void PmodSevenSegLogic::connectNet( QString net, QString pin )
{

  char port = pin.toLatin1()[1];
  unsigned char pin_num = pin.toLatin1()[2] - '0';

  int index = nets.indexOf( QRegularExpression( net ) );

  if ( index >= 0 && index <= 7 ) {
    pins[index] = &io->getGPIOPin( port, pin_num );
  }

}

void PmodSevenSegLogic::detach()
{
  timer->stop();
}

void PmodSevenSegLogic::RESET()
{
  timer->stop();
  timer->start( POLL_PERIOD );
}

PmodSevenSegLogic::~PmodSevenSegLogic()
{
  timer->stop();
  delete timer;
}
