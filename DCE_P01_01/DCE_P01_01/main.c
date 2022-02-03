/*
 * DCE_P01_01.c
 *
 * Created: 12/04/2021 8:50:54
 * Author : DCE
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB |= (1 << PORTB5);
    while (1) 
    {
		PORTB ^= (1 << PORTB5);
		_delay_ms(500);
    }
}

