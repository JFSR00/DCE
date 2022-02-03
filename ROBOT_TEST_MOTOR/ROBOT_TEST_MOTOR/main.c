/*
 * ROBOT_TEST_MOTOR.c
 *
 * Created: 24/05/2021 10:27:12
 * Author : Juan Francisco Santos Relinque
 */ 

/*
EN1		Pin 26	PD6 (T1/OC4D(Negado)/ADC9)
PWM1	Pin 31	PC6 (OC3A/OC4A(Negado))

EN2		Pin 1	PE6 (INT6/AIN0)
PWM2	Pin 27	PD7 (T0/OC4D/ADC10)
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"

void initPorts();

void InitTimer4(void);
void StartTimer4(void);
void setDutyCycleMotorL(uint8_t);
void setDutyCycleMotorR(uint8_t);

int main(void){
	uint8_t dc = 0, dc2 = 255, dir = 1;

	motor_init();
	
	motor_forward(255);
	_delay_ms(2000);
	motor_backward(255);
	_delay_ms(2000);
	motor_turnLeft(255, FORWARD);
	_delay_ms(2000);
	motor_turnLeft(255, BACKWARD);
	_delay_ms(2000);
	motor_turnRigth(255, FORWARD);
	_delay_ms(2000);
	motor_turnRigth(255, BACKWARD);
	_delay_ms(2000);
	motor_stop();
	
    while (1) 
    {
		/*if(dir){
			dc++;
			dc2--;
		}else{
			dc--;
			dc2++;
		}
		if((dc == 255)||dc == 0){
			dir = !dir;
		}
		_delay_ms(50);
		motor_FWD(dc,dc2);*/
    }
}

void initPorts(){
	DDRC |= (1<<PORTC6);				// PWM1		Pin 31	PC6 (OC3A/OC4A(Negado))
	DDRD |= (1<<PORTD7)|(1<<PORTD6);	// EN1		Pin 26	PD6 (T1/OC4D(Negado)/ADC9)
										// PWM2	Pin 27	PD7 (T0/OC4D/ADC10)
	DDRE |= (1<<PORTE6);				// EN2		Pin 1	PE6 (INT6/AIN0)
	
}

void InitTimer4(void){
	TCNT4 = 0;	//Set Initial Timer value
	//Pahse correct PWM mode and clear OC0A and OC0B on compare match
	TCCR4A |= (1<<COM4A0) | (1<<PWM4A);
	TCCR4C |= (1<<COM4D1) | (1<<PWM4D);
	TCCR4D |= (1<<WGM40);
}

void StartTimer4(void){
	//Set prescaler 64 and start timer (F_PWM= 488z)
	TCCR4B |= (1<<CS42)|(1<<CS41)|(1<<CS40);
}

void setDutyCycleMotorL(uint8_t dc){
	OCR4A = ~dc;
}

void setDutyCycleMotorR(uint8_t dc){
	OCR4D = dc;
}