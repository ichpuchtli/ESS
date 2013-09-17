/*
** FILE: scrolling_char_display.h
**
*/

#include <avr/pgmspace.h>

void set_display_text(char* string);
/* Sets the text to be displayed. The message will
 * be displayed after the current message (if any). (Only
 * one message can be queued for display (i.e. to be
 * displayed after the current message) - from the last
 * call to this function.)
 */

uint8_t scroll_display(void);
/* Scroll the display. Should be called whenever the display
 * is to be scrolled one bit to the left. It is assumed that
 * this happens much less frequently than display_row() is
 * called. (This accesses the LED "display" value directly.)
 * Returns 1 if display is scrolled, 0 if scrolled message
 * is complete.
 */
