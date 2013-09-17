/*
** FILE: led_display.c
**
** Original version by Peter Sutton
**
** Module that implements our LED display. We assume that
** lines for columns 0 to 7 are connected to AVR port A
** (bits 0 to 7) and that the lines for columsn 8 to 14
** are connected to AVR port C (bits 0 to 6). Bit 7 of
** port C is unused. The row signals (3 bits, 0 to 2) are
** connected to port G (bits 0 to 2).
**
*/

#include "led_display.h"
#include <avr/io.h>

/* Global variable - see comment in header file */
volatile uint16_t display[NUM_ROWS];

void init_display(void)
{
  uint8_t i;

  /* Set ports A and C to be outputs (except most significant
   * bit of port C) */
  DDRA = 0xFF;
  DDRC = 0x7F;

  /* Set 3 least significant bits of port G to be outputs */
  DDRG = 0x07;

  /* Empty the display */
  for (i = 0; i < NUM_ROWS; i++) {
    display[i] = 0;
  }
}

void display_row(void)
{
  /* Keep track of the row number we're up to. ("static"
   * indicates that the variable value will be remembered
   * from one function execution to the next.)
   */
  static uint8_t row = 0;

  /* Increment our row number (and wrap around if necessary) */
  if (++row == NUM_ROWS) {
    row = 0;
  }

  /* Output our row number to port G. This assumes the other
   * bits of port G are not being used. If they are, then
   * this line of code needs to be changed.
   */
  PORTG = row;

  /* Output the correct row data to ports A and C. (Port C gets
   * the high byte, port A gets the low byte.) We need to invert
   * the data since we need a low output for the LED to be lit.
   * Note - most significant bit is not displayed/used.
   */
  PORTA = ~(uint8_t)(display[row] & 0xFF);
  PORTC = ~(uint8_t)((display[row] >> 8) & 0X7F);
}
