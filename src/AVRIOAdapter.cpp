/**
 * \file AVRIOAdapter.cpp
 * \brief A class providing means for virtual peripherals to connect
 * to the avr simulation engine
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
#include "AVRIOAdapter.h"

#include "GPIOPin.h"
#include "StaticPin.h"

#include "sim_avr.h"
#include "avr_ioport.h"

const char* PORT_LETTERS = "ABCDEFG";
const int PIN_COUNT = 7 * 8;

AVRIOAdapter::AVRIOAdapter( avr_t* avr, QThread* thread ) :
  thread( thread ), avr( avr ), pinmap( new QHash<QString, GPIOPin*>() )
{

  const char* pin_names[PIN_COUNT] = {
    "PA0", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7",
    "PB0", "PB1", "PB2", "PB3", "PB4", "PB5", "PB6", "PB7",
    "PC0", "PC1", "PC2", "PC3", "PC4", "PC5", "PC6", "PC7",
    "PD0", "PD1", "PD2", "PD3", "PD4", "PD5", "PD6", "PD7",
    "PE0", "PE1", "PE2", "PE3", "PE4", "PE5", "PE6", "PE7",
    "PF0", "PF1", "PF2", "PF3", "PF4", "PF5", "PF6", "PF7",
    "PG0", "PG1", "PG2", "PG3", "PG4", "PG5", "PG6", "PG7"
  };

  this->irq = avr_alloc_irq( &this->avr->irq_pool, 0, PIN_COUNT, pin_names );

  for ( int i = 0; i < PIN_COUNT; i++ ) {

    int port = i / 8;
    int pin = i % 8;

    avr_connect_irq( this->irq + i, avr_io_getirq( avr,
                     AVR_IOCTL_IOPORT_GETIRQ( PORT_LETTERS[port] ), pin ) );

  }

}

AVRIOAdapter::~AVRIOAdapter()
{

  QList<GPIOPin*> pins = this->pinmap->values();

  for ( int i = 0; i < pins.size(); i++ ) {
    delete pins[i];
  }

  this->pinmap->clear();

  delete this->pinmap;

}

avr_t* AVRIOAdapter::getAVR( void )
{
  return this->avr;
}

QThread* AVRIOAdapter::getThread( void )
{
  return this->thread;
}

GPIOPin& AVRIOAdapter::getGPIOPin( char port, unsigned pin )
{

  GPIOPin* newPin;
  avr_irq_t* write_irq;

  char name[4];

  name[0] = 'P';
  name[1] = port;
  name[2] = ( char ) pin + '0';
  name[3] = '\0';

  QString key( name );

  if ( !this->pinmap->contains( key ) ) {

    write_irq = this->irq + ( port - 'A' ) * 8  + pin;

    newPin = new GPIOPin( this->avr, write_irq , name, this->getThread() );

    this->pinmap->insert( key, newPin );
  }

  return *this->pinmap->value( key );

}

GPIOPin& AVRIOAdapter::getGPIOPin( const char* name )
{

  return this->getGPIOPin( name[1], name[2] - '0' );

}

AbstractPin& AVRIOAdapter::VCC( void )
{

  static StaticPin vcc( 3300 );

  return vcc;

}

AbstractPin& AVRIOAdapter::GND( void )
{

  static StaticPin gnd( 0 );

  return gnd;

}

AbstractPin& AVRIOAdapter::AVCC( void )
{

  static StaticPin avcc( 3300 );

  return avcc;
}

AbstractPin& AVRIOAdapter::RESET( void )
{

  static StaticPin reset( 3300 );

  return reset;

}
