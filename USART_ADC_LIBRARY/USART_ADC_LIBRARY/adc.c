/*
 * adc.c
 *
 * Created: 12/04/2021 11:51:59
 *  Author: Juan Francisco Santos Relinque
 */

#include "adc.h"

inline void initADC(){
	ADMUX = 0x40;	// Usamos AVCC, ADLAR = 0 y usamos ADC0
	ADCSRA = 0xc7;	// Habilitamos el ADC, realizamos primera lectura, configuramos
					// el divisor de reloj a 128
}

inline void readADCInt(uint8_t input){
	ADMUX = 0x40 | (input & 0x0f);	// Usamos AVCC, ADLAR = 0, usamos ADCn especificado por el parámetro
	ADCSRA |= (1<<ADSC);
}

inline void enableADCInt(){
	ADCSRA |= (1<<ADIE);
}

inline void disableADCInt(){
	ADCSRA &= ~(1<<ADIE);
}

inline uint16_t readADC(uint8_t input) {
	ADMUX = (1 << REFS0) | (input & 0x0f);	// Usamos ADCn especificado por el parámetro

	// Habilitamos ADC, iniciamos lectura de ADC, limpiamos bandera de interrupción y configuramos divisor de reloj a 128
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIF) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	while(!(ADCSRA&(1<<ADIF)));				// Esperamos hasta que termine la lectura del ADC
	ADCSRA |= (1<<ADIF);					// Limpiamos el flag de fin de lectura

	return ADC;
}