/*
 * adc.h
 *
 * Created: 12/04/2021 11:51:39
 *  Author: Juan Francisco Santos Relinque
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void initADC();

void readADCInt(uint8_t input);

void enableADCInt();

void disableADCInt();

uint16_t funADC(uint8_t input);

#endif /* ADC_H_ */