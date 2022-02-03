/*
 * TMR1.c
 *
 * Created: 03/05/2021 9:19:12
 *  Author: DCE
 */ 

#include "TMR1.h"

void TMR1_CTC_irq(){
	TCCR1A |= (1<<COM1A0);	// Toggle OC1A on Compare Match.
	TCCR1B |= (1<<WGM12);	// ModeCTC on OCR1A
	// set prescaler to 1024 and start the timer
	TCCR1B |= (1<<CS02) | (1<<CS00);
}

void TMR1_CTC_set(uint16_t value){
	TCNT1 = 0;		// Initialize counter
	OCR1A = value;	// Set number of ticks to reach the time
}

void TMR1_CTC_start(){
	TIMSK1 |= (1 << OCIE1A);
}