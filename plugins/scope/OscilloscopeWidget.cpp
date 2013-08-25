/**
 * \file OscilloscopeWidget.cpp
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
#include "OscilloscopeWidget.h"
#include <QVBoxLayout>

OscilloscopeWidget::~OscilloscopeWidget() { }

OscilloscopeWidget::OscilloscopeWidget() : height( 400 ), width( 600 )
{

  QVBoxLayout* verticalLayout = new QVBoxLayout( this );

  verticalLayout->setContentsMargins( 0, 0, 0, 0 );

  this->customPlot = new QCustomPlot();

  verticalLayout->addWidget( customPlot );

  customPlot->addGraph();
  customPlot->graph( 0 )->setPen( QPen( Qt::cyan ) );
  customPlot->graph( 0 )->setLineStyle( QCPGraph::lsStepLeft );

  customPlot->xAxis->setTickLabelType( QCPAxis::ltNumber );
  customPlot->xAxis->setAutoTickStep( false );
  customPlot->xAxis->setTickStep( 0.5 );

  customPlot->axisRect()->setupFullAxesBox();

  customPlot->yAxis->setRange( -100.0f, 5000.0f );

  // make left and bottom axes transfer their ranges to right and top axes:
  connect( customPlot->xAxis, SIGNAL( rangeChanged( QCPRange ) ),
           customPlot->xAxis2, SLOT( setRange( QCPRange ) ) );

}

void OscilloscopeWidget::update( int voltage , long long time )
{

  double key = double( time ) / 1000000;
  double value = double( voltage );

  // add data to lines:
  customPlot->graph( 0 )->addData( key, value );

  // remove data of lines that's outside visible range:
  customPlot->graph( 0 )->removeDataBefore( key - 10 );

  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange( key + 0.5, 10, Qt::AlignRight );
  customPlot->replot();

}

void OscilloscopeWidget::resizeEvent( QResizeEvent *event )
{

  this->width = event->size().width();
  this->height = event->size().height();

  QWidget::resizeEvent( event );

}
QSize OscilloscopeWidget::sizeHint() const
{
  return QSize( this->height, this->height );
}
