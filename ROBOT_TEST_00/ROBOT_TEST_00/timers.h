/*
 * timers.h
 *
 * Created: 13/05/2021 17:28:59
 * Author: Juan Francisco Santos Relinque
 */


#ifndef TIMERS_H_
#define TIMERS_H_

#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifndef TIMER0_PRESC
#define TIMER0_PRESC 64
#endif

// Macro definition to calculate OCR value from desired frequency and prescaler
#define OCR(freq, presc) (F_CPU/presc/freq-1)

// --------------------| TIMER 0 |---------------------------------------------------------------------
// WARNING!!!
// This timer works using interrupts

// This function initialize Timer0 to the desired OCR and prescaler configuration
void timer0_init(uint8_t ocr, uint16_t prescaler);

// This function enables Timer0 interrupt on match with register OCR0A
void timer0_enaINT();

// This function enables Timer0 interrupt on match with register OCR0A
void timer0_disINT();

// This function sets the OCR0A register to the correspondig value of the spefified frequency
void timer0_setFreq(uint16_t freq);

// This function sets OCR0A value to the specified OCR value
void timer0_setOCR(uint8_t ocr);


// --------------------| TIMER 1 |---------------------------------------------------------------------
// This function initialize Timer1 with 1024 prescaler to be used as delay timer for millisecond sizes delays
void timer1_init();

// This function delays the specified amount of milliseconds
void timer1_delay_ms(float delay);

// ----------------------------------------------------------------------------------------------------
// WARNING!!!
// This function overwrites previous Timer0 and Timer1 configurations and uses interrupts

// This function reproduces a melody descripted on the uint16_t vector *freqs, which contains the frequencies of the
// melody. The period of every tone is setted by the period parameter, and the number of tones of the melody
// are specified by the size parameter
//
// uint16_t *freqs:	Vector of frequencies which makes the melody
// float period:	Period of every tone
// uint8_t size:	Number of tones (size of *freqs vector)

void melody(uint16_t *freqs, float period, uint8_t size);

#endif /* TIMERS_H_ */