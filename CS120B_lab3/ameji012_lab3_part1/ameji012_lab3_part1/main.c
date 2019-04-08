/*
 * ameji012_lab3_part1.c
 *
 * Created: 4/8/2019 2:56:28 PM
 * Author : Antho
 */ 

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
		
    while (1) 
    {
		unsigned char counter = 0;
		unsigned char a_pins = PINA;
		unsigned char b_pins = PINB;
		
		for (unsigned char i = 0x00; i < 8; ++i)
		{
			counter += GetBit(a_pins, i);
			counter += GetBit(b_pins, i);
		}
		
		PORTC = counter;
    }	
}

