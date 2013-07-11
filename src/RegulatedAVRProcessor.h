/**
 * \file RegulatedAVRProcessor.h
 * \brief a processor strategy using loop delays to achieve accurate speeds
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

#ifndef REGULATEDAVRPROCESSOR_H
#define REGULATEDAVRPROCESSOR_H

#include "AVRProcessor.h"

/**
 * \brief a processor strategy using loop delays to achieve accurate speeds
 */
class RegulatedAVRProcessor : public AVRProcessor {

  Q_INTERFACES(AVRProcessor)

  public slots:

    void run(void);

  /**
   * \brief simple loop delay (spin delay, spin counter, etc)
   *
   * \param count the number of \em nop's to execute to create a significant
   * delay
   */
  static inline void loop_delay(unsigned int count){

    while(count--) asm("nop");

  }

};

#endif
