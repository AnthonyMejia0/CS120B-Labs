/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #4 
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char upperNibble;
	unsigned char lowerNibble;
	unsigned char tmpB;
	unsigned char tmpC;
	
	while (1) 
    {
		upperNibble = PINA & 0xF0;
		lowerNibble = PINA & 0x0F;
		
		tmpB = (tmpB & 0x00) | (upperNibble >> 4);
		tmpC = (tmpC & 0x00) | (lowerNibble << 4);
		
		PORTB = tmpB;
		PORTC = tmpC;
    }
}

