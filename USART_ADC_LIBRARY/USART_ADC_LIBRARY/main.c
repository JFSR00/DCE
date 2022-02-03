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

static inline void initPorts();	// Función de inicialización de puertos

int main(void)
{
	uint8_t buff[10];
	
	initPorts();
	initADC();
	USART_Init(MYUBRR);
	//USART_defInit();
	
	//USART_TransmitStr("Hola\n");
	
	while (1) 
	{
		utoa(funADC(0x01), (char*)buff, 10);
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


/*
#include<avr/io.h>
#define FOSC 16000000			// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1	//103 cycles system-clk

//-----------Prototypes--------------------------
static inline void USART_Init(uint16_t ubrr);
static inline void USART_TX_char(unsigned char data);

int main(){
	//-----------Local variables --------------------------
	char *strPointer = "Hello World ";
	
	//-----------SETUP-------------------------------------
	USART_Init(MYUBRR);
	
	//-----------LOOP-------------------------------------
	while(1){
		while(*strPointer){
			USART_TX_char(*strPointer);
			strPointer++;
		}
	}
}

//-----------Functions--------------------------
static inline void USART_Init(uint16_t ubrr){
	//1.-Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//2.-Set the speed: Normal Asynchronous
	UCSR0A &= (0<<U2X0);	// NOT default option!!!!!
	//3.-Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//4.-Set frame format: 8data, 1stop bit
	UCSR0C |= (3<<UCSZ00);
}

static inline void USART_TX_char(unsigned char data){
	// (Polling) Wait for empty transmit buffer
	while(!(UCSR0A&(1<<UDRE0)));
	// Put data into buffer, sends the data
	UDR0=data;
}
*/