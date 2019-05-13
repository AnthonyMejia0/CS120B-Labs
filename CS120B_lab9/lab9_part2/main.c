/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #9  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25


double frequencies[8] = {C4, D4, E4, F4, G4, A4, B4, C5};
enum States{Start, init, Increment, Decrement}state;
unsigned char playNote;
unsigned char up_button;
unsigned char down_button;
unsigned char buttons;

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	//static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		//current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << WGM02) | (1 << WGM00) | (1 << COM0A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}


void tick() {
	static unsigned char i;
	
	switch(state) {
		case Start:
		i = 0;
		state = init;
		break;
		
		case init:
		if (up_button) {
			state = Increment;
		}
		else if (down_button) {
			state = Decrement;
		}
		else {
			state = init;
		}
		break;
		
		case Increment:
		if (up_button) {
			state = Increment;
		}
		else if (down_button) {
			state = Decrement;
		}
		else {
			state = init;
		}
		break;
		
		case Decrement:
		if (up_button) {
			state = Increment;
		}
		else if (down_button) {
			state = Decrement;
		}
		else {
			state = init;
		}
		break;
		
		default:
		state = Start;
		break;
	}
	
	switch (state) {
		case Start:
		break;
		
		case init:
		set_PWM(frequencies[i]);
		break;
		
		case Increment:
		if (i < 7) {
			i++;
		}
		break;
		
		case Decrement:
		if (i > 0) {
			i--;
		}
		break;
	}
}

void checkInput() {
	unsigned char current_state;
	do {
		current_state = (~PINA & 0x06);
		if (current_state) {
			buttons = current_state;
		}	
	} while (current_state);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;

    while (1) 
    {
		playNote = ~PINA & 0x01;
		buttons = 0x00;
		
		checkInput();
		up_button = buttons & 0x02;
		down_button = buttons & 0x04;

		tick();
			
		while (playNote) {
			playNote = ~PINA & 0x01;
			PWM_on();
		}
		
		if (!playNote) {
			PWM_off();
		}
    }
}

