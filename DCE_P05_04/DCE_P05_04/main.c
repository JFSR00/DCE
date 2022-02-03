/*
 * DCE_P05_04.c
 *
 * Created: 12/04/2021 9:39:15
 * Author : Juan Francisco Santos Relinque
 */

#define F_CPU 16000000UL	// Clock Speed

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define POT_POINT 300		// Umbral para lectura de LDR
#define LDR_POINT 600		// Umbral para lectura de potenci�metro

#define ADC_LDR 0x00		// M�scara para lectura de LDR
#define ADC_POT 0x01		// M�scara para lectura de potenci�metro

//-----------Prototypes--------------------------
static inline void initPorts();	// Funci�n de inicializaci�n depuertos
static inline void initINT0();	// Funci�n de inicializaci�n de interrupci�n INT0
static inline void initADC();	// Funci�n de inicializaci�n de ADC
static inline uint16_t funADC(uint8_t input);	// Funci�n encargada de la lectura del ADC en el puerto especificado

static inline void blink();		// Funci�n que parpadea 3 veces el LED de PORTB0

static inline void normal();	// Funci�n encargada del funcionamiento en modo NORMAL, controlado por el potenci�metro
static inline void night();		// Funci�n encargada del funcionamiento en modo NOCHE, controlado por la LDR en primer
								// lugar y por el potenci�metro en segundo

typedef enum {NORMAL = 0, NOCHE} Modos;	// Enumerado de modos: NORMAL = 0, NOCHE = 1 (los enumerados incrementan el valor
										//					   de sus elementos de 1 en uno a partir del anterior)
volatile Modos modo, sig_modo;

ISR(INT0_vect){
	modo = sig_modo;
}

int main(){
	//-----------| Variables locales |--------------------------
	modo = NORMAL;
	sig_modo = NOCHE;

	//-----------| Inicializaci�n |-------------------------------------
	initPorts();
	initINT0();
	initADC();
	sei();

	blink();

	//-----------| Bucle |-------------------------------------
	while(1){
		switch(modo){
			case NORMAL:
				normal();
				sig_modo = NOCHE;
				break;
			case NOCHE:
				night();
				sig_modo = NORMAL;
				break;
			default:
				blink();
				break;
		}

	}
}

//-----------| Funciones |--------------------------

static inline void initPorts(){
	// Configuracion de los LEDs
	DDRB |= (1<<PORTB0) | (1<<PORTB5);
	PORTB &= ~((1<<PORTB0)|(1<<PORTB5));
	// Configuracion del pulsador
	DDRD &= ~(1<<PORTD2);
	PORTD |= (1<<PORTD2);
}

static inline void initINT0(){
	EICRA|=(1<<ISC01);	// INT0-Falling edge
	EIMSK|=(1<<INT0);	// Enable INT0;
}

static inline void initADC(){
	ADMUX = 0x40;		// Usamos AVCC, ADLAR = 0 y usamos ADC0
	ADCSRA = 0x97;		// Habilitamos el ADC, deshabilitamos interrupciones, configuramos el divisor de reloj a 128
}

static inline uint16_t funADC(uint8_t input){
	cli();										// Deshabilitamos las interrupciones para esta funci�n

	ADMUX = (ADMUX & 0xf0) | (input & 0x0f);	// Configuramos el multiplexor de ADC para leer el puerto pasado por
	ADCSRA |= (1<<ADSC);						// par�metro y comenzamos la lectura poniendo a 1 el flag ADSC

	while(!(ADCSRA & (1 << ADIF))){}			// Esperamos a que finalice la lectura de ADC leyendo el flag ADIF
	ADCSRA |= (1 << ADIF);						// Borramos el flag ADIF escribiendo un 1 sobre �l

	sei();										// Reactivamos las interrupciones para el resto del programa

	return ADC;									// Devolvemos el resultado de la lectura del ADC
}

static inline void blink(){
	PORTB = 0x01;		// Encendemos LED por 300ms
	_delay_ms(300);
	PORTB = 0x00;		// Apagamos LED por 300ms
	_delay_ms(300);
	PORTB = 0x01;		// Encendemos LED por 300ms
	_delay_ms(300);
	PORTB = 0x00;		// Apagamos LED por 300ms
	_delay_ms(300);
	PORTB = 0x01;		// Encendemos LED por 300ms
	_delay_ms(300);

}

static inline void normal(){
	PORTB |= (1 << PORTB5);				// Cuando el LED principal es controlado por el potenci�metro, el secundario
	if(funADC(ADC_POT) >= POT_POINT){	// est� encendido
		PORTB |= 0x01;
	}else{
		PORTB &= 0xfe;
	}
}

static inline void night(){
	if(funADC(ADC_LDR) <= LDR_POINT){
		PORTB |= 0x01;
		PORTB &= ~(1 << PORTB5);		// Cuando el LED principal es controlado por la LDR, el secundario est� apagado
	}else{
		normal();
	}
}