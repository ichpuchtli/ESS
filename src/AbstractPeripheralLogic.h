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
#include <QStringList>

#include "AVRIOAdapter.h"
#include "AbstractAVRProcessor.h"

#define ABSTRACTPERIPHERALLOGIC_IDD "ESS.AbstractPeripheralLogic/1.0"

/**
 * \brief An abstract base class for representing peripheral logic interactions
 */
class AbstractPeripheralLogic : public QObject
{

  Q_OBJECT

public:

  virtual ~AbstractPeripheralLogic() {}

  /**
   * \brief select which nets connect to which pins, the available pins
   * can be determined by getNets( void ). Pin names should conform to
   * AVRIOAdpater::getGPIOPin( char* ) pin descriptions.
   *
   * \param net a string description of a peripheral end point
   * \param pin the pin you want to connect to the net to
   *
   * \see getNets( void )
   */
  virtual void connectNet( QString net, QString pin ) = 0;

  /**
   * \brief returns a list of nets ( terminals, end points ) that the
   * peripheral needs to function. These nets can then be used to
   * select which pins connect to which nets. For instance a SPI based
   * peripheral may have the nets MISO, MOSI, CLK and SS
   *
   * \see selectNet( QString, QString )
   *
   * \return a string list of available nets
   */
  virtual QStringList getNets( void ) = 0;

public slots:

  /**
   * \brief used to attach/detach the peripheral from the avr .
   *
   * \param io an AVRIOAdapter instance
   */
  virtual void attach( AVRIOAdapter* io ) = 0;

  /**
   * \brief used to detach the peripheral from the avr.
   */
  virtual void detach() = 0;

  /**
   * \brief used to notify a plugin that a simulation is about to begin, this
   * is an ideal time to reset structures and data before a new simulation.
   */
  virtual void RESET() = 0;


signals:

  /**
   * \brief request the plugin manager to unload this plugin
   *
   * \param error the message to be sent
   */
  void error( QString error );
};

Q_DECLARE_INTERFACE( AbstractPeripheralLogic, ABSTRACTPERIPHERALLOGIC_IDD )

#endif // ABSTRACTPERIPHERALLOGIC_H
