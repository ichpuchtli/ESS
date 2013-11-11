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
    QPushButton* btn2, QPushButton* btn3 )
{

  button[0] = btn0;
  button[1] = btn1;
  button[2] = btn2;
  button[3] = btn3;

  this->netList << "BTN1" << "BTN2" << "BTN3" << "BTN4";

}

QStringList PmodPushButtonLogic::getNets()
{
  return netList;
}

PmodPushButtonLogic::~PmodPushButtonLogic()
{
  detach();
}

void PmodPushButtonLogic::attach( AVRIOAdapter* io )
{
  this->io = io;
}

void PmodPushButtonLogic::connectNet( QString net, QString pin )
{

  int i = netList.indexOf( QRegularExpression( net ) );

  AbstractPin* aPin = &io->getGPIOPin( pin.toLatin1() );

  disconnect( button[i], 0, 0, 0 );

  connect( button[i], SIGNAL( pressed() ), aPin, SLOT( pullUp() ) );

  connect( button[i], SIGNAL( released() ), aPin, SLOT( pullDown() ) );

  button[i]->released();
}

void PmodPushButtonLogic::detach()
{
  for ( int i = 0; i < netList.count(); i++ ) {
    disconnect( button[i] );
  }
}

void PmodPushButtonLogic::RESET()
{
  for ( int i = 0; i < netList.count(); i++ ) {
    button[i]->released();
  }
}
