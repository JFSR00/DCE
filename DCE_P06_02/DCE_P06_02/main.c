/*
 * DCE_P06_02.c
 *
 * Created: 26/04/2021 11:34:39
 * Author : Juan Francisco Santos Relinque
 */

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER1_OVF_vect){
	/*static uint8_t tot_overflow = 0;
	if(tot_overflow>2){
		PORTB^=(1<<PORTB2);	// toggles the led
		tot_overflow=0;
	}else if(tot_overflow==0){
		TCNT0=27;			//after 67 clk -> overflow/irq
		tot_overflow++;
	}else{
		tot_overflow++;
	}*/
	PORTB^=(1<<PORTB2);	// toggles the led
	TCNT1 = 0xE17B;
}

void timer1_init();
void timer1_enaINT();

int main(void){
	DDRB |= (1 << PORTB2);	// connect led to pin PB5
	timer1_init();			// initialize timer
	timer1_enaINT();		// enable overflow interrupt
	sei();
	while(1){
		// do nothing
	}
}

void timer1_init(){
	TCCR1B |= (1<<CS12) | (1<<CS10);	// pre-scaler = 8
	//TCCR0B |= (1<<CS01)|(1<<CS00);	// pre-scaler = 8
	TCNT1 = 0x0000;
}

void timer1_enaINT(){
	TIMSK1 |=(1<<TOIE1);			// initialize counter
}
