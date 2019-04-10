/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail:
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

enum States{Start, PB0_Release, PB1_Press, PB1_Release, PB0_Press}state;

void tick() {
	switch(state) {
		case Start:
			state = PB0_Release;
			break;
			
		case PB0_Release:
			if (!(PINA & 0x01)) {
				state = PB0_Release;
			}
			else {
				PORTB = 0x02;
				state = PB1_Press;
			}
			break;
			
		case PB1_Press:
			if (PINA & 0x01) {
				state = PB1_Press;
			}
			else {
				state = PB1_Release;
			}
			break;
			
		case PB1_Release:
			if (!(PINA  & 0x01)) {
				state = PB1_Release;
			}
			else {
				PORTB = 0x01;
				state = PB0_Press;
			}
			break;
			
		case PB0_Press:
			if (PINA & 0x01) {
				state = PB0_Press;
			}
			else {
				state = PB0_Release;
			}
			break;
			
		default:
			state = Start;
			break;
	}
	
	switch(state) {
		case Start:
			break;
		
		case PB0_Release:
			PORTB = 0x01;
			break;
		
		case PB1_Press:
			break;
		
		case PB1_Release:
			break;
		
		case PB0_Press:
			break;
	}
}

int main(void)
{
	DDRA = 0xFE; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	PORTB = 0x00;
	
    while (1) 
    {
		tick();
    }
}

