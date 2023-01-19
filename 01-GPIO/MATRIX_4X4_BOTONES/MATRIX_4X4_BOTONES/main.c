/*
 * MATRIX_4X4_BOTONES.c
 *
 * Created: 15/01/2023 19:12:58
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>

/* Definicion de macros */

// Matriz de botones 4x4
#define DDR_MATRIX_BOT	DDRA
#define PIN_MATRIX_BOT	PINA
#define MATRIX_BOT_DA	PINA4
#define MATRIX_BOT_A	PINA0
#define MATRIX_BOT_B	PINA1
#define MATRIX_BOT_C	PINA2
#define MATRIX_BOT_D	PINA3
#define MASK_MATRIX		(1 << MATRIX_BOT_DA) | (1 << MATRIX_BOT_A) | (1 << MATRIX_BOT_B) | (1 << MATRIX_BOT_C) | (1 << MATRIX_BOT_D)
#define MASK_MATRIX_DE  (1 << MATRIX_BOT_A) | (1 << MATRIX_BOT_B) | (1 << MATRIX_BOT_C) | (1 << MATRIX_BOT_D)
#define MASK_PIN_DA		PIN_MATRIX_BOT & (1 << MATRIX_BOT_DA)

// Leds de respuesta
#define DDR_LEDS		DDRC
#define PORT_LEDS		PORTC
#define LED1			0
#define LED2			1
#define LED3			2
#define LED4			3
#define MASK_LEDS		(1 << LED1)	| (1 << LED2) | (1 << LED3)	| (1 << LED4)

/* Declaración de funciones */

/* Principal */

uint8_t decode_caracteres[16] = {7, 8, 9, 0,
								 4, 5, 6, 0,
								 1, 2, 3, 0,
								 0, 0, 0, 0};

int main(void)
{
	/* Replace with your application code */
	// Inicializacion de las entradas de la matriz de botones
	DDR_MATRIX_BOT &= ~MASK_MATRIX;
	// Inicio de los leds
	DDR_LEDS |= MASK_LEDS;
	PORT_LEDS &= ~MASK_LEDS;
	while (1)
	{
		if (PIN_MATRIX_BOT & (1 << MATRIX_BOT_DA))
		{
			PORT_LEDS = PIN_MATRIX_BOT & 0x0F;
		}
	}
}

/* Definición de funciones */

