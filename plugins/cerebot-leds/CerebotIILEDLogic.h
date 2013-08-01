/**
 * \file CerebotIILEDLogic.h
 * \brief The logic implementation for the cerebotII onboard led's
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
#ifndef CEREBOTIILEDLOGIC_H
#define CEREBOTIILEDLOGIC_H

#include <QtCore/QObject>

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

#include "../utils/LEDLogic.h"

/**
 * \brief The logic implementation for the cerebotII onboard led's
 */
class CerebotIILEDLogic: public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  CerebotIILEDLogic();
  ~CerebotIILEDLogic();

public slots:

  void connect( AVRIOAdapter* io );

  void disconnect();

  void RESET();

  void router( int voltage, char port, char pin );

signals:

  void error( QString error );

  void turnOnLED( int num );

  void turnOffLED( int num );

private:
  LEDLogic* leds[4];
  AVRIOAdapter* io;
};

#endif // CEREBOTIILEDLOGIC_H
