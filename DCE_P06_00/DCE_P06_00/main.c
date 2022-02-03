/*
 * DCE_P06_00.c
 *
 * Created: 26/04/2021 9:01:12
 * Author : Juan Francisco Santos Relinque
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect){
	static uint8_t tot_overflow = 0;
	if(tot_overflow>=16){
		PORTB^=(1<<PORTB5);	// toggles the led
		tot_overflow=0;
	}else if(tot_overflow==15){
		TCNT0=189;			//after 67 clk -> overflow/irq
		tot_overflow++;
	}else{
		tot_overflow++;
	}
}

void timer0_init();
void timer0_enaINT();

int main(void){
	DDRB |= (1 << PORTB5);	// connect led to pin PB5
	timer0_init();			// initialize timer
	timer0_enaINT();		// enable overflow interrupt
	sei();
	while(1){
		// do nothing
	}
}

void timer0_init(){
	TCCR0B|=(1<<CS02)|(1<<CS00);	// pre-scaler = 1024
	TCNT0=0;
}

void timer0_enaINT(){
	TIMSK0 |=(1<<TOIE0);			// initialize counter
}
