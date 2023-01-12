/*
 * BOTON_SIMPLE.c
 *
 * Created: 12/01/2023 15:43:45
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>

/* Definicion de macros */

#define DDR_BOTON	DDRD
#define PIN_BOTON	PIND
#define BOTON	1
#define MASK_BOTON (1 << BOTON)
#define DDR_LED		DDRB
#define PORT_LED	PORTB
#define LED		2

/* Declaración de funciones */

/* Principal */

int main(void)
{
	/* Replace with your application code */
	DDR_BOTON &= ~(1 << BOTON); // Boton como entrada
	DDR_LED |= (1 << LED); // Led como salida
	while (1)
	{
		if (PIN_BOTON & MASK_BOTON)
		{
			PORT_LED |= (1 << LED); // Led encendido
		} 
		else
		{
			PORT_LED &= ~(1 << LED); // Led apagado
		}
	}
}

/* Definición de funciones */
