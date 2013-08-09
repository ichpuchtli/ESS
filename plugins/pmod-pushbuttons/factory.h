/**
 * \file factory.h
 * \brief a factory pattern class for creating Pmod PushButton peripherals
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
#ifndef PMODPUSHBUTTON_FACTORY_H
#define PMODPUSHBUTTON_FACTORY_H

#include <QtCore/QtPlugin>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

#include "../../src/AbstractPeripheralFactory.h"

#include "PmodPushButtonLogic.h"

class Factory : public AbstractPeripheralFactory
{

  Q_OBJECT

  Q_PLUGIN_METADATA( IID "Pmod-PushButtons" )

  Q_INTERFACES( AbstractPeripheralFactory )

public:

  Factory() {}
  ~Factory() {}

  Peripheral getPeripheral( void ) {

    QWidget* widget = new QWidget();

    QPushButton* btn0 = new QPushButton( QString( '0' ), widget );
    QPushButton* btn1 = new QPushButton( QString( '1' ), widget );
    QPushButton* btn2 = new QPushButton( QString( '2' ), widget );
    QPushButton* btn3 = new QPushButton( QString( '3' ), widget );

    PmodPushButtonLogic* logic = new PmodPushButtonLogic( btn0, btn1, btn2, btn3 );

    QGridLayout* grid = new QGridLayout( widget );

    grid->addWidget( btn0, 0, 0 );
    grid->addWidget( btn1, 0, 1 );
    grid->addWidget( btn2, 1, 0 );
    grid->addWidget( btn3, 1, 1 );

    return { logic, widget };

  }

  QString getDescription( void ) {
    return QString( "Pmod-PushButtons" );
  }

  QString getVersion( void ) {
    return QString( "1.0" );
  }

};

#endif // PMODPUSHBUTTON_FACTORY_H
