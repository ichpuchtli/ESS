/**
 * \file AbstractPeripheralLogic.h
 * \brief An abstract base class for representing peripheral logic interactions
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
#ifndef ABSTRACTPERIPHERALLOGIC_H
#define ABSTRACTPERIPHERALLOGIC_H

#include <QObject>
#include <QString>

#include "AbstractPinFactory.h"
#include "AbstractAVRProcessor.h"

/**
 * \brief plugins can be compiled with or without simavr instead using AbstractPinFactory 
 * which is sufficient for simple cases. This abstraction was introduced to ease plugin
 * development on Microsoft Windows where simavr can be difficult to introduce.
 */
#ifdef SIMAVR_PLUGIN
#include "sim_avr.h"
#else
struct avr_t;
#endif

#define ABSTRACTPERIPHERALLOGIC_IDD "ESS.AbstractPeripheralLogic/1.0"

/**
 * \brief An abstract base class for representing peripheral logic interactions
 */
class AbstractPeripheralLogic : public QObject {

  Q_OBJECT

  public:

    virtual ~AbstractPeripheralLogic() {}

  public slots:

    /**
     * \brief one of two opportunities to connect internal logic to signals
     * provided by an AbstractPin via an AbstractPinFactory.
     *
     * \param pins an AnstractPinFactory instance providing access to any pin
     * connected to the avr simulator.
     */
    virtual void connect(AbstractPinFactory* pins) = 0;

    /**
     * \brief one of two opportunities to connect internal logic to the IRQ
     * system provided by \em simavr.
     *
     * \param avr the core data structure for manipulating simavr simulation
     * instances
     */
    virtual void connect(avr_t* avr) = 0;

    /**
     * \brief used to disconnect the plugin logic from the avr simulation engine
     */
    virtual void disconnect() = 0;

    /**
     * \brief used to notify a plugin that a simulation is about to begin, this
     * is an opportunities to reset structures and data before a new simulation.
     */
    virtual void RESET() = 0;

  signals:

    /**
     * \brief plugins can emit messages which will be captured in a plugin log,
     * this system can be used to notify users of errors in the plugin
     *
     * \param error the message to be sent
     */
    void error(QString error);
};

Q_DECLARE_INTERFACE( AbstractPeripheralLogic, ABSTRACTPERIPHERALLOGIC_IDD )

#endif // ABSTRACTPERIPHERALLOGIC_H
