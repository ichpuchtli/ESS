/**
 * \file LEDMatrixLogic.cpp
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
#include "LEDMatrixLogic.h"

#include <QtCore/QRegularExpression>

#define POLL_PERIOD 0

LEDMatrixLogic::LEDMatrixLogic() : timer( new QTimer( this ) )
{

  nets << "row0" << "row1" << "row2" << "col0" << "col1" << "col2"
       << "col3" << "col4" << "col5" << "col6" << "col7" << "col8"
       << "col9" << "col10" << "col11" << "col12" << "col13" << "col14";

  connect( timer, SIGNAL( timeout() ), this, SLOT( poll() ) );
}

LEDMatrixLogic::~LEDMatrixLogic()
{
  detach();
  delete timer;
}

void LEDMatrixLogic::poll( void )
{

  int row, cols;

  row = pins[0] ? pins[0]->getLevel() : 0;
  row |= ( pins[1] ? pins[1]->getLevel() : 0 ) << 1;
  row |= ( pins[2] ? pins[2]->getLevel() : 0 ) << 2;

  cols = ( pins[3] ?  pins[3]->getLevel() : 0 );
  cols |= ( pins[4] ?  pins[4]->getLevel() : 0 ) << 1;
  cols |= ( pins[5] ?  pins[5]->getLevel() : 0 ) << 2;
  cols |= ( pins[6] ?  pins[6]->getLevel() : 0 ) << 3;
  cols |= ( pins[7] ?  pins[7]->getLevel() : 0 ) << 4;
  cols |= ( pins[8] ?  pins[8]->getLevel() : 0 ) << 5;
  cols |= ( pins[9] ?  pins[9]->getLevel() : 0 ) << 6;
  cols |= ( pins[10] ? pins[10]->getLevel() : 0 ) << 7;
  cols |= ( pins[11] ? pins[11]->getLevel() : 0 ) << 8;
  cols |= ( pins[12] ? pins[12]->getLevel() : 0 ) << 9;
  cols |= ( pins[13] ? pins[13]->getLevel() : 0 ) << 10;
  cols |= ( pins[14] ? pins[14]->getLevel() : 0 ) << 11;
  cols |= ( pins[15] ? pins[15]->getLevel() : 0 ) << 12;
  cols |= ( pins[16] ? pins[16]->getLevel() : 0 ) << 13;
  cols |= ( pins[17] ? pins[17]->getLevel() : 0 ) << 14;

  if ( colCache[row] != cols ) {
    emit stateChange( row, cols );
  }

  colCache[row] = cols;
}

void LEDMatrixLogic::connectNet( QString net, QString pin )
{

  char port = pin.toLatin1()[1];
  unsigned char pin_num = pin.toLatin1()[2] - '0';

  int index = nets.indexOf( QRegularExpression( net ) );

  if ( index >= 0 && index < 18 ) {
    pins[index] = &this->io->getGPIOPin( port, pin_num );
  }

}

void LEDMatrixLogic::detach()
{
  timer->stop();
}

void LEDMatrixLogic::RESET()
{
  timer->start( POLL_PERIOD );

  for ( int i = 0; i < 7; i++ ) {
    colCache[i] = 0;
  }
}
