/*
 * ROBOT_TEST_USB.c
 *
 * Created: 15/05/2021 19:49:07
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include "m_general.h"
#include "m_usb.h"

int main(void)
{
	// VARIABLES DEFINITIONS -------------------
	unsigned int value;

	// SETUP -----------------------------------
	m_usb_init();						// USB peripheral setup
	while(!m_usb_isconnected());		// Wait for a USB connection
	m_usb_tx_string("Hello world\n\r");	// Send a string (a pointer is used)
	
	// BEGIN -----------------------------------
	// LOOP ------------------------------------
	while (1){
		if(m_usb_rx_available()){	// If there is a character in buffer
			value=m_usb_rx_char();	// Read the character
			m_usb_tx_char(value);	// Print the ASCII character
			m_usb_tx_char('\t');
			m_usb_tx_uint(value);	// Print the decimal equivalent
			m_usb_tx_char('\n');
			m_usb_tx_char('\r');
		}
	}
}