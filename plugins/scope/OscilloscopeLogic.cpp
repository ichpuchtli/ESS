/**
 * \file OscilloscopeLogic.cpp
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
#include "OscilloscopeLogic.h"

#include <sys/time.h>

OscilloscopeLogic::OscilloscopeLogic() : port( '\0' ), pin( 0 )
{
}

OscilloscopeLogic::~OscilloscopeLogic()
{
  this->detach();
}

void OscilloscopeLogic::connectNet( QString net, QString pin )
{

  ( void ) net;

  this->detach();

  this->port = pin.toLatin1()[1];
  this->pin = pin.toLatin1()[2] - '0';

  QObject::connect( &this->io->getGPIOPin( this->port, this->pin ),
                    &AbstractPin::levelChange,
                    this, &OscilloscopeLogic::router );
}

void OscilloscopeLogic::attach( AVRIOAdapter* io )
{
  this->io = io;
}

void OscilloscopeLogic::detach()
{
  if ( port ) {
    QObject::disconnect( &this->io->getGPIOPin( this->port, this->pin ), 0, this,
                         0 );
  }
}

void OscilloscopeLogic::RESET()
{

  struct timeval t;

  // TODO use avr cycles for time base
  gettimeofday( &t, NULL );

  this->initial = t.tv_sec * 1000000U + t.tv_usec;
}

void OscilloscopeLogic::router( int voltage, char port, char pin )
{

  ( void ) port;
  ( void ) pin;

  long long now;

  struct timeval t;

  // TODO use avr cycles for time base
  gettimeofday( &t, NULL );

  now = t.tv_sec * 1000000U + t.tv_usec;

  emit this->newData( voltage * 3300 , now - this->initial );

}
