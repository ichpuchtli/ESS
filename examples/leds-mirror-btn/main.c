#include <avr/io.h>

int main( void )
{

  DDRE |= 0xF0;

  DDRD &= 0x0F;

  while ( 1 ) {

    PORTE = PIND;

  }

  return 0;
}
