/**
 * \file LEDMatrixWidget.cpp
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
#include "LEDMatrixWidget.h"
#include <QTransform>

LEDMatrixWidget::~LEDMatrixWidget()
{
  delete this->background;
  delete this->buffer;
}

LEDMatrixWidget::LEDMatrixWidget( int width, int height )
  : rotated( false ), width( width ), height( height )
{

  memset( ( void* ) colCache, ~0, 7 * sizeof( int ) );

  background = new QPixmap( this->width, this->height );
  updateBackground();

  buffer = new QPixmap( this->width, this->height );
  updateBuffer();

  setFocusPolicy( Qt::ClickFocus );
}

void LEDMatrixWidget::resizeEvent( QResizeEvent *event )
{

  if ( rotated ) {
    height = event->size().width();
    width = event->size().height();
  } else {
    width = event->size().width();
    height = event->size().height();
  }

  delete background;
  background = new QPixmap( width, height );
  updateBackground();

  delete buffer;
  buffer = new QPixmap( width, height );
  updateBuffer();

  QWidget::resizeEvent( event );

}

QSize LEDMatrixWidget::sizeHint() const
{
  return QSize( width, height );
}

void LEDMatrixWidget::updateBackground( void )
{

  background->fill( Qt::lightGray );

  QPainter painter( background );

  float xpadding = width / 100.0;
  float ypadding = height / 100.0;

  float rectWidth = ( 0.84 * width / 15.0 );

  float rectHeight = ( 0.92 * height / 7.0 );

  for ( int row = 0; row < 7; row++ ) {

    for ( int col = 0; col < 15; col++ ) {

      painter.fillRect( ( int )( xpadding + col * ( rectWidth + xpadding ) ),
                        ( int )( ypadding + row * ( rectHeight + ypadding ) ),
                        ( int )rectWidth, ( int )rectHeight, Qt::gray );

    }

  }

  painter.end();

}

void LEDMatrixWidget::updateMatrix( int row, int cols )
{
  colCache[row] = cols;

  updateBuffer();
}

void LEDMatrixWidget::updateBuffer()
{

  QPainter painter( buffer );

  // Start with the background
  painter.drawPixmap( QPoint( 0, 0 ), *background );

  float xpadding = width / 100.0;
  float ypadding = height / 100.0;

  float rectWidth = ( 0.84 * width / 15.0 );

  float rectHeight = ( 0.92 * height / 7.0 );

  for ( int row = 0; row < 7; row++ ) {

    for ( int col = 0; col < 15; col++ ) {

      if ( colCache[row] & ( 1 << col ) ) {
        continue;
      }

      painter.fillRect( ( int )( xpadding + col * ( rectWidth + xpadding ) ),
                        ( int )( ypadding + row * ( rectHeight + ypadding ) ),
                        ( int )rectWidth, ( int )rectHeight, Qt::red );

    }
  }

  painter.end();

  update();
}

void LEDMatrixWidget::paintEvent( QPaintEvent *event )
{

  ( void ) event;

  QPainter painter( this );

  QTransform rotation;

  rotation = rotation.rotate( rotated ? 270 : 0 );

  QPixmap rotated = QPixmap( buffer->transformed( rotation ) );

  painter.drawPixmap( QPoint( 0, 0 ), rotated );

  painter.end();

}

void LEDMatrixWidget::keyPressEvent( QKeyEvent* event )
{

  if ( event->key() == Qt::Key_R ) {

    rotated = !rotated;

    resize( height, width );

    updateGeometry();

    resize( width, height );

  } else {
    QWidget::keyPressEvent( event );
  }

}
