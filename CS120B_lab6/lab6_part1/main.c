/*
 * lab6_part1.c
 *
 * Created: 4/22/2019 3:50:01 PM
 * Author : Antho
 */ 

#include <avr/io.h>
#include "Timer.h"

enum States{Start, init, nextLed}state;

void Tick() {
	switch(state) {
		case Start:
			state = init;
			break;
			
		case init:
			state = nextLed;
			break;
			
		case nextLed:
			state = (PORTB == 0x04) ? init: nextLed;
			break;
	}
	
	switch(state) {
		case Start:
			break;
			
		case init:
			PORTB = 0x01;
			break;
			
		case nextLed:
			PORTB = PORTB<<1;
	}
}


int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

