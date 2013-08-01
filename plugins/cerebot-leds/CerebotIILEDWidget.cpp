/**
 * \file CerebotIILEDWidget.cpp
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
#include "CerebotIILEDWidget.h"

#define CELL_PADDING ( 2 )

CerebotIILEDWidget::~CerebotIILEDWidget()
{
  delete this->background;
  delete this->buffer;
}

CerebotIILEDWidget::CerebotIILEDWidget( int width, int height )
  : width( width ), height( height )
{

  leds[0] = leds[1] = leds[2] = leds[3] = false;

  this->background = new QPixmap( this->width, this->height );

  this->background->fill( Qt::lightGray );

  this->buffer = new QPixmap( this->width, this->height );

  this->updateBuffer();
}


void CerebotIILEDWidget::resizeEvent( QResizeEvent *event )
{

  this->width = event->size().width();
  this->height = event->size().height();

  delete this->background;
  this->background = new QPixmap( this->width, this->height );
  this->background->fill( Qt::lightGray );

  delete this->buffer;
  this->buffer = new QPixmap( this->width, this->height );
  this->updateBuffer();

  QWidget::resizeEvent( event );

}

QSize CerebotIILEDWidget::sizeHint() const
{
  return QSize( this->width, this->height );
}

void CerebotIILEDWidget::updateBuffer( void )
{

  QPainter painter( this->buffer );

  // Start with the background
  painter.drawPixmap( QPoint( 0, 0 ), *this->background );

  if ( leds[0] ) {
    painter.fillRect( QRect( 0, height / 4 * 0 + CELL_PADDING, width,
                             height / 4 - CELL_PADDING ) , Qt::green );
  }

  if ( leds[1] ) {
    painter.fillRect( QRect( 0, height / 4 * 1 + CELL_PADDING, width,
                             height / 4 - CELL_PADDING ) , Qt::green );
  }

  if ( leds[2] ) {
    painter.fillRect( QRect( 0, height / 4 * 2 + CELL_PADDING, width,
                             height / 4 - CELL_PADDING ) , Qt::green );
  }

  if ( leds[3] ) {
    painter.fillRect( QRect( 0, height / 4 * 3 + CELL_PADDING, width,
                             height / 4 - CELL_PADDING ) , Qt::green );
  }

  painter.end();

  update();
}

void CerebotIILEDWidget::turnOffLED( int num )
{

  this->leds[num] = false;

  this->updateBuffer();
}

void CerebotIILEDWidget::turnOnLED( int num )
{

  this->leds[num] = true;

  this->updateBuffer();

}

void CerebotIILEDWidget::paintEvent( QPaintEvent *event )
{

  ( void ) event;

  QPainter painter( this );
  painter.drawPixmap( QPoint( 0, 0 ), *this->buffer );
  painter.end();

}
