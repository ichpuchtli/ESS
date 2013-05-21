/*
** FILE: led_display.h
**
** Functions and definitions to support the LED display
** module. 
**
*/

#include <avr/io.h>

/* Number of rows in our display */
#define NUM_ROWS 7

/* Our display data - indexed by row number 0 to 6
 * (from top to bottom). Bit 14 (second most significant 
 * bit)is the rightmost column. Bit 0 (least significant 
 * bit) is the leftmost column. Bit 15 (most significant bit) 
 * is unused. A bit value of 1 indicates the LED is lit.
 */
extern volatile uint16_t display[NUM_ROWS];

void init_display(void);
	/* Initialises the display, including setting data
	 * direction registers for the ports we use. The 15
	 * columns (numbered 0 to 14 from left to right) 
	 * are connected to bits 0 to 7 of port A (columns 0 to 7)
	 * and bits 0 to 6 of port C (columns 8 to 14). 
	 * (Bit 7 of port C is not used). 
	 * The row select is assumed to be the three least 
	 * significant bits of port G.
	 */

void display_row(void);
	/* Display the next row of data. Should be called every 
	 * millisecond or two to ensure that there is no perceptible
	 * display flicker.
	 */
