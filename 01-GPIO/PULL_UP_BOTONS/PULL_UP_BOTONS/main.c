/*
 * PULL_UP_BOTONS.c
 *
 * Created: 12/01/2023 18:56:28
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>

/* Definicion de macros */

// Botones
#define DDR_BOTONS	DDRD
#define PIN_BOTONS  PIND
#define PUR_BOTONS	PORTB // Pull Up Resistor

#define BOTON_1		1
#define BOTON_2		2
#define BOTON_3		3	

#define MASK_BOTONS	(1 << BOTON_1) | (1 << BOTON_2) | (1 << BOTON_3)
#define BOTON_1_MASK	(1 << BOTON_1)
#define BOTON_2_MASK	(1 << BOTON_2)
#define BOTON_3_MASK	(1 << BOTON_3)

#define BOTON_1_STATUS (PIN_BOTONS & BOTON_1_MASK)
#define BOTON_2_STATUS (PIN_BOTONS & BOTON_2_MASK)
#define BOTON_3_STATUS (PIN_BOTONS & BOTON_3_MASK)	

// Leds
#define DDR_LEDS	DDRB
#define PORT_LEDS	PORTB

#define LED_1		1
#define LED_2		2
#define LED_3		3	

#define MASK_LEDS (1 << LED_1) | (1 << LED_2) | (1 << LED_3)
#define LED_1_TOGGLE()	(PORT_LEDS ^= (1 << LED_1));
#define LED_2_TOGGLE()	(PORT_LEDS ^= (1 << LED_2));
#define LED_3_TOGGLE()	(PORT_LEDS ^= (1 << LED_3));

/* Declaración de funciones */

/* Principal */

int main(void)
{
	// Botones con pull-up resistencias
	PUR_BOTONS |= MASK_BOTONS;
	// Botones como entradas 
	DDR_BOTONS &= ~MASK_BOTONS;
	// Leds como salidas
	DDR_LEDS |= MASK_LEDS;
	// Leds iniciados en 0
	PORT_LEDS = 0x00;
	while (1)
	{
		if (!(PIN_BOTONS & BOTON_1_MASK))
		{
			LED_1_TOGGLE();
			_delay_ms(500);
		}
		if (!(PIN_BOTONS & BOTON_2_MASK))
		{
			LED_2_TOGGLE();
			_delay_ms(250);
		}
		if (!(PIN_BOTONS & BOTON_3_MASK))
		{
			LED_3_TOGGLE();
			_delay_ms(125);
		}
	}
}

/* Definición de funcione */

