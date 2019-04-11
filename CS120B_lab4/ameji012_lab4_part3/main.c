/*
 * ameji012_lab4_part3.c
 *
 * Created: 4/11/2019 2:41:51 PM
 * Author : Antho
 */ 

#include <avr/io.h>

enum States{Start, Lock, Wait_Y, Unlock}state;
unsigned char X;
unsigned char Y;
unsigned char hashtag;
unsigned char lock_button;

void tick() {
	switch(state) {
		case Start:
			state = Lock;
			break;
			
		case Lock:
			if (hashtag && !X && !Y && !lock_button) {
				state = Wait_Y;
			}
			else {
				state = Lock;
			}
			break;
			
		case Wait_Y:
			if (hashtag && !X && !Y && !lock_button) {
				state = Wait_Y;
			}
			else if (Y && !X && !lock_button && !hashtag){
				state = Unlock;
			}
			else {
				state = Lock;
			}
			break;
			
		case Unlock:
			if (lock_button && !X && !Y && !hashtag){
				state = Lock;
			}
			else {
				state = Unlock;
			}
			break;
			
		default:
			state = Start;
			break;
	}
	
	switch(state) {
		case Start:
			break;
			
		case Lock:
			PORTB = 0x00;
			PORTC = 0;
			break;
			
		case Wait_Y:
			PORTB = 0x00;
			PORTC = 0x01;
			break;
			
		case Unlock:
			PORTB = 0x01;
			PORTC = 0x02;
			break;
	}	
}

int main(void)
{
	DDRA = 0x78; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;

    while (1) 
    {
		X = PINA & 0x01;
		Y = (PINA & 0x02)>>1;
		hashtag = (PINA & 0x04)>>2;
		lock_button = (PINA & 0x80)>>7;
		tick();
    }
}

