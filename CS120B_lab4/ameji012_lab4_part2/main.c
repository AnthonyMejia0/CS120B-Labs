/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail:
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #2 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

enum States{Start, init, Increment, Decrement, Reset}state;
unsigned char currentValue;
unsigned char A0_button;
unsigned char A1_button;

void tick() {
	switch(state) {
		case Start:
			state = init;
			break;
			
		case init:
			if (A0_button && !A1_button) {
				state = Increment;
			}
			else if (!A0_button && A1_button) {
				state = Decrement;
			}
			else if (A0_button && A1_button) {
				state = Reset;
			}
			break;
			
		case Increment:
			if (A0_button && !A1_button) {
				state = Increment;
			}
			else if (!A0_button && A1_button) {
				state = Decrement;
			}
			else if (A0_button && A1_button) {
				state = Reset;
			}
			break;
			
		case Decrement:
			if (A0_button && !A1_button) {
				state = Increment;
			}
			else if (!A0_button && A1_button) {
				state = Decrement;
			}
			else if (A0_button && A1_button) {
				state = Reset;
			}
			break;
			
		case Reset:
			if (A0_button && !A1_button) {
				state = Increment;
			}
			else if (!A0_button && A1_button) {
				state = Decrement;
			}
			else if (A0_button && A1_button) {
				state = Reset;
			}
			break;
			
		default:
			state = Start;
			break;
	}
	
	switch(state) {
		case Start:
			break;
			
		case init:
			PORTC = currentValue = 7;
			break;
			
		case Increment:
			if (currentValue < 9) {
				++currentValue;
				PORTC = currentValue;
			}
			break;
			
		case Decrement:
			if (currentValue > 0) {
				--currentValue;
				PORTC = currentValue;
			}
			break;
			
		case Reset:
			currentValue = 0;
			PORTC = currentValue;
	}
}

int main(void)
{
	DDRA = 0xFC; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	PORTC = 0x00;
	state = Start;
	
    while (1) 
    {
		A0_button = PINA & 0x01;
		A1_button = (PINA & 0x02)>>1;
		tick();
   }
}

