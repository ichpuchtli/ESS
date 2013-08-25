/**
 * \file OscilloscopeLogic.h
 * \brief The logic implementation for single channel oscilloscope
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
#ifndef OSCILLOSCOPELOGIC_H
#define OSCILLOSCOPELOGIC_H

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

/**
 * \brief The logic implementation for single channel oscilloscope
 */
class OscilloscopeLogic: public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  OscilloscopeLogic();
  ~OscilloscopeLogic();

  void connectNet( QString net, QString pin );

  QStringList getNets( void ) {
    return QStringList() << "Channel 1";
  }

public slots:

  void router( int voltage, char port, char pin );

  void attach( AVRIOAdapter* io );

  void detach();

  void RESET();

signals:
  void error( QString error );

  void newData( int voltage, long long time );

private:
  AVRIOAdapter* io;
  long long initial;
  char port;
  int pin;
};

#endif // OSCILLOSCOPELOGIC_H
