/*
 * adc.h
 *
 * Created: 12/04/2021 11:51:39
 *  Author: Juan Francisco Santos Relinque
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

// Esta función inicializa el ADC
void initADC();

// Esta función lanza la lectura del puerto ADC especificado haciendo uso de interrupciones
void readADCInt(uint8_t input);

// Esta función habilita las interrupciones de ADC
void enableADCInt();

// Esta función deshabilita las interrupciones de ADC
void disableADCInt();

// Esta función iniciliza y realiza la lectura de ADC por polling del puerto especificado
uint16_t readADC(uint8_t input);

#endif /* ADC_H_ */