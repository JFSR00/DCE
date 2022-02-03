/*
 * usart.c
 *
 * Created: 12/04/2021 11:51:52
 *  Author: DCE
 */ 

#include "usart.h"

void USART_Init(uint16_t ubrr){
	//1.-Set baud rate
	UBRR0H = (uint8_t) (ubrr>>8);
	UBRR0L = (uint8_t) ubrr;
	//2.-Set the speed: Normal Asynchronous
	UCSR0A &= ~(1<<U2X0);
	//3.-Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	//4.-Set frame format: 8data, 1stop bit
	UCSR0C |= (3<<UCSZ00);
}

void USART_Transmit_Char(uint8_t data ){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Transmit(uint8_t *data, uint16_t size){
	while(size){
		USART_Transmit_Char(*data);
		data++;
		size--;
	}
}

void USART_TransmitStr(char *str){
	while(*str){
		USART_Transmit_Char((uint8_t)*str);
		str++;
	}
}

uint8_t USART_Receive_Char(){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_Receive_UpTo(uint8_t *buff, uint16_t buff_size, uint8_t end){
	if(buff_size && buff){		// Comprobamos que el buffer no es un puntero nulo y que su tamaño es distinto de 0
								// We verify that the buffer isn't NULL pointer and it's size is distinct of 0
		do{
			*buff = USART_Receive_Char();
			buff++;
			buff_size--;
		} while (buff_size && (*(buff - 1) != end));
	}
}