/**
 * \file PolledLEDLogic.h
 * \brief a simple polled LED logic implementation
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
#ifndef POLLEDLEDLOGIC_H
#define POLLEDLEDLOGIC_H

#include <QObject>
#include <QtCore/QTimer>

#include "../../src/AbstractPin.h"

/**
 * \brief cutoff frequency for updating the widget, note the
 * human eye can only perceive oscillations up to 25-30 Hz.
 * However you can probably get away with 20 Hz.
 */
const int FREQUENCY_THRESHOLD = 25; // Hz

/**
 * \brief the frequency at which to poll the net attached to this
 * LED, if you want to accurately detect certain frequency you need to
 * poll the signal at twice that frequency.
 *
 * \see Nyquist Theorem
 */
const int POLL_FREQUENCY = FREQUENCY_THRESHOLD * 2; // Hz

const int POLL_PERIOD = 1000 / ( POLL_FREQUENCY ); // Milliseconds

/**
 * \brief size of the sliding window of pin status history,
 * must be an order of 2
 */
const int HISTORY_SIZE = 32;

/**
 * \brief a simple polled LED logic implementation
 */
class PolledLEDLogic : public QObject
{

  Q_OBJECT

public:
  /**
   * \brief creates a PolledLEDLogic instance
   *
   * \param num a number which uniquely identifies the LED, this number will be emitted with
   * LEDOn( int ) and LEDOff( int )
   * \param pin the abstract pin instance for the pin tied to this led
   */
  PolledLEDLogic( int num, AbstractPin* pin );

  ~PolledLEDLogic();

public slots:

  /**
   * \brief starts polling the pin
   */
  void startPolling();

  /**
   * \brief stops polling the pin
   */
  void stopPolling();

private slots:

  void poll();

signals:

  /**
   * \brief the signal emitted when the LED logic determines the LED to be on
   *
   * \param num a unique number identifier the LED which sent the signal
   * \see PolledLEDLogic::PolledLEDLogic( int )
   */
  void LEDOn( int num );

  /**
   * \brief the signal emitted when the LED logic determines the LED to be off
   *
   * \param num a unique number identifier the LED which sent the signal
   * \see PolledLEDLogic::PolledLEDLogic( int )
   */
  void LEDOff( int num );

private:

  void updateCache();

  int findNearestEdge( int offset );

  int findFallingEdge( int offset );

  int findRisingEdge( int offset );

  int num;
  AbstractPin* pin;

  QTimer* timer;

  bool lowFrequency;

  double dutyCycle;
  double frequency;

  int index;
  bool history[HISTORY_SIZE];

};

#endif // POLLEDLEDLOGIC_H
