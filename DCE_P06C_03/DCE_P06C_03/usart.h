/*
 * usart.h
 *
 * Created: 12/04/2021 11:51:25
 *  Author: DCE
 */ 

#ifndef USART_H_
#define USART_H_

#ifndef FOSC
#define FOSC 16000000UL			// Clock Speed
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#ifndef MYUBRR
#define MYUBRR FOSC/16/BAUD-1
#endif

#include <avr/io.h>

// ---| This functions doesn't use interrupts|---

// This function will set up and initialize the USART port
void USART_Init(uint16_t ubrr);

// This function will transmit a byte
void USART_Transmit_Char(uint8_t data );

// This function will be transmitting bytes as specified on "size" parameter
void USART_Transmit(uint8_t *data, uint16_t size);

// This function will transmit the specified string
void USART_TransmitStr(char *str);

// This function will receive a byte
uint8_t USART_Receive_Char();

// This function will be receiving bytes up to the received data be the same as the "end" parameter, or up to the buffer being filled up
void USART_Receive_UpTo(uint8_t *buff, uint16_t buff_size, uint8_t end);


#endif /* USART_H_ */