/**
 * \file factory.h
 * \brief a factory pattern class responsible for creating the CerebotII LED peripheral
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
#ifndef CEREBOTIILED_FACTORY_H
#define CEREBOTIILED_FACTORY_H

#include <QtCore/QtPlugin>
#include <QtWidgets/QWidget>

#include "../../src/AbstractPeripheralFactory.h"

#include "CerebotIILEDLogic.h"
#include "CerebotIILEDWidget.h"

class Factory : public AbstractPeripheralFactory
{

  Q_OBJECT

  Q_PLUGIN_METADATA( IID "CerebotII Onbord LEDs" )

  Q_INTERFACES( AbstractPeripheralFactory )

public:

  Factory() {}
  ~Factory() {}

  Peripheral getPeripheral( void ) {

    CerebotIILEDLogic* logic = new CerebotIILEDLogic();

    CerebotIILEDWidget* widget = new CerebotIILEDWidget();

    Peripheral periph = { logic, widget };

    connect( logic, &CerebotIILEDLogic::turnOnLED, widget,
             &CerebotIILEDWidget::turnOnLED );
    connect( logic, &CerebotIILEDLogic::turnOffLED, widget,
             &CerebotIILEDWidget::turnOffLED );

    return periph;

  }

  QString getDescription( void ) {
    return QString( "CerebotII Onbord LEDs" );
  }

  QString getVersion( void ) {
    return QString( "1.0" );
  }

};

#endif // CEREBOTIILED_FACTORY_H
