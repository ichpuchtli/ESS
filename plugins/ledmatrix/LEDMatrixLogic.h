/**
 * \file LEDMatrixLogic.h
 * \brief The logic implementation for the led matrix display
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
#ifndef LEDMATRIXLOGIC_H
#define LEDMATRIXLOGIC_H

#include <QtCore/QString>
#include <QtCore/QTimer>

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

/**
 * \brief The logic implementation for the led matrix display
 */
class LEDMatrixLogic: public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  LEDMatrixLogic();
  ~LEDMatrixLogic();


public slots:

  void poll();

  void connectNet( QString net, QString pin );

  QStringList getNets( void ) {
    return nets;
  }

  void attach( AVRIOAdapter* io ) {
    this->io = io;
  }

  void detach();

  void RESET();

signals:

  void stateChange( int row, int cols );

  void error( QString error );

private:

  QTimer* timer;
  int colCache[7];
  AbstractPin* pins[18];

  AVRIOAdapter* io;
  QStringList nets;
};

#endif // LEDMATRIXLOGIC_H
