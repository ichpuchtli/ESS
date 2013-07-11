/**
 * \file AbstractAVRProcessor.h
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

#ifndef ABSTRACTAVRPROCESSOR_H
#define ABSTRACTAVRPROCESSOR_H

#include <QtCore/QObject>
#include <QtCore/QString>

/**
 * \brief An abstract base class for running simavr based avr simulations
 */
class AbstractAVRProcessor : public QObject {

  Q_OBJECT

public:

  virtual ~AbstractAVRProcessor() {}

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
  virtual void load(const QString& filename, const QString& mmcu, unsigned frequency) = 0;

};

Q_DECLARE_INTERFACE(AbstractAVRProcessor, "ESS.AbstractAVRProcessor/1.0")

#endif // ABSTRACTAVRPROCESSOR_H
