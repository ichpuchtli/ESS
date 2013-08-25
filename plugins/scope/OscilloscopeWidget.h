/**
 * \file OscilloscopeWidget.h
 * \brief The widget implementation for a single channel oscilloscope
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
#ifndef OSCILLOSCOPEWIDGET_H
#define OSCILLOSCOPEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QSize>

#include "include/qcustomplot/qcustomplot.h"

/**
 * \brief The widget implementation for a single channel oscilloscope
*/
class OscilloscopeWidget : public QWidget
{

  Q_OBJECT

public:
  OscilloscopeWidget();
  ~OscilloscopeWidget();

  virtual QSize sizeHint() const;

public slots:
  void update( int voltage, long long time );

private:

  QCustomPlot* customPlot;

  int height, width;

protected:
  virtual void resizeEvent( QResizeEvent *event );

};

#endif // OSCILLOSCOPEWIDGET_H
