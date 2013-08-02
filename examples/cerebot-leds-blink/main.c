#include <avr/io.h>
#include "util/delay.h"

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

    OCR0 = 255;

    TCCR0 |= (0 << FOC0) | (0 << WGM01) | (0 << WGM00);

    TCCR0 |= (0 << COM01) | (0 << COM00);

    TCCR0 |= (1 << CS02) | (0 << CS01) | (1 << CS00);

    TIMSK |= (1 << OCIE0) | (0 << TOIE0);
}

void init_timer1(void){

    // CS12 CS11 CS10  Description
    //  0    0    0    No Clock Source (Timer/Counter stopped)
    //  0    0    1    No Prescaling
    //  0    1    0    clk/8
    //  0    1    1    clk/64
    //  1    0    0    clk/256
    //  1    0    1    clk/1024
    //  1    1    0    External T1 pin failing edge
    //  1    1    1    External T1 pin rising edge

    OCR1A = 4000;

    TCCR1A = 0;

    TCCR1B = (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);

    TIMSK |= (1<<OCIE1A)|(0<<OCIE1B)|(0<<TOIE1);
}

void init_timer2(void){

    // CS22 CS21 CS20  Description
    //  0    0    0    No Clock Source (Timer/Counter stopped)
    //  0    0    1    No Prescaling
    //  0    1    0    clk/8
    //  0    1    1    clk/32
    //  1    0    0    clk/64 
    //  1    0    1    clk/128
    //  1    1    0    clk/256
    //  1    1    1    clk/1024

    OCR2 = 255;

    TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);

    TIMSK |= (1 << OCIE2) | (0 << TOIE2);
}

int main(void) {

    DDRE = 0xF0;

    while(1) {

      _delay_ms(5);

      PORTE += 1;

    }

}
