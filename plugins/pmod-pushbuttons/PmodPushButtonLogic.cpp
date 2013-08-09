/**
 * \file PmodPushButtonLogic.cpp
 * \brief The logic implementation for the Pmod Push Buttons
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
#include "PmodPushButtonLogic.h"
#include <QRegularExpression>

PmodPushButtonLogic::PmodPushButtonLogic( QPushButton* btn0, QPushButton* btn1,
    QPushButton* btn2, QPushButton* btn3 ) :
  button {btn0, btn1, btn2, btn3} {
  this->netList << "BTN0" << "BTN1" << "BTN2" << "BTN3";
}

QStringList PmodPushButtonLogic::getNets()
{
  return this->netList;
}

PmodPushButtonLogic::~PmodPushButtonLogic()
{
}

void PmodPushButtonLogic::attach( AVRIOAdapter* io )
{

  this->io = io;

  this->connectNet( "BTN0", "PD4" );
  this->connectNet( "BTN1", "PD5" );
  this->connectNet( "BTN2", "PD6" );
  this->connectNet( "BTN3", "PD7" );

}

void PmodPushButtonLogic::connectNet( QString net, QString pin )
{

  int i = this->netList.indexOf( QRegularExpression( net ) );

  AbstractPin* aPin = &this->io->getGPIOPin( pin.toLatin1() );

  QObject::disconnect( this->button[i] );

  QObject::connect( this->button[i], SIGNAL( pressed() ), aPin,
                    SLOT( pullDown() ) );
  QObject::connect( this->button[i], SIGNAL( released() ), aPin,
                    SLOT( pullUp() ) );

  QMetaObject::invokeMethod( this->button[i], "released", Qt::DirectConnection );
}

void PmodPushButtonLogic::detach()
{
  for ( int i = 0; i < this->netList.count(); i++ ) {
    QObject::disconnect( this->button[i] );
  }
}

void PmodPushButtonLogic::RESET()
{

  QMetaObject::invokeMethod( this->button[0], "released", Qt::DirectConnection );
  QMetaObject::invokeMethod( this->button[1], "released", Qt::DirectConnection );
  QMetaObject::invokeMethod( this->button[2], "released", Qt::DirectConnection );
  QMetaObject::invokeMethod( this->button[3], "released", Qt::DirectConnection );

}
