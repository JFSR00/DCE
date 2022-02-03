/*
 * DCE_P06C_01.c
 *
 * Created: 03/05/2021 10:27:10
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void initPorts();

void InitTimer0(void);
void StartTimer0(void);
void setDutyCycleOC0A(uint8_t);
void setDutyCycleOC0B(uint8_t);

int main(void){
	uint8_t dc = 128;
	uint8_t dir = 1;

	initPorts();
	InitTimer0();
	//setDutyCycleOC0A(178);	// Ej 1
	//setDutyCycleOC0B(89);	// Ej 1
	StartTimer0();
	while(1){
		setDutyCycleOC0B(dc);
		if(dir){
			dc++;
		}else{
			dc--;
		}
		if(dc == 255 || dc == 0){
			dir = !dir;
		}
		_delay_ms(10);
	}
}

void initPorts(){
	//set OC0A/PD6 and OC0B/PD5 as output
	//DDRD |= (1<<PORTD6) | (1<<PORTD5);	// Ej 1
	DDRD |= (1<<PORTD5);	// Ej 2
}

void InitTimer0(void){
	TCNT0 = 0;	//Set Initial Timer value
	//Pahse correct PWM mode and clear OC0A and OC0B on compare match
	TCCR0A |= (1<<COM0B1) | (1<<COM0A1) | (1<<WGM02) | (1<<WGM00);
}

void StartTimer0(void){
	//Set prescaler 64 and start timer (F_PWM= 488z)
	//TCCR0B |= (1<<CS01) | (1<<CS00);	// Ej 1
	TCCR0B |= (1<<CS10);	// Ej 2
}

void setDutyCycleOC0A(uint8_t dc){
	OCR0A = dc;	//Compare value (Duty Cycle = 70%)
}

void setDutyCycleOC0B(uint8_t dc){
	OCR0B = dc;	//Compare value (Duty Cycle = 70%)
}