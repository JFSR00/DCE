/*
 * adc.h
 *
 * Created: 12/04/2021 11:51:39
 *  Author: DCE
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

// ---| This functions doesn't use interrupts|---

void initADC();
uint16_t funADC(uint8_t input);
void readADC();



#endif /* ADC_H_ */