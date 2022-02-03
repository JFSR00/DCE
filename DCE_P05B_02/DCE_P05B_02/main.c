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

#define ADC_PORT 0x01

static inline void initPorts();	// Función de inicialización de puertos

int main(void)
{
	uint8_t i = 0;
	uint8_t buff[5];
	uint16_t media = 0;
	
	initPorts();
	initADC();
	USART_Init(MYUBRR);
	
	/*
	Tip:As  the  first  conversion  takes  more  cycles  than  afterwards  (25  vs  13 cycles)
	it  is recommendable to discard the first one. Besides, taking several readouts and average them,
	gives  you  a more  accuracy  measure.  (It  is more  optimal  to  take  2^n  readout  to average
	by means of shift operations instead of a division).
	*/
	
	funADC(ADC_PORT);
	
	while(1){
		media = 0;
		for(i = 0; i < 8; i++){
			media += funADC(ADC_PORT);
		}
		media = (media >> 3);
		
		utoa(media, (char*)buff, 10);
		USART_TransmitStr("    \r");
		USART_TransmitStr(buff);
		USART_Transmit_Char('\r');
		_delay_ms(500);
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
