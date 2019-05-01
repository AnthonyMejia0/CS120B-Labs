/*
 * lab8_part1.c
 *
 * Created: 4/29/2019 4:02:18 PM
 * Author : Antho
 */ 

#include <avr/io.h>
#include "io.c"

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char lower_8;
	unsigned char upper_2;
	ADC_init();

    while (1) 
    {
		unsigned short x = ADC;
		lower_8 = (char)x;
		upper_2 = (char)(x>>8);
		
		PORTB = lower_8;
		PORTD = upper_2;
    }
}

