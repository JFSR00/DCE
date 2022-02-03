/*
 * adc.c
 *
 * Created: 12/04/2021 11:51:59
 *  Author: DCE
 */ 

#include "adc.h"

inline void initADC(){
	ADMUX = 0x40;	// Usamos AVCC, ADLAR = 0 y usamos ADC0
	ADCSRA = 0xcf;	// Habilitamos el ADC, activamos interrupciones, configuramos
	// el divisor de reloj a 128
}

inline void readADC(){
	ADCSRA |= (1<<ADSC);
}

inline uint16_t funADC(uint8_t input) {	// Por motivos aun desconocidos, esta función no funciona
	ADMUX = 0x00;					// Reseteamos los registros del ADC
	ADCSRA = 0x00;

	ADMUX = 0x40 | (input & 0x0f);	// Usamos AVCC, ADLAR = 0, usamos ADCn especificado por el parámetro
	ADCSRA = 0x87;					// Habilitamos el ADC, configuramos el divisor de reloj a 128
	
	ADCSRA |= (1<<ADSC);			// Iniciamos lectura de ADC
	while(!(ADCSRA&(1<<ADIF)));		// Esperamos hasta que termine la lectura del ADC
	ADCSRA |= (1<<ADIF);			// Limpiamos el flag de fin de lectura

	return ADC;
}