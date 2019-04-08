/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #1
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char door = 0x00;
	unsigned char light = 0x00;
	unsigned char led = 0x00;
	
	while(1)
	{
		door = PINA & 0x01;
		light = PINA & 0x02;
		
		if (door && !light) {
			led = 0x01;
		}
		else {
			led = 0x00;
		}
		
		PORTB = led;
	} 
	
	return 0;
}

