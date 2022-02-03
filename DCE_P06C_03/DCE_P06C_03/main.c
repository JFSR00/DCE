/*
 * DCE_P06C_03.c
 *
 * Created: 03/05/2021 18:59:32
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "adc.h"

void initPorts();

void InitTimer0(void);
void StartTimer0(void);
void setDutyCycleOC0B(uint8_t);

int main(void){
	initADC();

	initPorts();
	InitTimer0();
	StartTimer0();

	while(1){
		setDutyCycleOC0B(readADC(1) >> 2);
	}
}

void initPorts(){
	//set OC0A/PD6 and OC0B/PD5 as output
	DDRD |= (1<<PORTD5);
}

void InitTimer0(void){
	TCNT0 = 0;	//Set Initial Timer value
	//Pahse correct PWM mode and clear OC0A and OC0B on compare match
	TCCR0A |= (1<<COM0B1) | (1<<COM0A1) | (1<<WGM02) | (1<<WGM00);
}

void StartTimer0(void){
	//Set prescaler 64 and start timer (F_PWM= 488z)
	TCCR0B |= (1<<CS10);
}

void setDutyCycleOC0B(uint8_t dc){
	OCR0B = dc;	//Compare value (Duty Cycle = 70%)
}