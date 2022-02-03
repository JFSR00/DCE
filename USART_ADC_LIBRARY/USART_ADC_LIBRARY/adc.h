/*
 * adc.h
 *
 * Created: 12/04/2021 11:51:39
 *  Author: Juan Francisco Santos Relinque
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

// Esta funci�n inicializa el ADC
void initADC();

// Esta funci�n lanza la lectura del puerto ADC especificado haciendo uso de interrupciones
void readADCInt(uint8_t input);

// Esta funci�n habilita las interrupciones de ADC
void enableADCInt();

// Esta funci�n deshabilita las interrupciones de ADC
void disableADCInt();

// Esta funci�n iniciliza y realiza la lectura de ADC por polling del puerto especificado
uint16_t readADC(uint8_t input);

#endif /* ADC_H_ */