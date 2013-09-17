/**
 * \file PmodSevenSegWidget.cpp
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
#include "PmodSevenSegWidget.h"

#include <QtCore/QPoint>

PmodSevenSegWidget::~PmodSevenSegWidget()
{
  delete background;
  delete buffer;
}

PmodSevenSegWidget::PmodSevenSegWidget( int width, int height ) :
  width( width ), height( height )
{
  background = new QPixmap( width, height );
  updateBackground();

  buffer = new QPixmap( width, height );
  updateBuffer();
}

void PmodSevenSegWidget::updateSegments( int segments )
{

  if ( segments & ( 1 << 7 ) ) { // Cathode Switch
    segment0 = segments;
  } else {
    segment1 = segments;
  }

  updateBuffer();
}

void PmodSevenSegWidget::drawSegment( QPainter& painter, int display,
                                      int segments )
{

  int w = ( width - width / 5 - width / 10 ) / 2;
  int h = height - height / 10;

  int yoffset = height / 20;

  int xoffset = 0;

  if ( display == 0 ) {
    xoffset = width / 10;
  } else {
    xoffset = w + width / 5;
  }

  if ( segments & ( 1 << 3 ) ) // A
    painter.drawLine( xoffset, yoffset, xoffset + w, yoffset );

  if ( segments & ( 1 << 4 ) ) // B
    painter.drawLine( xoffset + w, yoffset, xoffset + w, yoffset + h / 2 );

  if ( segments & ( 1 << 5 ) ) // C
    painter.drawLine( xoffset + w, yoffset + h, xoffset + w, yoffset + h / 2 );

  if ( segments & ( 1 << 6 ) ) // D
    painter.drawLine( xoffset , yoffset + h, xoffset + w, yoffset + h );

  if ( segments & ( 1 << 0 ) ) // E
    painter.drawLine( xoffset , yoffset + h, xoffset , yoffset + h / 2 );

  if ( segments & ( 1 << 1 ) ) // F
    painter.drawLine( xoffset , yoffset, xoffset , yoffset + h / 2 );

  if ( segments & ( 1 << 2 ) ) // G
    painter.drawLine( xoffset , yoffset + h / 2, xoffset + w, yoffset + h / 2 );

}

void PmodSevenSegWidget::updateBackground( void )
{

  background->fill( Qt::lightGray );

  QPainter painter( background );

  QPen pen;

  pen.setWidth( width / 15 );
  pen.setBrush( Qt::gray );

  painter.setPen( pen );

  drawSegment( painter, 0, 0xFF );

  drawSegment( painter, 1, 0xFF );

  painter.end();

}

void PmodSevenSegWidget::resizeEvent( QResizeEvent *event )
{
  width = event->size().width();
  height = event->size().height();

  delete background;
  background = new QPixmap( width, height );
  updateBackground();

  delete buffer;
  buffer = new QPixmap( width, height ); updateBuffer();

  QWidget::resizeEvent( event );
}

QSize PmodSevenSegWidget::sizeHint() const
{
  return QSize( width, height );
}

void PmodSevenSegWidget::updateBuffer( void )
{

  QPainter painter( this->buffer );

  painter.drawPixmap( QPoint( 0, 0 ), *background );

  QPen pen;

  pen.setWidth( width / 20 );
  pen.setBrush( Qt::red );

  painter.setPen( pen );

  drawSegment( painter, 0, segment0 );

  drawSegment( painter, 1, segment1 );

  painter.end();

  update();
}

void PmodSevenSegWidget::paintEvent( QPaintEvent *event )
{
  ( void ) event;

  QPainter painter( this );

  painter.drawPixmap( QPoint( 0, 0 ), *buffer );

  painter.end();
}
