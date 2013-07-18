/**
 * \file GPIOPin.h
 * \brief an AbstractPin implementation for General Peripheral Input/Output pins
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

#ifndef GPIOPIN_H
#define GPIOPIN_H

#include "sim_avr.h"
#include "sim_irq.h"

#include "AbstractPin.h"

/**
 * \brief an AbstractPin implementation for General Peripheral Input/Output pins
 */
class GPIOPin : public AbstractPin
{

  Q_OBJECT
  Q_INTERFACES(AbstractPin)

public:
  /**
   * \brief constructs a GPIOPin instance identified by the port and pin
   * inside the identifier
   *
   * \param avr the avr_t instance for the avr processor
   * \param identifier the unique identifier for the pin, the structure is
   * P[A-G][0-7] all uppercase. For example PORT D Pin 1 would be \em "PD1"
   *
   * \see PinFactory::getGPIOPin( const char* )
   */
  GPIOPin(avr_t* avr, const char* identifier, QObject* parent = 0);

  /**
   * \brief constructs a GPIOPin instance identified by \em port and \em pin
   *
   * \param avr the avr_t instance for the avr processor
   * \param port the uppercase letter representing the desired port from [A-G]
   * \param pin the desired pin number along the port from [0-7]
   *
   * \see PinFactory::getGPIOPin( char, unsigned )
   */
  GPIOPin(avr_t* avr, char port, unsigned pin, QObject* parent = 0);

  ~GPIOPin();

  virtual int getLevel(void) const;
  virtual int getVoltage(void) const;

  /**
   * \brief get the direction of the pin
   *
   * \return the direction of the pin, a direction of 0 indicates this pin is
   * configured as an input, where a 1 indicates the pin is set as an output.
   */
  virtual int getDirection(void) const;

signals:

  void levelChange(int level);
  void voltageChange(int voltage);

  /**
   * \brief the signal to be emitted if the direction changes
   *
   * \param level the new direction for the pin either 0 or 1
   */
  void directionChange(int direction);

public slots:

  virtual void setLevel(int level);
  virtual void setVoltage(int voltage);

protected:

  /**
   * \brief this method is tied directly to simavr's irq system,
   * in the event of a pin change this method is called with the new pin level.
   * This method is responsible for emitting the corresponding signals.
   *
   * \param level the new pin level
   */
  void pinChangeEvent( int level );

  /**
   * \brief this method is tied directly to simavr's irq system,
   * in the event of a DDR change this method is called with the new pin
   * direction. This method is responsible for emitting the corresponding
   * signals.
   *
   * \param direction the new pin direction
   */
  void dirChangeEvent( int direction );

private:

  void init(void);

  static void pinChangeHook(struct avr_irq_t* irq, uint32_t value, void* param);
  static void ddrChangeHook(struct avr_irq_t* irq, uint32_t value, void* param);

  avr_t* avr;
  avr_irq_t* pin_irq;
  avr_irq_t* ddr_irq;

  char port, pin;

  int levelCache;
  int ddrCache;

  int voltageCache;

};

#endif // GPIOPIN_H
