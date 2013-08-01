/**
 * \file CerebotIILEDWidget.h
 * \brief The widget implementation for the cerebotII onboard led's
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
#ifndef CEREBOTIILEDWIDGET_H
#define CEREBOTIILEDWIDGET_H

#include <QtCore/QObject>

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtCore/QSize>

#include <QResizeEvent>

#include "../../src/AbstractPeripheralWidget.h"

/**
 * \brief The widget implementation for the cerebotII onboard led's
*/
class CerebotIILEDWidget : public AbstractPeripheralWidget
{

  Q_OBJECT
  Q_INTERFACES( AbstractPeripheralWidget )

public:
  CerebotIILEDWidget( int width = 25, int height = 100 );
  ~CerebotIILEDWidget();

  virtual QSize sizeHint() const;

public slots:

  void turnOnLED( int num );

  void turnOffLED( int num );

  void RESET() {}

private:

  QPixmap* background;
  QPixmap* buffer;

  void updateBuffer( void );


protected:

  virtual void resizeEvent( QResizeEvent *event );

  void paintEvent( QPaintEvent *event );

  bool leds[4];
  int width, height;

};

#endif // CEREBOTIILEDWIDGET_H
