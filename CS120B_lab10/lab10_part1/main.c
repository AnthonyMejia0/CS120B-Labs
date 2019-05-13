/*
 * lab10_part1.c
 *
 * Created: 5/6/2019 3:47:12 PM
 * Author : Antho
 */ 

#include <avr/io.h>
#include "Timer.h"

enum Three_Leds{StartTLED, nextLed} TLState;
enum Blink_Led{StartBLED, toggle} BLState;
unsigned char BLED;
unsigned char TLED;
	
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
	TimerOn();
	TimerSet(1000);
	
    while (1) 
    {
		TL_Tick();
		BL_Tick();
		while(!TimerFlag){}
		TimerFlag = 0;	
		
		Leds = TLED | ((BLED & 0x01)<<3);
		PORTB = Leds;
    }
}

