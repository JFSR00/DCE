/*
 * TMR1.h
 *
 * Created: 03/05/2021 9:13:09
 *  Author: DCE
 */ 


#ifndef TMR1_H_
#define TMR1_H_

#include <avr/io.h>

void TMR1_CTC_irq();
void TMR1_CTC_set(uint16_t);
void TMR1_CTC_start();

#endif /* TMR1_H_ */