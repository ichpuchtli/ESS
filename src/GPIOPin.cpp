/**
 * \file GPIOPin.cpp
 * \brief an AbstractPin implementation for General Peripheral Input/Output pins
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
#include "GPIOPin.h"

#include "sim_avr.h"
#include "sim_irq.h"
#include "avr_ioport.h"

#include <QDebug>

GPIOPin::GPIOPin(avr_t* avr, const char* identifier, QObject* parent) :
  AbstractPin(parent), avr(avr), port(identifier[1]), pin(identifier[2] - '0')
{
  this->init();
}

GPIOPin::GPIOPin(avr_t* avr, char port, unsigned pin, QObject* parent) :
  AbstractPin(parent), avr(avr), port(port), pin(pin)
{
  this->init();
}

GPIOPin::~GPIOPin(){

  avr_irq_unregister_notify(this->pin_irq, GPIOPin::pinChangeHook, NULL);
  avr_irq_unregister_notify(this->ddr_irq, GPIOPin::ddrChangeHook, NULL);

}

void GPIOPin::init(){

  //TODO polling based GPIOPins with avr_ioctl

 qDebug() << "GIOPin: Pin" << port << (unsigned) pin << "connected!";

  this->pin_irq = avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(this->port),
                                this->pin);

  this->ddr_irq = avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(this->port),
                                IOPORT_IRQ_DIRECTION_ALL);

  this->levelCache = 0x0;
  this->ddrCache = 0x0;

  avr_irq_register_notify(this->pin_irq, GPIOPin::pinChangeHook, this);
  avr_irq_register_notify(this->ddr_irq, GPIOPin::ddrChangeHook, this);

}

void GPIOPin::pinChangeHook(struct avr_irq_t* irq, uint32_t value, void* param){

  (void) irq;

  GPIOPin* pin = (GPIOPin*) param;

  pin->pinChangeEvent( value );

}

void GPIOPin::ddrChangeHook(struct avr_irq_t* irq, uint32_t value, void* param){

  (void) irq;

  GPIOPin* pin = (GPIOPin*) param;

  pin->dirChangeEvent( value );
}

void GPIOPin::pinChangeEvent( int value ) {

  /*
  if ( this->levelCache == 0 ) {
    emit this->risingEdge();
  }

  if ( this->levelCache == 1 ) {
    emit this->fallingEdge();
  }
  */

  this->levelCache = value;
  this->voltageCache = value*3300;

  emit this->levelChange( this->levelCache );
  emit this->voltageChange( this->voltageCache );
}

void GPIOPin::dirChangeEvent( int direction ) {

  this->ddrCache = direction;

  emit this->directionChange( direction );

}

void GPIOPin::setVoltage( int voltage ) {

  if( this->ddrCache == 0 ) {

    //TODO establish global GND/VCC Levels
    avr_raise_irq(this->pin_irq, voltage);

  }

}

void GPIOPin::setLevel( int level ) {

  if( this->ddrCache == 0 ) {

    //TODO establish global GND/VCC Levels
    avr_raise_irq( this->pin_irq, level * 3300);

  }

}

int GPIOPin::getLevel( void ) const {
  return this->levelCache;
}

int GPIOPin::getVoltage( void ) const {
  return this->voltageCache;
}

int GPIOPin::getDirection( void ) const {
  return this->ddrCache;
}
