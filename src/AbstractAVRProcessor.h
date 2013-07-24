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
class AbstractAVRProcessor : public QObject
{

  Q_OBJECT

public:

  virtual ~AbstractAVRProcessor() {}

signals:

  /**
   * \brief this signal is emitted prior to entering a simulation loop,
   * this would be the ideal time to initialize/reset components etc.
   */
  void RESET();

  /**
   * \brief this signal is emitted when a simulation loop has exited, this
   * is usually caused by intervention via stop() or when execution errors
   * occurs or when EOF is reached in the avr program.
   * \see avrStateChange(int)
   */
  void stopped();

  /**
   * \brief this signal is emitted when the simulation core state changes,
   * this is emitted before and after a simulation loop
   *
   * \param status the new status of the simavr core
   */
  void avrStateChange( int status );

public slots:

  /**
   * \brief exit as soon as possible, emits stopped() when exiting
   */
  virtual void stop() = 0;

  /**
   * \brief the only pure virtual method in the class, this method
   * houses the simulation procedure and is often connected to a
   * QThread or QTimer event.
   */
  virtual void run() = 0;

  /**
   *\brief load a new 8-bit avr executable compiled with avr-gcc or WinAVR
   * given a \em filename to the compiled executable
   *
   * \param filename the path to the compiled avr executable
   */
  virtual void loadFirmware( const QString& filename ) = 0;

};

Q_DECLARE_INTERFACE( AbstractAVRProcessor, "ESS.AbstractAVRProcessor/1.0" )

#endif // ABSTRACTAVRPROCESSOR_H
