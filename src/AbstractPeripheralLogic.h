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

#include "AVRIOAdapter.h"
#include "AbstractAVRProcessor.h"

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
     * \brief the opportunity to connect internal logic to signals
     * offered by AVRIOAdapter and friends
     *
     * \param io an AVRIOAdapter instance
     */
    virtual void connect(AVRIOAdapter* io) = 0;

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
     * \brief request the plugin manager to unload this plugin
     *
     * \param error the message to be sent
     */
    void error(QString error);
};

Q_DECLARE_INTERFACE( AbstractPeripheralLogic, ABSTRACTPERIPHERALLOGIC_IDD )

#endif // ABSTRACTPERIPHERALLOGIC_H
