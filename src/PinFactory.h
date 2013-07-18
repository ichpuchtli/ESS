/**
 * \file PinFactory.h
 * \brief An class for managing the set of peripheral pins for an avr
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

#ifndef PINFACTORY_H
#define PINFACTORY_H

#include <QHash>
#include <QString>

#include "GPIOPin.h"
#include "AbstractPin.h"
#include "AbstractPinFactory.h"

/**
 * \brief An class for managing the set of peripheral pins for an avr
 */
class PinFactory : public AbstractPinFactory
{

  public:

    /**
     * \brief constructs a PinFactory instance, each new pin will assume
     * \em pinAffinity as its parent QObject
     *
     * \param avr the simavr c structure to connect the pin to
     * \param pinAffinity the pin affinity for all the pins
     */
    PinFactory(avr_t* avr, QObject* pinAffinity);
    ~PinFactory();

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
    GPIOPin& getGPIOPin(const char* name);

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
    GPIOPin& getGPIOPin(char port, unsigned pin);

    /**
     * \brief get an instance of the GND pin
     *
     * \return a pointer to an object representing the GND pin
     */
    AbstractPin& GND(void);

    /**
     * \brief get an instance of the VCC pin
     *
     * \return a pointer to an object representing the VCC pin
     */
    AbstractPin& VCC(void);

    /**
     * \brief get an instance of the AVCC pin
     *
     * \return a pointer to an object representing the AVCC pin
     */
    AbstractPin& AVCC(void);

    /**
     * \brief get an instance of the RESET pin
     *
     * \return a pointer to an object representing the RESET pin
     */
    AbstractPin& RESET(void);

  private:

    QHash<QString, GPIOPin*>* pinmap;

    QObject* parent;

    avr_t* avr;

};

#endif // PINFACTORY_H
