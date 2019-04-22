/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char fuelLevel;
	unsigned char leds;
	unsigned char button0;
	unsigned char button1;
	unsigned char button2;
	unsigned char button3;
	
	while (1)
	{
		button0 = 0x00 | (~PINA & 0x01);
		button1 = 0x00 | (~PINA & 0x02);
		button2 = 0x00 | (~PINA & 0x04);
		button3 = 0x00 | (~PINA & 0x08);
		
		fuelLevel = 0x00 | button0 | button1 | button2 | button3;
		
		switch(fuelLevel) {
			case 1:
			case 2:
			leds = (leds & 0x00) | 0x20;
			break;
			
			case 3:
			case 4:
			leds = (leds & 0x00) | 0x30;
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
			
			default:
				leds = 0x00;
				break;
		}
		
		if (fuelLevel <= 4) {
			leds = SetBit(leds, 6, 1);
		}
		
		PORTB = leds;
	}
}

