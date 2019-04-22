/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #3 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#define F_CPU 125000UL

#include <avr/io.h>
#include <util/delay.h>

enum States{Start, init, Stage1, Stage2}state;
unsigned char MASK1;
unsigned char MASK2;

unsigned char buttonPressed;

void lightShow() {
	switch (state) {
		case Start:
			state = init;
			break;
			
		case init:
			state = Stage1;
			break;
			
		case Stage1:
			if (MASK1 > 0x20) {
				state = Stage2;
			}
			break;
			
		case Stage2:
			if (MASK2 < 0x01) {
				state = init;
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
			PORTB = 0x00;
			MASK1 = 0x01;
			MASK2 = 0x20;
			break;
			
		case Stage1:
			if (MASK1 <= 0x20) {
				PORTB = PORTB | MASK1;
				MASK1 = MASK1<<1;
			}
			break;
			
		case Stage2:
			if (MASK2 == 0x20) {
				PORTB = MASK2;
				MASK2 = MASK2>>1;
			}
			else if (MASK2 >= 0x01) {
				PORTB = PORTB | MASK2;
				MASK2 = MASK2>>1;	
			}
			break;
	}
}


void checkInput() {
	static unsigned char count = 0;
	static unsigned char prev_state = 0;
	unsigned char current_state = (~PINA & 0x01);
	
	if (current_state != prev_state) {
		++count;
		
		if (count >= 4) {
			prev_state = current_state;

			if (current_state != 0) {
				buttonPressed = 1;
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
	lightShow();
	
    while (1) 
    {
		checkInput();
		
		if (buttonPressed) {
			buttonPressed = 0;
			lightShow();
		}
		_delay_ms(10);		
    }
}

