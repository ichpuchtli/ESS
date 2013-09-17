/**
 * \file factory.h
 * \brief a factory pattern class responsible for creating the pmod seven segment peripheral
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
#ifndef PMODSEVENSEG_FACTORY_H
#define PMODSEVENSEG_FACTORY_H

#include <QtCore/QtPlugin>
#include <QtWidgets/QWidget>

#include "../../src/AbstractPeripheralFactory.h"

#include "PmodSevenSegLogic.h"
#include "PmodSevenSegWidget.h"

class Factory : public AbstractPeripheralFactory
{

  Q_OBJECT

  Q_PLUGIN_METADATA( IID "Pmod Seven Seg" )

  Q_INTERFACES( AbstractPeripheralFactory )

public:

  Factory() {}
  ~Factory() {}

  Peripheral getPeripheral( void ) {

    PmodSevenSegLogic* logic = new PmodSevenSegLogic();

    PmodSevenSegWidget* widget = new PmodSevenSegWidget();

    connect( logic, SIGNAL( segmentChange( int ) ), widget,
             SLOT( updateSegments( int ) ) );

    Peripheral periph = { logic, widget };

    return periph;

  }

  QString getDescription( void ) {
    return QString( "Pmod Seven Seg" );
  }

  QString getVersion( void ) {
    return QString( "1.0" );
  }

};

#endif // PMODSEVENSEG_FACTORY_H
