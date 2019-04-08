/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #1 
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
	DDRA = 0xF0; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char fuelLevel = 0x00;
	unsigned char leds = 0x00;
	
    while (1) 
    {
		fuelLevel = PINA & 0x0F;
		
		switch(fuelLevel) {
			case 1:
			case 2:
				leds = (leds & 0x00) | 0x60;
				break;
				
			case 3:
			case 4:
				leds = (leds & 0x00) | 0x70;
				break;
				
			case 5:
			case 6:
				leds = (leds & 0x00) | 0x38;
				break;
				
			case 7:
			case 8:
			case 9:
				leds = (leds & 0x00) | 0x3C;
				break;
				
			case 10:
			case 11:
			case 12:
				leds = (leds & 0x00) | 0x3E;
				break;
				
			case 13:
			case 14:
			case 15:
				leds = (leds & 0x00) | 0x3F;
				break;
		}
		
		PORTC = leds;
	}
}

