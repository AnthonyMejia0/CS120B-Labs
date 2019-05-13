/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "io.c"
#include "Timer.h"

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
			currentValue = 0;
			break;
			
		case Increment:
			if (currentValue < 9) {
				++currentValue;
			}
			break;
			
		case Decrement:
			if (currentValue > 0) {
				--currentValue;
			}
			break;
			
		case Reset:
			currentValue = 0;
			break;
	}
}


void checkInput() {
	static unsigned char count = 0;
	
	unsigned char current_state = (~PINA & 0x03);
	
	if (current_state) {
		++count;
		if (count >= 4) {
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
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

	state = Start;
	
	LCD_init();
	
	//A0_button = 0x00;
	//A1_button = 0x00;
	tick();
	LCD_WriteData(currentValue + '0');
	
	TimerSet(1000);
	TimerOn();
		
	while(1) {		
		while(!TimerFlag) {
			checkInput();
		}
		TimerFlag = 0;
		/*
		if (buttons) {
			A0_button = buttons & 0x01;
			A1_button = buttons & 0x02;
			tick();
			unsigned char column = 1;
			LCD_Cursor(column);
			LCD_WriteData(currentValue + '0');
			
			buttons = 0x00;
		}*/
	}
   
	return 0;
}



