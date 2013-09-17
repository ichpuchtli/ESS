/**
 * \file PmodSevenSegLogic.h
 * \brief The logic implementation for the pmod seven segment display
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
#ifndef PMODSEVENSEGLOGIC_H
#define PMODSEVENSEGLOGIC_H

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include "../../src/AbstractPeripheralLogic.h"
#include "../../src/AVRIOAdapter.h"

/**
 * \brief The logic implementation for the pmod seven segment display
 */
class PmodSevenSegLogic: public AbstractPeripheralLogic
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralLogic )

public:

  PmodSevenSegLogic();
  ~PmodSevenSegLogic();

public slots:

  QStringList getNets( void ) {
    return nets;
  }

  void connectNet( QString net, QString pin );

  void attach( AVRIOAdapter* io ) {
    this->io = io;
  }

  void detach();

  void RESET();

signals:

  void segmentChange( int segments );

  void error( QString error );

private slots:

  void poll();

  void startPolling();

  void stopPolling();

private:
  QTimer* timer;
  QStringList nets;

  AbstractPin* pins[8] = {0};
  AVRIOAdapter* io;

  uint8_t history1[5] = {0};
  uint8_t history2[5] = {0};
  int index1 = 0;
  int index2 = 0;
};

#endif // PMODSEVENSEGLOGIC_H
