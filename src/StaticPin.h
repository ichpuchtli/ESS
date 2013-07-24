/**
 * \file StaticPin.h
 * \brief a AbstractPin implementation representing a fixed voltage pin
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

#ifndef STATICPIN_H
#define STATICPIN_H

#include "AbstractPin.h"

/**
 * \brief a AbstractPin implementation representing a fixed voltage pin
 */
class StaticPin : public AbstractPin
{

  Q_INTERFACES( AbstractPin )

public:
  /**
   * \brief constructs a StaticPin instance with the given voltage
   *
   * \param volts the fixed voltage for the pin
   */
  StaticPin( int volts ) : voltage( volts ) { }

  int getLevel( void ) const {
    return ( this->voltage ) < 1650 ? 0 : 1;
  }
  int getVoltage( void ) const {
    return this->voltage;
  }

  /**
   * \brief this method has no affect since this pin has a fixed voltage level
   */
  void setLevel( int level ) {
    ( void ) level;
  }

  /**
   * \brief this method has no affect since this pin has a fixed voltage level
   */
  void setVoltage( int voltage ) {
    ( void ) voltage;
  }

private:
  const int voltage;

};

#endif // STATICPIN_H
