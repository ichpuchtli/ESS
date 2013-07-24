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

AVRIOAdapter::AVRIOAdapter(avr_t* avr, QThread* thread) :
  thread(thread), avr(avr), pinmap(new QHash<QString, GPIOPin*>())
{
}

AVRIOAdapter::~AVRIOAdapter(){

  QList<GPIOPin*> pins = this->pinmap->values();

  for( int i = 0; i < pins.size(); i++){
     delete pins[i];
  }

  this->pinmap->clear();

  delete this->pinmap;

}

avr_t* AVRIOAdapter::getAVR(void){
  return this->avr;
}

QThread* AVRIOAdapter::getThread(void){
  return this->thread;
}

GPIOPin& AVRIOAdapter::getGPIOPin(char port, unsigned pin){

  char name[4];

  name[0] = 'P';
  name[1] = port;
  name[2] = (char) pin + '0';
  name[3] = '\0';

  return this->getGPIOPin(name);
}

GPIOPin& AVRIOAdapter::getGPIOPin(const char* name){

  QString key(name);

  /*
  if( key.containts(QRegularExpresseion("P[A-G][0-7]")) )
    throw new InvalidPortIdentifier();
  }
  */

  if( !this->pinmap->contains(key) ){
    this->pinmap->insert(key, new GPIOPin(this->getAVR(), name, this->getThread()) );
  }

  return *this->pinmap->value(key);

}

AbstractPin& AVRIOAdapter::VCC(void){

  static StaticPin vcc(3300);

  return vcc;

}

AbstractPin& AVRIOAdapter::GND(void){

  static StaticPin gnd(0);

  return gnd;

}

AbstractPin& AVRIOAdapter::AVCC(void){

  static StaticPin avcc(3300);

  return avcc;
}

AbstractPin& AVRIOAdapter::RESET(void){

  static StaticPin reset(3300);

  return reset;

}
