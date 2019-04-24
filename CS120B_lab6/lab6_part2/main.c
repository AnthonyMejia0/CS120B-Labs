/*
 * lab6_part2.c
 *
 * Created: 4/22/2019 4:15:40 PM
 * Author : Antho
 */ 

#include <avr/io.h>
#include "Timer.h"

enum States{Start, init, forward, reverse, stop}state;
		
unsigned char button;
	

void Tick() {
	switch(state) {
		case Start:
			state = init;
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
			if (button) {
				state = init;
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
	state = Start;
	TimerSet(300);
	TimerOn();
		
	while(1) {
		Tick();
		button = 0;
		while(!TimerFlag) {
			checkInput();
		}
		TimerFlag = 0;
	}
}

