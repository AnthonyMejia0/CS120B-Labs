/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "Timer.h"
#include "io.c"

enum States{Start, init, forward, reverse, stop, wait, winner}state;
	
unsigned char button;
unsigned char score;
	

void Tick() {
	switch(state) {
		case Start:
			score = 5;
			state = init;
			LCD_WriteData(score + '0');
			break;
			
		case init:
			state = forward;
			break;
			
		case forward:
			if (button) {
				state = stop;
			}
			else if (PORTB == 0x04) {
				state = reverse;
			}
			break;
			
		case reverse:
			if (button) {
				state = stop;
			}
			else if (PORTB == 0x01) {
				state = forward;
			}
			break;
			
		case stop:
			if (score == 9) {
				state = winner;
			}
			else {
				state = wait;
			}
			break;
		
		case wait:
			if (button) {
				state = init;
			}
			break;
			
		case winner:
			if (button) {
				state = init;
				score = 5;
				LCD_ClearScreen();
			}
			break;
	}
	
	switch(state) {
		case Start:
			break;
			
		case init:
			PORTB = 0x01;
			break;
			
		case forward:
			PORTB = PORTB<<1;
			break;
			
		case reverse:
			PORTB = PORTB>>1;
			break;
			
		case stop:
			if (PORTB == 0x02 && score < 9) {
				score++;
			}
			else if (PORTB != 0x02 && score > 0) {
				score--;
			}
			break;
			
		case wait:
			break;
			
		case winner:
			LCD_DisplayString(1, "WINNER!!!");
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
				button = 1;
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
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char column = 1;
	state = Start;
	TimerSet(300);
	TimerOn();
	LCD_init();
		
	while(1) {
		Tick();
		button = 0;
		while(!TimerFlag) {
			checkInput();
		}
		TimerFlag = 0;
		
		LCD_Cursor(column);
		LCD_WriteData(score + '0');
	}
}

