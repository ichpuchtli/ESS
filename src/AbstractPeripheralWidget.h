/**
 * \file AbstractPeripheralWidget.h
 * \brief an abstract base class for representing peripheral widgets
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
#ifndef ABSTRACTPERIPHERALWIDGET_H
#define ABSTRACTPERIPHERALWIDGET_H

#include <QWidget>
#include <QString>

#define ABSTRACTPERIPHERALWIDGET_IDD "ESS.AbstractPeripheralWidget/1.0"

/**
 * \brief an abstract base class for representing peripheral widgets
 */
class AbstractPeripheralWidget : public QWidget {

  Q_OBJECT

  public:

    virtual ~AbstractPeripheralWidget() {}

  public slots:

    /**
     * \brief used to notify a plugin that a simulation is about to begin, this
     * is an opportunities to reset structures and data before a new simulation.
     */
    virtual void RESET() = 0;

  signals:

    /**
     * \brief plugins can emit messages which will be captured in a plugin log,
     * this system can be used to notify users of errors in the plugin
     *
     * \param error the message to be sent
     */
    void error(QString error);
};

Q_DECLARE_INTERFACE( AbstractPeripheralWidget, ABSTRACTPERIPHERALWIDGET_IDD )

#endif // ABSTRACTPERIPHERALWIDGET_H
