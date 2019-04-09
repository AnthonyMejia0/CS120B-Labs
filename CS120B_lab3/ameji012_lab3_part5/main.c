/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #5 
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
	DDRB = 0xFE; PORTB = 0xFF;
	DDRD = 0x00; PORTD = 0xFF;
	
    while (1) 
    {
		unsigned short totalWeight = 0x00;
		unsigned char tmpB = 0x00;

		totalWeight = PIND;
		totalWeight = totalWeight << 1;
		totalWeight = totalWeight | (PINB & 0x01);
		
		if (totalWeight >= 70) {
			tmpB = SetBit(tmpB, 1, 1);
		}
		else if (totalWeight > 5 && totalWeight < 70) {
			tmpB = SetBit(tmpB, 2, 1);
		}
		else {
			tmpB = 0x00;	
		}
		
		PORTB = tmpB;
    }
}

