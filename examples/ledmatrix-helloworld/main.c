#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "led_display.h"
#include "scrolling_char_display.h"

void init_timer0(void)
{
  // CS02 CS01 CS00  Description
  //  0    0    0    No Clock Source (Timer/Counter stopped)
  //  0    0    1    No Prescaling
  //  0    1    0    clk/8
  //  0    1    1    clk/32
  //  1    0    0    clk/64
  //  1    0    1    clk/128
  //  1    1    0    clk/256
  //  1    1    1    clk/1024

  // Freq = F_CPU / prescaler / OCR0A

  OCR0 = 128;

  TCCR0 |= (0 << FOC0) | (0 << WGM01) | (0 << WGM00);

  TCCR0 |= (0 << COM01) | (0 << COM00);

  TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);

  TIMSK |= (1 << OCIE0) | (0 << TOIE0);
}

void init_timer1(void)
{

  // CS12 CS11 CS10  Description
  //  0    0    0    No Clock Source (Timer/Counter stopped)
  //  0    0    1    No Prescaling
  //  0    1    0    clk/8
  //  0    1    1    clk/64
  //  1    0    0    clk/256
  //  1    0    1    clk/1024
  //  1    1    0    External T1 pin failing edge
  //  1    1    1    External T1 pin rising edge

  // Freq = F_CPU / prescaler / OCR1A

  OCR1A = 7000;

  TCCR1A = 0;

  TCCR1B = (0 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10);

  TIMSK |= (1 << OCIE1A) | (0 << OCIE1B) | (0 << TOIE1);
}

int main(void)
{

  init_display();

  set_display_text("Hello World");

  init_timer0();
  init_timer1();

  sei();

  for ( ; ; ){ asm( "nop" ); }

  return 0;
}

ISR(TIMER0_COMP_vect)
{
  (void) display_row();
}

ISR(TIMER1_COMPA_vect)
{
  (void) scroll_display();
}
