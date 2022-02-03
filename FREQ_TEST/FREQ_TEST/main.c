/*
 * ROBOT_TEST_00.c
 *
 * Created: 10/05/2021 9:17:30
 * Author : DCE
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PREESCALER 64
#define FREQ 1000
#define OCR 

ISR(TIMER0_COMPA_vect){
	PORTB^=(1<<PORTB2);	// toggles the led
	//TCNT0 = 0xf0;
}

void timer0_init();
void timer0_enaINT();

int main(void)
{
	DDRB |= (1 << PORTB2);
	timer0_init();
	timer0_enaINT();
	sei();
	/*_delay_ms(500);
	cli();
	_delay_ms(500);
	sei();
	_delay_ms(500);
	cli();*/
    while (1) 
    {
		/*_delay_ms(1);
		PORTB^=(1<<PORTB2);	// toggles the led*/
    }
}

void timer0_init(){
	TCCR0A |= (1<<WGM01);			// Modo CTC (Clear Timer on Compare match)
	TCCR0B |= (1<<CS01)|(1<<CS00);	// Preescaler de 64
	OCR0A = 0xf9;
}

void timer0_enaINT(){
	TIMSK0 |=(1<<OCIE0A);			// Activo interrupción por comparación del registro de comparación OCR0A
}