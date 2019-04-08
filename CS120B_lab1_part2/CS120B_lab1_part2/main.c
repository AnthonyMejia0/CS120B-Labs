/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #2
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char cntavail = 0x00;
	
    while (1) 
    {
		switch (PINA)
		{
			case 0x00:
				cntavail = 0x04;
				break;
				
			case 0x01:
			case 0x02:
			case 0x04:
			case 0x08:
				cntavail = 0x03;
				break;
				
			case 0x03:
			case 0x06:
			case 0x0A:
			case 0x09:
				cntavail = 0x02;
				break;

			case 0x07:
			case 0x0E:
			case 0x0D:
			case 0x0B:
				cntavail = 0x01;
				break;

			case 0x0F:
				cntavail = 0x00;
				break;
		}
		
		PORTC = cntavail;
    }
	
	return 0;
}

