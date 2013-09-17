/**
 * \file PmodSevenSegWidget.h
 * \brief The widget implementation for the pmod seven segment display
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
#ifndef PMODSEVENSEGWIDGET_H
#define PMODSEVENSEGWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtCore/QSize>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>

/**
 * \brief The widget implementation for the pmod seven segment display
*/
class PmodSevenSegWidget : public QWidget
{

  Q_OBJECT

public:
  PmodSevenSegWidget( int width = 100, int height = 80 );
  ~PmodSevenSegWidget();

  virtual QSize sizeHint() const;

public slots:
  void updateSegments( int segments );

protected:

  virtual void resizeEvent( QResizeEvent *event );

  void paintEvent( QPaintEvent *event );

private:

  QPixmap* background;
  QPixmap* buffer;

  void updateBuffer( void );
  void updateBackground( void );
  void drawSegment( QPainter& painter, int display, int segments );

  int width, height;

  int segment0 = 0;
  int segment1 = 0;

};

#endif // PMODSEVENSEGWIDGET_H
