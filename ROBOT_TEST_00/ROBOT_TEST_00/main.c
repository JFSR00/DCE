/*
 * ROBOT_TEST_00.c
 *
 * Created: 10/05/2021 9:17:30
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timers.h"

int main(void)
{
	// VARIABLES DEFINITIONS -------------------
	uint16_t startMelody[3] = {330,370,392};	// Definition of start up melody
	// SETUP -----------------------------------
	// BEGIN -----------------------------------
	melody(startMelody, 150, 3);				// Reproduction of start up melody

	// LOOP ------------------------------------
    while (1){}
}
