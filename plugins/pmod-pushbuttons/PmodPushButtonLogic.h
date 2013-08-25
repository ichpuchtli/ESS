/**
 * \file PmodPushButtonLogic.h
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
#ifndef PMODPUSHBUTTONLOGIC_H
#define PMODPUSHBUTTONLOGIC_H

#include <QtWidgets/QPushButton>

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

/**
 * \brief The logic implementation for the Pmod Push Buttons
 */
class PmodPushButtonLogic: public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  PmodPushButtonLogic( QPushButton* btn0, QPushButton* btn1, QPushButton* btn2,
                       QPushButton* btn3 );
  ~PmodPushButtonLogic();

  QStringList getNets( void );

public slots:

  void connectNet( QString net, QString pin );

  void attach( AVRIOAdapter* io );

  void detach();

  void RESET();

signals:

  void error( QString error );

private:

  QPushButton* button[4];

  AVRIOAdapter* io;

  QStringList netList;

};

#endif // PMODPUSHBUTTONLOGIC_H
