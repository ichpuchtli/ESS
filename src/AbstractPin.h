/**
 * \file AbstractPin.h
 * \brief An abstract base class for ave pin states
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

#ifndef ABSTRACTPIN_H
#define ABSTRACTPIN_H

#include <QObject>

/**
 * \brief An abstract base class for mcu pin state descriptions
 */
class AbstractPin : public QObject
{

  Q_OBJECT

public:

  AbstractPin( QObject* parent = 0 ) : QObject( parent ) {}
  virtual ~AbstractPin() {}

//virtual char* getName(void) const = 0;

  /**
   * \brief get the digital level of the pin
   *
   * \return the digital level of the pin either 0 or 1
   */
  virtual int getLevel( void ) const = 0;


  /**
   * \brief get the voltage level of the pin
   *
   * \return the voltage level of the pin between 0 ( GND ) and 3300 ( VCC )
   */
  virtual int getVoltage( void ) const = 0;

signals:

  /**
   * \brief the signal to be emitted if the voltage of the pin has changed
   *
   * \param voltage the new voltage level
   * \param port the port the voltagechange occurred on
   * \param pin the pin the voltagechange occurred on
   */
  void voltageChange( int voltage, char port, char pin );

  /**
   * \brief the signal to be emitted if the level of the pin has changed, a
   * voltage less than VCC / 2 is considered a digital 0 and any voltage
   * greater than or equal to VCC / 2 is considered a digital 1.
   *
   * \param level the new digital level for the pin either 0 or 1
   * \param port the port the levelchange occurred on
   * \param pin the pin the levelchange occurred on
   */
  void levelChange( int level, char port, char pin );

  /**
   * \brief the signal to be emitted level changes from low to high
   */
  void risingEdge();

  /**
   * \brief the signal to be emitted level changes from high to low
   */
  void fallingEdge();

public slots:


  /**
   * \brief set the digital level of the pin to \em level
   *
   * \param level the new digital level for the pin either 0 or 1
   *
   * \note voltageChange(int) and levelChange(int) will both be emitted here if this
   * action results in a level change. Setting the level to 1 will set the voltage
   * to 3300 ( VCC ) and setting the level to 0 will set the voltage to 0 ( GND )
   */
  virtual void setLevel( int level ) = 0;

  /**
   * \brief set the voltage level of the pin to \em voltage
   *
   * \param voltage the new voltage level for the pin between 0 ( GND ) or 3300 ( VCC )
   *
   * \note voltageChange(int) will be emitted here if
   *
   * \code{.cpp}
   * voltage != old_voltage
   * \endcode
   *
   * \note levelChange(int) will only be emitted here if the new voltage has resulted in a level
   * change
   *
   * \see voltageChange(int)
   * \see levelChange(int)
   */
  virtual void setVoltage( int voltage ) = 0;

  /**
   * \brief set the digital level of the pin low
   */
  virtual void pullDown() {
    this->setLevel( 0 );
  }

  /**
   * \brief set the digital level of the pin high
   */
  virtual void pullUp() {
    this->setLevel( 1 );
  }

};

Q_DECLARE_INTERFACE( AbstractPin, "ESS.AbstractPin/1.0" )

#endif // ABSTRACTPIN_H
