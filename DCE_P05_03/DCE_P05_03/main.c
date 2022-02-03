/*
 * DCE_P05_03.c
 *
 * Created: 12/04/2021 9:13:33
 * Author : DCE
 */ 

#define F_CPU 16000000UL			// Clock Speed

#include <avr/io.h>
#include <avr/interrupt.h>

#define DEF_POINT 512
#define DEF_STEP 100

//-----------Prototypes--------------------------
static inline void initPorts();
static inline void initINT0();
static inline void initADC();

volatile uint16_t res;
volatile uint16_t set_point;

ISR(ADC_vect){
	res = ADC;
}

ISR(INT0_vect){
	set_point += DEF_STEP;
	set_point &= 0x03ff;	// De esta manera nos aseguramos que nunca sera
	// mayor de 1023
}

int main(){
	//-----------Local variables --------------------------
	res = 0;
	set_point = DEF_POINT;
	
	//-----------SETUP-------------------------------------
	initPorts();
	initINT0();
	initADC();
	sei();
	
	//-----------LOOP-------------------------------------
	while(1){
		ADCSRA |= (1<<ADSC);
		if(res >= set_point){
			PORTB = 0x0f;
			}else{
			PORTB = 0x00;
		}
	}
}

//-----------Functions--------------------------

static inline void initPorts(){
	// Configuracion de los LEDs
	DDRB |= (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3);
	PORTB &= ~((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3));
	// Configuracion del pulsador
	DDRD &= ~(1<<PORTD2);
	PORTD |= (1<<PORTD2);
}

static inline void initINT0(){
	EICRA|=(1<<ISC01);		// INT0-Falling edge
	EIMSK|=(1<<INT0);		// Enable INT0;
}

static inline void initADC(){
	ADMUX = 0x41;	// Usamos AVCC, ADLAR = 0 y usamos ADC1
	ADCSRA = 0xcf;	// Habilitamos el ADC, activamos interrupciones, configuramos
	// el divisor de reloj a 128
}