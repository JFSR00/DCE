/*
 * motors.c
 *
 * Created: 24/05/2021 12:20:55
 *  Author: Juan Francisco Santos Relinque
 */ 

#include <avr/io.h>
#include "motors.h"

void motor_init(){
	// ---------------| Ports configuration |----------------------
	DDRC |= (1<<PORTC6);				// PWM1		Pin 31	PC6 (OC3A/OC4A(Negado))
	DDRD |= (1<<PORTD7)|(1<<PORTD6);	// EN1		Pin 26	PD6 (T1/OC4D(Negado)/ADC9)
										// PWM2	Pin 27	PD7 (T0/OC4D/ADC10)
	DDRE |= (1<<PORTE6);				// EN2		Pin 1	PE6 (INT6/AIN0)
	
	// ---------------| Timer 4 configuration |----------------------
	TCNT4 = 0;	//Set Initial Timer value
	//Phase correct PWM mode and clear OC4A and OC4D on compare match
	TCCR4A |= (1<<COM4A0) | (1<<PWM4A);
	TCCR4C |= (1<<COM4D1) | (1<<PWM4D);
	TCCR4D |= (1<<WGM40);
	TCCR4B |= (1<<CS42)|(1<<CS41)|(1<<CS40);	// Starts the timer and sets the prescaler at 64
	
	// ---------------| Motors initialize |----------------------
	motor_setVelocity(0, 0);
	motor_setDirection(FORWARD);
}

void motor_turnLeft(uint8_t spd, uint8_t dir){
	switch(dir){
		case FORWARD:
			motor_setDirection(FORWARD);
			motor_setVelocity(spd, spd>>1);
			break;
		case BACKWARD:
			motor_setDirection(BACKWARD);
			motor_setVelocity(spd>>1, spd);
			break;
	}
}

void motor_turnRigth(uint8_t spd, uint8_t dir){
	switch(dir){
		case FORWARD:
			motor_setDirection(FORWARD);
			motor_setVelocity(spd>>1, spd);
			break;
		case BACKWARD:
			motor_setDirection(BACKWARD);
			motor_setVelocity(spd, spd>>1);
			break;
	}
}

void motor_forward(uint8_t spd){
	motor_setDirection(FORWARD);
	motor_setVelocity(spd, spd);
}

void motor_backward(uint8_t spd){
	motor_setDirection(BACKWARD);
	motor_setVelocity(spd, spd);
}

void motor_setVelocity(uint8_t spd_l, uint8_t spd_r){
	OCR4A = ~spd_l;
	OCR4D = spd_r;
}

void motor_setDirection(uint8_t dir){
	switch(dir){
		case BACKWARD:
			PORTD |= (1<<PORTD6);
			PORTE |= (1<<PORTE6);
			break;
		case FORWARD:
			PORTD &= ~(1<<PORTD6);
			PORTE &= ~(1<<PORTE6);
			break;
	}
}

void motor_stop(){
	motor_setVelocity(0, 0);
}
