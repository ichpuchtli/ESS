/**
 * \file HybridAVRProcessor.h
 * \brief A simulation stategy using bundled execuation at frequent intervals
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

#ifndef HYBRIDAVRPROCESSOR_H
#define HYBRIDAVRPROCESSOR_H

#include "AVRProcessor.h"

#include <QtCore/QTimer>

/**
 * \brief A simulation strategy using bundled execution at frequent intervals
 */
class HybridAVRProcessor : public AVRProcessor
{

  Q_INTERFACES( AVRProcessor )

public:
  HybridAVRProcessor( const QString& mmcu, unsigned frequency ) :
    AVRProcessor( mmcu, frequency ) {}

public slots:

  void run( void );

private:

  QTimer* timer;

  void update( void );
};

#endif
