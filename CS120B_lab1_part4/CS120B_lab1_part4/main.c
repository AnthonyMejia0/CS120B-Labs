/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #4
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#include <stdlib.h>


int main(void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char MAX_WEIGHT = 0x8C;
	unsigned short totalWeight = 0x00;
	unsigned short totalWeight_shifted = 0x00;
	unsigned char balance = 0x00;
	unsigned char tempD = 0x00;
	
    while (1) 
    {
		totalWeight = PINA + PINB + PINC;
		totalWeight_shifted = totalWeight << 2;
		balance = abs(PINA - PINC);
		
		if (totalWeight > MAX_WEIGHT ) {
			if (balance > 80) {
				tempD = (tempD & 0xFC) | 0x03;
			}
			else {
				tempD = (tempD & 0xFC) | 0x01;
			}
		}
		else {
			if (balance > 80) {
				tempD = (tempD & 0xFC) | 0x02;
			}
			else {
				tempD = (tempD & 0xFC) | 0x00;
			}
		}
		
		if (totalWeight_shifted >= 0xFC) {
			PORTD = (tempD & 0x03) | 0xFC;
		}
		else {
			PORTD = (tempD & 0x03) | totalWeight_shifted;
		}		
	}
}

