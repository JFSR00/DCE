/*
 * DCE_P06B_01.c
 *
 * Created: 26/04/2021 12:20:37
 * Author : Juan Francisco Santos Relinque
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TMR1.h"
#include "adc.h"

void config_ports();

volatile uint16_t res;

ISR(TIMER1_COMPA_vect){
	enableADCInt();
	readADCInt(1);
}

ISR(ADC_vect){
	disableADCInt();
	res = ADC;
}

int main(void){
	config_ports();
	initADC();
	
	TMR1_CTC_irq();
	TMR1_CTC_set(7812);
	TMR1_CTC_start();
	
	sei();
	while(1){
		if(res >= 512){
			PORTB |= (1 << PORTB5);
		}else{
			PORTB &= ~(1 << PORTB5);
		}
	}
}

void config_ports(){
	//set PD6 as output
	DDRB |= (1<<PORTB1) | (1<<PORTB5);	// Connect led to pin PB1/OC1A
	//DDRB |= (1<<PORTB5);
}
