/**
 * \file LEDMatrixWidget.h
 * \brief The widget implementation for the led matrix display
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
#ifndef LEDMATRIXWIDGET_H
#define LEDMATRIXWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtCore/QSize>

#include <QtGui/QResizeEvent>

/**
 * \brief The widget implementation for the led matrix display
*/
class LEDMatrixWidget : public QWidget
{

  Q_OBJECT

public:
  LEDMatrixWidget( int width = 300, int height = 140 );
  ~LEDMatrixWidget();

  virtual QSize sizeHint() const;

public slots:

  void updateMatrix( int row, int cols );

private:
  QPixmap* buffer;
  QPixmap* background;

  void updateBackground( void );
  void updateBuffer();

  int colCache[7] = {~0, ~0, ~0, ~0, ~0, ~0, ~0};

protected:

  virtual void resizeEvent( QResizeEvent *event );

  void paintEvent( QPaintEvent *event );

  int width, height;

};

#endif // LEDMATRIXWIDGET_H
