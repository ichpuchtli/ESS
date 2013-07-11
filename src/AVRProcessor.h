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

/**
 * \brief An abstract base class for running simavr based avr simulations
 */
class AVRProcessor : public QObject {

  Q_OBJECT

public:

  AVRProcessor();
  virtual ~AVRProcessor();

  signals:

  /**
   * \brief this signal is emitted prior to entering a simulation loop,
   * this would be the ideal time to intialize/reset components etc.
   */
  void RESET();

  /**
   * \brief this signal is emitted when a simulation loop has finished either
   * following an error in simulation or reaching the end of the simulated
   * program
   * \see avrStateChange(int)
   */
  void finished();

  /**
   * \brief this signal is emitted when new firmware file is loaded and ready
   * to simulate
   *
   * \param avr an initialized avr_t pointer for this simavr instance
   */
  void loaded(avr_t* avr);

  /**
   * \brief this signal is emitted when the simulation core state changes,
   * this is emitted before and after a simulation loop
   *
   * \param status the new status of the simavr core
   */
  void avrStateChange(int status);

  public slots:

  /**
   * \brief the only pure virtual method in the class, this method 
   * houses the simulation procedure and is often connected to a
   * QThread or QTimer event.
   */
  virtual void run() = 0;

  /**
   * \brief load a new 8-bit avr executable compiled with avr-gcc or WinAVR
   * given a \em filename to the compiled executable the desired
   * \em frequency and \em mmcu
   *
   * \note the list of supported avr devices is determined by the version
   * of simavr linked with the ESS at compile time.
   *
   * \see <a href="http://github.com/buserror-uk/simavr">buserror-uk/simavr</a>
   *
   * \note the list of supported devices for simavr at cc901dc include:
   *
   *   \li AT90USB162 (with USB!)
   *   \li ATMega1280
   *   \li ATMega128
   *   \li ATMega64
   *   \li ATMega16M1
   *   \li ATMega164/324/644
   *   \li ATMega48/88/168/328
   *   \li ATMega8
   *   \li ATTiny25/45/85
   *   \li ATTIny44/84
   *   \li ATTiny2313
   *   \li ATTiny13
   *
   * \param filename the path to the compiled avr executable
   * \param mmcu the avr device to target
   * \param frequency the diesred frequency of execuation typically in the
   * range of MHz for instance 8MHz would be 8000000. The actual rate is up to
   * the simulation stragtegy and can be limited by the power of the computer
   * running the simulation
   */
  void load(const QString& filename, const QString& mmcu, unsigned frequency);

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
