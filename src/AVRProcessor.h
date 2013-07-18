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

  /**
   * \brief Creates a generic 8-bit avr processor containing all the
   * necessary functionality except the main strategy of execution which is
   * fulfilled by subclasses
   *
   * \note the list of supported avr devices is determined by the version
   * of simavr linked with the ESS at compile time.
   *
   * \see <a href="http://github.com/buserror-uk/simavr">buserror-uk/simavr</a>
   *
   * \note the list of supported devices for simavr at cc901dc include:
   *
   *   \li at90usb162 (with usb!)
   *   \li atmega1280
   *   \li atmega128
   *   \li atmega64
   *   \li atmega16m1
   *   \li atmega164/324/644
   *   \li atmega48/88/168/328
   *   \li atmega8
   *   \li attiny25/45/85
   *   \li attiny44/84
   *   \li attiny2313
   *   \li attiny13
   *
   * \param mmcu the avr device to target
   * \param frequency the desired frequency of execution typically in the
   * range of MHz for instance 8MHz would be 8000000. The actual rate is up to
   * the simulation strategy and can be limited by the power of the computer
   * running the simulation
   */
    AVRProcessor(const QString& mmcu, unsigned frequency) :
    isRunning(false),
    mmcu(mmcu),
    frequency(frequency)
    {
      this->avr = avr_make_mcu_by_name(mmcu.toLatin1());
      avr_init(this->avr);
    }

  ~AVRProcessor() {
      free(this->avr);
   }

public slots:

  void stop() { this->isRunning = false; }

  void loadFirmware(const QString &filename);

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

    return ( status != cpu_Crashed ) && ( status != cpu_Done ) &&
        this->isRunning;

  }

  /**
   * \brief get the internal avr_t structure
   *
   * \return a pointer to the internal simavr based avr_t structure
   */
  avr_t* getAVR(void) { return this->avr; }

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
   * \brief simavr owned c structure containing simavr instance data
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
   * \brief the name of the targeted avr device 
   */
  QString mmcu;

  /**
   * \brief the desired frequency of execution
   */
  unsigned frequency;

  /**
   * \brief indicates the user has requested stop to execution
   */
  bool isRunning;

};

Q_DECLARE_INTERFACE(AVRProcessor, "ESS.AVRProcessor")

#endif // AVRPROCESSOR_H
