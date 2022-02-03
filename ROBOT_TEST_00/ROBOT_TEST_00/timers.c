/*
 * timers.c
 *
 * Created: 13/05/2021 17:29:43
 * Author: Juan Francisco Santos Relinque
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timers.h"

// --------------------------------------------------------------------------------
// --------------------| ISR |-----------------------------------------------------
// --------------------------------------------------------------------------------

ISR(TIMER0_COMPA_vect){				// Sound generation routine on compare match interrupt vector
	PORTB^=(1<<PORTB2);				// Toggles buzzer's pin
}

// --------------------------------------------------------------------------------
// --------------------| TIMER 0 |-------------------------------------------------
// --------------------------------------------------------------------------------

void timer0_init(uint8_t ocr, uint16_t prescaler){
	DDRB |= (1 << PORTB2);			// Output pin for the buzzer
	TCCR0A |= (1<<WGM01);			// CTC mode (Clear Timer on Compare match)
	OCR0A = ocr;
	switch(prescaler){				// Sets the Timer0 to the specified prescaler configuration
		case 1:
		TCCR0B |= (1<<CS00);
		break;
		case 8:
		TCCR0B |= (1<<CS01);
		break;
		case 64:
		TCCR0B |= (1<<CS01)|(1<<CS00);
		break;
		case 256:
		TCCR0B |= (1<<CS02);
		break;
		case 1024:
		TCCR0B |= (1<<CS02)|(1<<CS00);
		break;
		default:
		TCCR0B |= (1<<CS00);
		break;
	}
}

void timer0_enaINT(){
	TIMSK0 |=(1<<OCIE0A);			// Enables interrupt on match with register OCR0A
}

void timer0_disINT(){
	TIMSK0 &= ~(1<<OCIE0A);			// Disables interrupt on match with register OCR0A
}

void timer0_setFreq(uint16_t freq){	// Sets OCR0A to the value of specified frequency
	OCR0A = OCR(freq, TIMER0_PRESC);
}

void timer0_setOCR(uint8_t ocr){	// Sets OCR0A
	OCR0A = ocr;
}

// --------------------------------------------------------------------------------
// --------------------| TIMER 1 |-------------------------------------------------
// --------------------------------------------------------------------------------

void timer1_init(){
	TCCR1B |= (1<<WGM12);			// CTC mode (Clear Timer on Compare match)
	OCR1A = 0;
	TCCR1B |= (1<<CS12)|(1<<CS10);	// Default preescaler at 1024
}

void timer1_delay_ms(float delay){
	OCR1A = (uint16_t)((float)OCR((1000/delay), 1024));	// Sets the OCR register to the value of specified delay
	TIFR1 |= (1 << OCF1A);			// Clears Output Compare C Match Flag
	TCNT1 = 0;						// Restart the Timer1
	while(!(TIFR1 & (1 << OCF1A)));	// Waits to the compare match
}

void melody(uint16_t *freqs, float period, uint8_t size){
	uint8_t i;
	timer0_init(0, 64);				// That's the optimal configuration to use Timer0 as sound generator
	timer1_init();
	timer0_disINT();				// Disables sound generation before setting the sound frequency
	sei();							// Enables global interrupts
	for(i=0; i<size; i++){
		timer0_setFreq(freqs[i]);	// Sets the sound frequency
		timer0_enaINT();			// Enables sound generation, it's enabled only on first iteration
		timer1_delay_ms(period);	// Delays upt to the end of the sound period
	}
	timer0_disINT();				// Disables sound generation and all interrupts after the end of the melody
	cli();
}