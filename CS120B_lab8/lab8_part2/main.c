/*
 * lab8_part1.c
 *
 * Created: 4/29/2019 4:02:18 PM
 * Author : Antho
 */ 

#include <avr/io.h>

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
	unsigned short MAX = 0x6F;
	ADC_init();
	
    while (1) 
    {
		unsigned short x = ADC;
		PORTB = (x >= MAX/2) ? 1: 0;
	}
}
