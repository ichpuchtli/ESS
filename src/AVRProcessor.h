/**
 * \file AVRProcessor.h
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

#ifndef AVRPROCESSOR_H
#define AVRPROCESSOR_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "sim_avr.h"
#include "sim_elf.h"

#include "AbstractAVRProcessor.h"

/**
 * \brief An abstract base class for running simavr based avr simulations
 */
class AVRProcessor : public AbstractAVRProcessor {

  Q_OBJECT
  Q_INTERFACES(AbstractAVRProcessor)

public:

  AVRProcessor() : avr(NULL) {}
  virtual ~AVRProcessor() {}

  /**
   * \brief returns true if the simavr core is still runnable typically used
   * to determine when to leave the simulation loop
   *
   * \code{.cpp}
   *
   * int status = cpu_Running;
   *
   * while ( AVRProcessor::avrRunnable( status ) {
   *  status = avr_run( avr );
   * }
   *
   * \endcode
   *
   * \param status the enum returned by avr_run( avr_t* avr ) from simavr which
   * executes a single operation
   *
   * \return a bool representing a runnable state given the current simavr core
   * status
   */
  inline bool avrRunnable( int status ){

    return ( status != cpu_Crashed ) && ( status != cpu_Done );

  }

  void load(const QString& filename, const QString& mmcu, unsigned frequency);

signals:

  /**
   * \brief this signal is emitted when new firmware file is loaded and ready
   * to simulate
   *
   * \param avr an initialized avr_t pointer for this simavr instance
   */
  void loaded(avr_t* avr);


protected:

  /**
   * \brief simavr owned c structure contatining simavr instance data
   */
  avr_t* avr;

  /**
   * \brief simavr owned c structure holds information about the loaded firmware
   */
  elf_firmware_t firmware;

  /**
   * \brief the filename of the loaded firmware
   */
  QString filename;

  /**
   * \brief the name of the targetet avr device 
   */
  QString mmcu;

  /**
   * \brief the desired frequency of executation
   */
  unsigned frequency;

};

Q_DECLARE_INTERFACE(AVRProcessor, "ESS.AVRProcessor")

#endif // AVRPROCESSOR_H
