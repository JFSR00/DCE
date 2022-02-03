/*
 * ROBOT_TEST_OPTICAL.c
 *
 * Created: 15/05/2021 19:58:07
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "adc.h"
#include "timers.h"
#include "m_general.h"
#include "m_usb.h"

// That macro convert volts to ADC resolution value
#define V_to_ADC(v) (v*1024/5)
#define WHITE V_to_ADC(4.7)

// ADC ports of every sensor
#define IR0 0x07
#define IR1 0x06
#define IR2 0x05
#define IR3 0x04
#define IR4 0x01

void printMenu();

int main(void)
{
	// VARIABLES DEFINITIONS -------------------
	uint8_t opt;						// Variable for selected option from menu
	uint16_t adcVal = 0;				// Variable for ADC read value
	
	// SETUP -----------------------------------
	m_usb_init();						// USB peripheral setup
	while(!m_usb_isconnected());		// Wait for a USB connection
	
	// BEGIN -----------------------------------
	printMenu();

	// LOOP ------------------------------------
	while (1){
		while(!m_usb_rx_available()){}	// Wait up to receiving a character
		opt = m_usb_rx_char();			// Read the character
		
		// Here we read the sensor specified by the user through menu options
		if(opt != 'm'){							// If selected option is Print menu, prints menu, in other
			m_usb_tx_string("Reading ");	// case prints the specified sensor read value with it's
			switch(opt){						// correspondig identifier
				case '0':
					adcVal = readADC(IR0);
					m_usb_tx_string("IR0 ");
					break;
				case '1':
					adcVal = readADC(IR1);
					m_usb_tx_string("IR1 ");
					break;
				case '2':
					adcVal = readADC(IR2);
					m_usb_tx_string("IR2 ");
					break;
				case '3':
					adcVal = readADC(IR3);
					m_usb_tx_string("IR3 ");
					break;
				case '4':
					adcVal = readADC(IR4);
					m_usb_tx_string("IR4 ");
					break;
				default:
					m_usb_tx_string("0 ");
					adcVal = 0;
					break;
			}
			m_usb_tx_string(": ");
			m_usb_tx_uint(adcVal);			// Sends the ADC read value
		}else{
			printMenu();
		}
		
		m_usb_tx_string("\n\n\r");
	}
}

void printMenu(){
	m_usb_tx_string("\033[1J");			// With this two first lines cleans screen, then prints the menu
	m_usb_tx_string("\033c");
	m_usb_tx_string("\n\r0.-Measure of the IR0\n\r1.-Measure of the IR1\n\r2.-Measure of the IR2\n\r3.-Measure of the IR3\n\r4.-Measure of the IR4\n\n\rm.-Print menu\n\n\rOption: ");
}

/*
// TEST MAIN -----------------------------------

int main(void)
{
	// VARIABLES DEFINITIONS -------------------
	// SETUP -----------------------------------
	// BEGIN -----------------------------------
	// Start up beeps
	beep(3000, 100);				// 3000 Hz sound frequency and 100 ms duration
	timer1_delay_ms(50);
	beep(3000, 100);

	// LOOP ------------------------------------
	while (1){
		timer1_delay_ms(1000);
		if(readADC(0x07) >= WHITE){	// If read value by ADC is above 4.7 volts, surface is white, so the robot makes
			beep(3000, 200);		// a 3 KHz beep, else makes a 1 KHz beep, both of them with a 100 ms duration.
		}else{
			beep(1000, 200);
		}
	}
}
*/