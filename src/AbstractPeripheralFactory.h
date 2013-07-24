/**
 * \file AbstractPeripheralFactory.h
 * \brief a abstract factory pattern used to instantiate the peripheral components
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

#ifndef ABSTRACTPERIPHERALFACTORY_H
#define ABSTRACTPERIPHERALFACTORY_H

#include <QObject>
#include <QString>

#include "AbstractPeripheralLogic.h"
#include "AbstractPeripheralWidget.h"

#define ABSTRACTPERIPHERALFACTORY_IDD "ESS.AbstractPeripheralFactory/1.0"

/**
 * \brief Peripheral structure combines logic and widget components for conveniences
 */
struct Peripheral {
  AbstractPeripheralLogic* logic;
  AbstractPeripheralWidget* widget;
};

/**
 * \brief a abstract factory pattern used to instantiate the peripheral components
 */
class AbstractPeripheralFactory : public QObject
{

public:

  virtual ~AbstractPeripheralFactory() {}

  /**
   * \brief creates a Peripheral structure containing pointers to the
   * plugin components. Connecting the logic and widget components should
   * be done with a Qt::QueuedConnection since the logic component will
   * will be moved to the cpu thread.
   *
   * \see Plugin Development
   * \return Peripheral structure by value
   */
  virtual Peripheral getPeripheral( void ) = 0;

  /**
   * \return a string containing a brief unformatted description of the plugin
   */
  virtual QString getDescription( void ) = 0;

  /**
   * \return a string containing unformatted version information
   */
  virtual QString getVersion( void ) = 0;

};

Q_DECLARE_INTERFACE( AbstractPeripheralFactory, ABSTRACTPERIPHERALFACTORY_IDD )

#endif
