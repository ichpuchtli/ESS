/**
 * \file AbstractPinFactory.h
 * \brief An abstract base class for managing the set of peripheral pins for
 * an avr
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

#ifndef ABSTRACTPINFACTORY_H
#define ABSTRACTPINFACTORY_H

#include <QObject>

#include "AbstractPin.h"

#define ABSTRACTPINFACTORY_IDD "ESS.AbstractPinFactory/1.0"

/**
 * \brief An class for managing the set of peripheral pins for an avr
 */
class AbstractPinFactory
{

  public:

    virtual ~AbstractPinFactory() {}

    /**
     * \brief get an instance of a GPIOPin identified by \em name
     *
     * \param name the unique identifier for the pin, the structure is
     * P[A-G][0-7] all uppercase. For example PORT D Pin 1 would be \em PD1
     *
     * \return a pointer to a GPIOPin instance or NULL if \em name do not
     * meet the given criteria
     *
     * \see GPIOPin::GPIOPin(const char*)
     */
    virtual AbstractPin& getGPIOPin(const char* name) = 0;

    /**
     * \brief get an instance of a GPIOPin identified by \em port and \em pin
     * for instance Port C Pin 5 would be getGPIOPin( 'C', 5 );
     *
     * \param port the uppercase port of the pin as a ASCII character from [A-G]
     * \param pin the index in to the port of the particular pin from [0-7]
     *
     * \return a pointer to a GPIOPin instance or NULL if \em port and \em pin
     * do not meet the given criteria
     *
     * \see GPIOPin::GPIOPin(char,unsigned)
     */
    virtual AbstractPin& getGPIOPin(char port, unsigned pin) = 0;

    /**
     * \brief get an instance of the GND pin
     *
     * \return a pointer to an object representing the GND pin
     */
    virtual AbstractPin& GND(void) = 0;

    /**
     * \brief get an instance of the VCC pin
     *
     * \return a pointer to an object representing the VCC pin
     */
    virtual AbstractPin& VCC(void) = 0;

    /**
     * \brief get an instance of the AVCC pin
     *
     * \return a pointer to an object representing the AVCC pin
     */
    virtual AbstractPin& AVCC(void) = 0;

    /**
     * \brief get an instance of the RESET pin
     *
     * \return a pointer to an object representing the RESET pin
     */
    virtual AbstractPin& RESET(void) = 0;

};

Q_DECLARE_INTERFACE( AbstractPinFactory, ABSTRACTPINFACTORY_IDD )

#endif // PINFACTORY_H
