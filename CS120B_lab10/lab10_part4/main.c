/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #10  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "Timer.h"

double frequencies[8] = {600, 700, 800, 900, 1000, 1100, 1200, 1300};

enum Three_Leds{StartTLED, nextLed} TLState;
enum Blink_Led{StartBLED, toggle} BLState;
enum Speaker{StartSpeaker, ON, OFF} SPState;
enum Change_Freq{Start, wait, changeFrequency} FreqState;
	
unsigned char BLED;
unsigned char TLED;
unsigned char Period = 1;
unsigned char button;
double frequency;

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}


void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}


void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}
	
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

void SpeakerTick() {
	button = ~PINA & 0x04;

	switch (SPState) {
		case StartSpeaker:
			SPState = OFF;
			break;
			
		case ON:
			SPState = OFF;
			break;
			
		case OFF:
			SPState = (button) ? ON: OFF;
			break;
			
		default:
			SPState = StartSpeaker;
	}
	
	switch (SPState) {
		case StartSpeaker:
			break;
			
		case ON:
			set_PWM(frequency);
			break;
			
		case OFF:
			set_PWM(0);
			break;
	}
}

void FreqTick() {
	static unsigned char prev_buttons;
	unsigned char up_button = ~PINA & 0x01;
	unsigned char down_button = ~PINA & 0x02;
	static unsigned char i;
	
	switch (FreqState) {
		case Start:
			i = 0;
			FreqState = wait;
			break;
			
		case wait:
			if ((up_button || down_button) && (prev_buttons != (up_button | down_button<<1))) {
				FreqState = changeFrequency;
			}
			break;
			
		case changeFrequency:
			FreqState = wait;
			break;
			
		default:
			FreqState = Start;
			break;
	}
	
	switch (FreqState) {
		case Start:
			break;
			
		case wait:
			frequency = frequencies[i];
			break;
			
		case changeFrequency:
			if (up_button && !down_button) {
				if (i < 7) {
					i++;
				}
			}
			else if (!up_button && down_button) {
				if (i > 0) {
					i--;
				}
			}
			break;
	}
	PORTB |= (i<<4);
	prev_buttons = up_button | (down_button<<1);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	unsigned char Leds = 0x00;
	unsigned long BL_elapsedTime= 0;
	unsigned long TL_elapsedTime = 0;
	BLState = StartBLED;
	TLState = StartTLED;
	SPState = StartSpeaker;
	
	TimerOn();
	TimerSet(Period);
	PWM_on();
	
    while (1) 
    {
		FreqTick();
		SpeakerTick();
		
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

