/*
 * LEDS.c
 *
 * Created: 10/01/2023 22:38:40
 * Author : jmott
 */ 

/* Inclusión de archivos */

#include <avr/io.h>  

/* Definicion de macros */

#define LED1		4
#define LED2		5
#define LED3		6	
#define LED4		7

#define LEDS_MASKS	(1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4)

/* Declaración de funciones */

/* Principal */

int main(void)
{
    /* Replace with your application code */
	
	/* PINES: PB4 - PB5 - PB6 - PB7 como salida */
	DDRB |= (1 << LEDS_MASKS); // Direction Data Registers
	
    while (1) 
    {
		PORTB |= ((1 << LED1) | (1 << LED2)); // 5v to PB5-PB4
		PORTB &= ~((1 << LED3) | (1 << LED4)); // 0v to PB6-PB7
    }
}

/* Definición de funciones */