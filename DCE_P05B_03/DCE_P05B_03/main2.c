/*
 * USART_ADC_LIBRARY.c
 *
 * Created: 12/04/2021 11:50:44
 * Author : DCE
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "adc.h"
#include "usart.h"

#define ADC_LDR 0x00
#define ADC_POT 0x01

static inline void initPorts();	// Función de inicialización de puertos
static inline uint16_t readADC_8samples(uint8_t port);

int main(void)
{
	uint8_t buff[5];
	uint8_t opt;
	
	initPorts();
	initADC();
	USART_Init(MYUBRR);
	
	USART_TransmitStr("1.-Measure of the LDR\n\r2.-Measure of the potentiometer\n\rOption: ");
	
	while(1){
		if(UCSR0A & (1<<RXC0)){		// Comprobamos si hay algún caracter por leer, de esta manera no bloqueamos el funcionamiento del microcontrolador
			opt = UDR0;				// Leemos el dato recibido
			
			USART_TransmitStr("\n\n\rReading: ");
			
			switch(opt){
				case '1':
					utoa(readADC_8samples(ADC_LDR), (char*)buff, 10);
					break;
				case '2':
					utoa(readADC_8samples(ADC_POT), (char*)buff, 10);
					break;
				default:
					buff[0] = 0x00;
					USART_TransmitStr("\rWrong key!");
				break;
			}
			
			USART_TransmitStr((char*)buff);
			USART_TransmitStr("\n\n\r1.-Measure of the LDR\n\r2.-Measure of the potentiometer\n\rOption: ");
		}
	}
}

static inline void initPorts(){
	// Configuracion de los LEDs
	DDRB |= (1<<PORTB0) | (1<<PORTB5);
	PORTB &= ~((1<<PORTB0)|(1<<PORTB5));
	// Configuracion del pulsador
	DDRD &= ~(1<<PORTD2);
	PORTD |= (1<<PORTD2);
}

static inline uint16_t readADC_8samples(uint8_t port){
	uint16_t media = 0;
	uint8_t i;
	
	funADC(port);
	
	for(i = 0; i < 8; i++){
		media += funADC(port);
	}
	
	return (media >> 3);
}