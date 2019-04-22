/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #2 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#define F_CPU 125000UL

#include <avr/io.h>
#include <util/delay.h>

enum States{Start, init, Increment, Decrement, Reset}state;
unsigned char currentValue;
unsigned char A0_button;
unsigned char A1_button;
unsigned char buttons;


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
			PORTB = currentValue = 7;
			break;
			
		case Increment:
			if (currentValue < 9) {
				++currentValue;
				PORTB = currentValue;
			}
			break;
			
		case Decrement:
			if (currentValue > 0) {
				--currentValue;
				PORTB = currentValue;
			}
			break;
			
		case Reset:
			currentValue = 0;
			PORTB = currentValue;
			break;
	}
}


void checkInput() {
	static unsigned char count = 0;
	static unsigned char button_state = 0;
	
	unsigned char current_state = (~PINA & 0x03);
	
	if (current_state != button_state) {
		++count;
		if (count >= 4) {
			button_state = current_state;

			if (current_state != 0) {
				buttons = current_state;
			}
			count = 0;
		}
	}
	else {
		count = 0;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	
	A0_button = 0x00;
	A1_button = 0x00;
	tick();
		
    while (1) 
    {
		checkInput();
		
		if (buttons) {
			A0_button = buttons & 0x01;
			A1_button = buttons & 0x02;
			tick();
			buttons = 0x00;
		}
		_delay_ms(10);
   }
   
	return 0;
}

