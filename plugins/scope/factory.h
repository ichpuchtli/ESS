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
#ifndef OSCILLOSCOPE_FACTORY_H
#define OSCILLOSCOPE_FACTORY_H

#include <QtCore/QtPlugin>
#include <QtWidgets/QWidget>

#include "../../src/AbstractPeripheralFactory.h"

#include "OscilloscopeLogic.h"
#include "OscilloscopeWidget.h"

class Factory : public AbstractPeripheralFactory
{

  Q_OBJECT

  Q_PLUGIN_METADATA( IID "Single Channel Scope" )

  Q_INTERFACES( AbstractPeripheralFactory )

public:

  Factory() {}
  ~Factory() {}

  Peripheral getPeripheral( void ) {

    OscilloscopeLogic* logic = new OscilloscopeLogic();

    OscilloscopeWidget* widget = new OscilloscopeWidget();

    QObject::connect( logic, SIGNAL( newData( int, long long ) ),
                      widget, SLOT( update( int, long long ) ) );

    Peripheral periph = { logic, widget };

    return periph;

  }

  QString getDescription( void ) {
    return QString( "Single Channel Scope" );
  }

  QString getVersion( void ) {
    return QString( "1.0" );
  }

};

#endif // OSCILLOSCOPE_FACTORY_H
