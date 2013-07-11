/**
 * \file AVRProcessor.cpp
 * \brief An abstract base class for running simavr based avr simulations
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
#include "AVRProcessor.h"

#include <QtCore/QDebug>

AVRProcessor::AVRProcessor(){

  this->avr = NULL;

}

AVRProcessor::~AVRProcessor(){

  if(this->avr){

    free(this->avr);
  }

}

void AVRProcessor::load(const QString& filename, const QString& mmcu, unsigned frequency) {

  this->filename = QString(filename);

  this->mmcu = QString(mmcu);

  this->frequency = frequency;

  elf_read_firmware(filename.toLatin1(), &this->firmware);

  this->firmware.frequency = frequency;

  memcpy(this->firmware.mmcu, mmcu.toLatin1(), mmcu.size() );

  qDebug() << "AVRProcessor:" << this->filename.toLatin1() << " freq "
    << frequency << " mmcu " << mmcu.toLatin1();

  this->avr = avr_make_mcu_by_name(mmcu.toLatin1());

  if(!this->avr){
      qDebug() << "AVRProcessor: possible memory allocation error\n";
      return;
  }

  avr_init(this->avr);

  avr_load_firmware(this->avr, &this->firmware);

  fflush(stdout);

  emit this->loaded(this->avr);
}
