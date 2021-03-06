/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #9  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#define F_CPU 125000*8

#include <avr/io.h>
#include <util/delay.h>

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25


double notes[42] = {F4, F4, C4, C4, D4, D4, C4,
					 B4, B4, A4, A4, G4, G4, F4, 
					 C4, C4, B4, B4, A4, A4, G4, 
					 C4, C4, B4, B4, A4, A4, G4, 
					 F4, F4, C4, C4, D4, D4, C4, 
					 B4, B4, A4, A4, G4, G4, F4};

unsigned char playNote;
unsigned char button;

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

void checkInput() {
	unsigned char current_state;
	do {
		current_state = (~PINA & 0x01);
		if (current_state) {
			playNote = current_state;
		}	
	} while (current_state);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned long i;
	
    while (1) 
    {
		playNote = 0x00;	
		i = 0;	
		checkInput();
					
		if (playNote) {
			do {
				
				PWM_on();
				set_PWM(notes[i]);
				
				if (i == 6 || i == 13 || i == 20 || i == 27 || i == 34 || i == 41)
					_delay_ms(3000);
				else
					_delay_ms(1500);
				
				PWM_off();
				_delay_ms(2500);
				
				i++;
			}while (i < 42);
		}
    }
}

