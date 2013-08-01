/**
 * \file LEDLogic.h
 * \brief a simple LED logic implementation
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
#ifndef LEDLOGIC_H
#define LEDLOGIC_H

#include <QObject>

/**
 * \brief a simple LED logic implementation
 */
class LEDLogic : public QObject
{

  Q_OBJECT


public:
  /**
   * \brief creates a LEDLogic instance
   *
   * \param num a number which uniquely identifies the LED, this number will be emitted with
   * LEDOn( int ) and LEDOff( int )
   */
  LEDLogic( int num ) : num( num ), on( false ), lowFrequency( false ),
    dutyCycle( 0.0f ), frequency( 0.0f ), index( 0 ) { }

  ~LEDLogic() {}

  /**
   * \brief returns the frequency of the LED in Hertz
   *
   * \return the frequency in Hertz
   */
  double getFrequency( void ) {
    return this->frequency;
  }

  /**
   * \brief returns the duty cycle of the LED as a percentage i.e. from 0.0 <-> 1.0
   *
   * \return the duty cycle of the led
   */
  double getDutyCycle( void ) {
    return this->dutyCycle;
  }

public slots:

  /**
   * \brief used to log pin history, this function will emit LEDOn( int )
   * and LEDOff( int ) when calculation result in changes to the LED State i.e. on or off
   *
   * \note this method assumes consecutive calls have alternating voltage levels
   *
   * \param level the voltage level at a particular \em time
   * \param time the time the voltage level change occurred
   */
  void update( int level, long long time );

signals:

  /**
   * \brief the signal emitted when the LED logic determines the LED to be on
   *
   * \param num a unique number identifier the LED which sent the signal
   * \see LEDLogic::LEDLogic( int )
   */
  void LEDOn( int num );

  /**
   * \brief the signal emitted when the LED logic determines the LED to be off
   *
   * \param num a unique number identifier the LED which sent the signal
   * \see LEDLogic::LEDLogic( int )
   */
  void LEDOff( int num );

private:

  struct PinState {
    int level;
    long long time;
  };

  int num;

  bool on;

  bool lowFrequency;
  bool flash;

  double dutyCycle;
  double frequency;

  int index;
  PinState history[3];
};

#endif // LEDLOGIC_H
