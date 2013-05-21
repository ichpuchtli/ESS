#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "led_display.h"
#include "scrolling_char_display.h"

/*
 * This demonstrate how to use the avr_mcu_section.h file
 * The macro adds a section to the ELF file with useful
 * information for the simulator
 */
#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega64");
AVR_MCU_VOLTAGES(3300,3300,3300); // 3.3V Vcc, AVcc, Vref

/*
 * This small section tells simavr to generate a VCD trace dump with changes to these
 * registers.
 */
const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
	{ AVR_MCU_VCD_SYMBOL("LOOP"), .mask = (1 << 0), .what = (void*)&PORTF, },
	{ AVR_MCU_VCD_SYMBOL("TIMER0"), .mask = (1 << 1), .what = (void*)&PORTF, },
	{ AVR_MCU_VCD_SYMBOL("TIMER1"), .mask = (1 << 2), .what = (void*)&PORTF, },
	{ AVR_MCU_VCD_SYMBOL("TIMER2"), .mask = (1 << 3), .what = (void*)&PORTF, },
};

void init_ADC(void){

    // ADC voltage reference
    // REFS1 REFS0 Description
    //  0     0    AREF
    //  0     1    AVcc
    //  1     0    Reserved
    //  1     1    Internal 1.1V
 
    // When ADLAR = 1 (Left Adjusted)
    //---------------------------------------------------------
    //| ADC9 | ADC8 | ADC7 | ADC6 | ADC5 | ADC4 | ADC3 | ADC2 | ADCH
    //---------------------------------------------------------
    //| ADC1 | ADC0 |      |      |      |      |      |      | ADCL
    //---------------------------------------------------------

    // ADCH:ADCL = Vin * 1024 / VREF << 6
    
    // When ADLAR = 0
    //---------------------------------------------------------
    //|      |      |      |      |      |      | ADC9 | ADC8 | ADCH
    //---------------------------------------------------------
    //| ADC7 | ADC6 | ADC5 | ADC4 | ADC3 | ADC2 | ADC1 | ADC0 | ADCL
    //---------------------------------------------------------

    // ADCH:ADCL = Vin * 1024 / VREF
    
    // Aref, No left adjust suitable for 10bit accumulation 
    ADMUX = (0<<REFS1)|(0<<REFS0)|(0<<ADLAR);

    // Select ADC Channel 0 Initially
    ADMUX |= 0;

    // ADC Prescaler Selections
    // ADPS2 ADPS1 ADPS0 Division Factor
    //   0     0     0          2
    //   0     0     1          2
    //   0     1     0          4
    //   0     1     1          8
    //   1     0     0         16
    //   1     0     1         32
    //   1     1     0         64
    //   1     1     1        128
    
    // Enable ADC, Enable Interrupt and 128 clk division factor
    ADCSRA = (1<<ADEN)|(0<<ADSC)|(0<<ADATE)|(1<<ADIE)|(0<<ADPS2)|(0<<ADPS1)|(1<<ADPS0);

    // ADC Auto Trigger Sources
    // ADTS2 ADTS1 ADTS0 Trigger Source
    //  0    0     0    Free Running mode
    //  0    0     1    Analog Comparator
    //  0    1     0    External Interrupt Request 0
    //  0    1     1    Timer/Counter0 Compare Match A
    //  1    0     0    Timer/Counter0 Overflow
    //  1    0     1    Timer/Counter1 Compare Match B
    //  1    1     0    Timer/Counter1 Overflow
    //  1    1     1    Timer/Counter1 Capture Event

    // Timer/Counter 0 prepared for 38Hz ADC polling
    ADCSRB = (0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
}

void trigger_ADC(uint8_t channel){

    // Clear MUX
    ADMUX  &= 0xF0; 

    // Enable Channel
    ADMUX  |= ( channel & 0x0F );

    // Start Conversion
    ADCSRA |= (1<<ADSC);
}

uint8_t read_ADC(uint8_t channel){

    trigger_ADC(channel);

    // Wait for Conversion to finish
    while(ADCSRA & (1 << ADSC));

    // Return ADC Value
    return ADCH;
}

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
    
    OCR0 = 255;

    TCCR0 |= (0 << FOC0) | (0 << WGM01) | (0 << WGM00);

    TCCR0 |= (0 << COM01) | (0 << COM00);

    TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);

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
 
    // Freq = F_CPU / prescaler / OCR1A

    OCR1A = 31250;

    TCCR1A = 0;

    TCCR1B = (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);

    TIMSK |= (1<<OCIE1A)|(0<<OCIE1B)|(0<<TOIE1);
}

void init_timer2(void){

    // Freq = F_CPU / prescaler / 2 * OCR2A
    // OCR2A = F_CPU / prescaler / Freq / 2 

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

    /*
    init_timer0(); 
    init_timer1(); 
    init_timer2();

    //init_ADC();

    DDRF = 0xFF;

    PORTE = SIMAVR_CMD_VCD_START_TRACE;

    sei();

    while(1) {

        PORTF ^= (1 << 0);

        _delay_ms(1);

    }
    */

    init_display();

    set_display_text("Hello World!");

    init_timer0(); 
    init_timer1(); 

    sei();

    for(;;) asm("nop");

    cli();

    sleep_cpu();

    return 0;
}

ISR(TIMER0_COMP_vect){

    (void) display_row();
    PORTF ^= (1 << 1);
}

ISR(TIMER1_COMPA_vect){

    (void) scroll_display();

    PORTF ^= (1 << 2);
}

ISR(TIMER2_COMP_vect){

    PORTF ^= (1 << 3);
}

ISR(ADC_vect){

    uint16_t value = (ADCH << 8) + ADCL;
    
    // Clear Interrupt Flag
    ADCSRA |= (1 << ADSC);
}
