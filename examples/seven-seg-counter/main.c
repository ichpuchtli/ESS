#include <avr/io.h>
#include </usr/avr/include/avr/interrupt.h>
#include <util/delay.h>

uint8_t ucTens = 0;
uint8_t ucSecs = 0;


void init_timer1( void )
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

  OCR1A = 7812;

  TCCR1A = 0;

  TCCR1B = ( 0 << WGM13 ) | ( 1 << WGM12 ) | ( 1 << CS12 ) | ( 0 << CS11 ) |
           ( 1 << CS10 );

  TIMSK |= ( 1 << OCIE1A ) | ( 0 << OCIE1B ) | ( 0 << TOIE1 );
}


void init_timer0( void )
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

  OCR0 = 255;

  TCCR0 |= ( 0 << FOC0 ) | ( 0 << WGM01 ) | ( 0 << WGM00 );

  TCCR0 |= ( 0 << COM01 ) | ( 0 << COM00 );

  TCCR0 |= ( 1 << CS02 ) | ( 1 << CS01 ) | ( 0 << CS00 );

  TIMSK |= ( 1 << OCIE0 ) | ( 0 << TOIE0 );
}

inline void setDigit( uint8_t ucDigit )
{

  static const uint8_t ucpLookup[ 10 ]  = {0xF3, 0x60, 0xB5, 0xF4, 0x66, 0xD6, 0xD7, 0x70, 0xF7, 0x76};

  if ( ucDigit > 9 ) {
    return;
  }

  PORTA &= 0x0F;
  PORTA |= ucpLookup[ ucDigit ] & 0xF0;

  PORTC &= 0x8F;
  PORTC |= ucpLookup[ ucDigit ] << 4;

}

inline void switchDisplay( void )
{
  PORTC ^= 0x80;
}

int main( void )
{

  DDRA |= 0xF0;
  DDRC |= 0xF0;

  init_timer0();
  init_timer1();

  sei();

  for ( ;; ) {
    asm( "nop" );
  }

  return 0;

}


ISR( TIMER0_COMP_vect )
{

  if ( PORTC & 0x80 ) {
    setDigit( ucSecs );
  } else {
    setDigit( ucTens );
  }

  switchDisplay();
}

ISR( TIMER1_COMPA_vect )
{

  static uint8_t i = 0;

  if ( i++ >= 99 ) i = 0;

  ucTens = i / 10;
  ucSecs = i % 10;

}
