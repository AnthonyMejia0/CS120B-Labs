/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #10  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "Timer.h"

enum Three_Leds{StartTLED, nextLed} TLState;
enum Blink_Led{StartBLED, toggle} BLState;
unsigned char BLED;
unsigned char TLED;
unsigned char Period = 100;
	
void BL_Tick() {
	switch (BLState) {
		case StartBLED:
			BLED = 0x01;
			BLState = toggle;
			break;
			
		case toggle:
			BLED = ~BLED;
			break;
			
		default:
			BLState = StartBLED;
	}
}

void TL_Tick() {
	switch (TLState) {
		case StartTLED:
			TLED = 0x01;
			TLState = nextLed;
			break;
			
		case nextLed:
			TLED = TLED<<1;
			break;
			
		default:
			TLState = StartTLED;
	}
	
	switch (TLState) {
		case StartTLED:
			break;
			
		case nextLed:
			if (TLED > 0x04) {
				TLED = 0x01;
			}
			break;
	}
}

int main(void)
{
    DDRB = 0xFF; PORTB = 0x00;
	unsigned char Leds = 0x00;
	unsigned long BL_elapsedTime= 0;
	unsigned long TL_elapsedTime = 0;
	
	TimerOn();
	TimerSet(Period);
	
    while (1) 
    {
		if (TL_elapsedTime >= 300) {
			TL_Tick();
			TL_elapsedTime = 0;
		}
		
		if (BL_elapsedTime >= 1000) {
			BL_Tick();
			BL_elapsedTime = 0;
		}

		while(!TimerFlag){}
		TimerFlag = 0;	
		
		Leds = TLED | ((BLED & 0x01)<<3);
		PORTB = Leds;
		
		BL_elapsedTime += Period;
		TL_elapsedTime += Period;
    }
}

