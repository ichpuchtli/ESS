/**
 * \file AVRIOAdapter.h
 * \brief A class providing means for virtual peripherals to connect
 * to the avr simulation engine
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

#ifndef AVRIOADAPTER_H
#define AVRIOADAPTER_H

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QThread>

#include "AbstractPin.h"
#include "GPIOPin.h"

struct avr_t;

/**
 * \brief A class providing means for virtual peripherals to connect
 * to the avr simulation engine
 */
class AVRIOAdapter {

  public:

    /**
     * \brief constructs a AVRIOAdapter instance, all IO will assume the affinity
     * of the \em thread provided
     *
     * \param avr the simavr c structure
     * \param thread the thread of the avr cpu
     */
    AVRIOAdapter(avr_t* avr, QThread* thread);
    ~AVRIOAdapter();

    /**
     * \brief get the internal simavr data structure
     *
     * \return a pointer to the internal avr_t struct
     */
    virtual avr_t* getAVR(void);

    /**
     * \brief returns the thread affinity of the IO objects provided by this 
     * class, i.e. signals emitted from these pins are sent from the event
     * loop \em thread.
     *
     * \see Thread Affinity
     *
     * \return a pointer to the thread
     */
    virtual QThread* getThread(void);

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
    virtual GPIOPin& getGPIOPin(const char* name);

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
    virtual GPIOPin& getGPIOPin(char port, unsigned pin);

    /**
     * \brief get an instance of the GND pin
     *
     * \return a pointer to an object representing the GND pin
     */
    virtual AbstractPin& GND(void);

    /**
     * \brief get an instance of the VCC pin
     *
     * \return a pointer to an object representing the VCC pin
     */
    virtual AbstractPin& VCC(void);

    /**
     * \brief get an instance of the AVCC pin
     *
     * \return a pointer to an object representing the AVCC pin
     */
    virtual AbstractPin& AVCC(void);

    /**
     * \brief get an instance of the RESET pin
     *
     * \return a pointer to an object representing the RESET pin
     */
    virtual AbstractPin& RESET(void);

  private:

    QThread* thread;

    avr_t* avr;

    QHash<QString, GPIOPin*>* pinmap;
};

#endif // AVRIOADAPTER_H
