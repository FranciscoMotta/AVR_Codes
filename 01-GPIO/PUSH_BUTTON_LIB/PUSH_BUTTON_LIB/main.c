/*
 * PUSH_BUTTON_LIB.c
 *
 * Created: 14/01/2023 21:07:04
 * Author : jmott
 */ 

#define F_CPU 16000000L 

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <FM_Push_Boton_Lib.h>

/* Definicion de macros */

#define DDR_LED	DDRD
#define PORT_LED PORTD
#define LED	3
#define MASK_LED (1 << LED)
#define LED_TOGGLE() (PORT_LED ^= MASK_LED);
#define LED_OFF()	PORT_LED &= ~(MASK_LED);	
/* Declaración de funciones */

void Inicializacion_Led (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	Inicializacion_Led(); // Led como salida
	Inicializacion_Boton(BOTON_1, PULL_UP_DISABLE); // Boton 1 sin pullup
	while (1)
	{
		if (Leer_Boton_Sin_Rebote_Simple(BOTON_1))
		{
			LED_TOGGLE();
		}
	}
}

/* Definición de funcione */

void Inicializacion_Led (void)
{
	DDR_LED |= MASK_LED;
}