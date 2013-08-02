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

#include "sim_hex.h"

void AVRProcessor::loadFirmware( const QString& filename )
{

  this->stop();

  bzero( &this->firmware, sizeof( elf_firmware_t ) );

  if ( filename.endsWith( ".hex" ) ) {

    ihex_chunk_p chunk = NULL;

    int count = read_ihex_chunks( filename.toLatin1(), &chunk );

    if ( count <= 0 ) {
      qDebug() << "Firmware: Unable to load hex file:" << filename;
      return;
    }

    for ( int index = 0; index < count; index++ ) {
      if ( chunk[index].baseaddr < ( 1 * 1024 * 1024 ) ) {
        this->firmware.flash = chunk[index].data;
        this->firmware.flashsize = chunk[index].size;
        this->firmware.flashbase = chunk[index].baseaddr;
      }
    }

  } else if ( filename.endsWith( ".axf" ) ) {

    elf_read_firmware( filename.toLatin1(), &this->firmware );

  } else {

    qDebug() << "Firmware: Unrecognized file extension:" << filename;
    return;

  }

  this->filename = filename;

  this->firmware.frequency = this->frequency;

  memcpy( this->firmware.mmcu, this->mmcu.toLatin1(), this->mmcu.size() );

  qDebug() << "AVRProcessor:" << this->filename.toLatin1() << " freq "
           << this->frequency << " mmcu " << this->mmcu.toLatin1();

  avr_reset( this->avr );

  avr_load_firmware( this->avr, &this->firmware );

  fflush( stdout );

  emit this->loaded( this->avr );

}
