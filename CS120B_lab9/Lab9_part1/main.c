/*	Partner 1 Name & E-mail: Anthony Mejia, ameji012@ucr.edu
 *	Partner 2 Name & E-mail: David Gutierrez, dguti026@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#define C4 261.63
#define D4 293.66
#define E4 329.63

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



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x08; PORTB = 0x00;

    while (1) 
    {
		unsigned char C_Button = ~PINA & 0x01;
		unsigned char D_Button = (~PINA & 0x02)>>1;
		unsigned char E_Button = (~PINA & 0x04)>>2;
		

		if (C_Button) {set_PWM(C4);}
		else if (D_Button) {set_PWM(D4);}
		else if (E_Button) {set_PWM(E4);}
			
		while (C_Button && !D_Button && !E_Button) {
			C_Button = ~PINA & 0x01;
			D_Button = (~PINA & 0x02)>>1;
			E_Button = (~PINA & 0x04)>>2;
			PWM_on();
		}
			
		while (!C_Button && D_Button && !E_Button) {
			C_Button = ~PINA & 0x01;
			D_Button = (~PINA & 0x02)>>1;
			E_Button = (~PINA & 0x04)>>2;
			PWM_on();
		}
		
		while (!C_Button && !D_Button && E_Button) {
			C_Button = ~PINA & 0x01;
			D_Button = (~PINA & 0x02)>>1;
			E_Button = (~PINA & 0x04)>>2;
			PWM_on();
		}
		
		if (!C_Button && !D_Button && !E_Button)
			PWM_off();
    }
}

