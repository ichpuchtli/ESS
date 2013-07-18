/**
 * \file PinFactory.cpp
 * \brief An class for managing the set of peripheral pins for an avr
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
#include "PinFactory.h"

#include "StaticPin.h"

PinFactory::PinFactory(avr_t* avr, QObject* pinAffinity) :
  parent(pinAffinity), avr(avr)
{
  this->pinmap = new QHash<QString, GPIOPin*>();
}

PinFactory::~PinFactory(){

  QList<GPIOPin*> pins = this->pinmap->values();

  for( int i = 0; i < pins.size(); i++){
     delete pins[i];
  }

  this->pinmap->clear();

  delete this->pinmap;

}

GPIOPin& PinFactory::getGPIOPin(char port, unsigned pin){

  char name[4];

  name[0] = 'P';
  name[1] = port;
  name[2] = (char) pin + '0';
  name[3] = '\0';

  return this->getGPIOPin(name);
}

GPIOPin& PinFactory::getGPIOPin(const char* name){

  QString key(name);

  /*
  if( key.containts(QRegularExpresseion("P[A-G][0-7]")) )
    throw new InvalidPortIdentifier();
  }
  */

  if( !this->pinmap->contains(key) ){
    this->pinmap->insert(key, new GPIOPin(this->avr, name, this->parent) );
  }

  return *this->pinmap->value(key);

}

AbstractPin& PinFactory::VCC(void){

  static StaticPin vcc(3300);

  return vcc;

}

AbstractPin& PinFactory::GND(void){

  static StaticPin gnd(0);

  return gnd;

}

AbstractPin& PinFactory::AVCC(void){

  static StaticPin avcc(3300);

  return avcc;
}

AbstractPin& PinFactory::RESET(void){

  static StaticPin reset(3300);

  return reset;

}
