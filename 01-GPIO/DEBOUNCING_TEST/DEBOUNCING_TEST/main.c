/*
 * DEBOUNCING_TEST.c
 *
 * Created: 12/01/2023 21:28:52
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdbool.h>

/* Definicion de macros */

// Boton
#define DDR_BUTTON	DDRB
#define PIN_BUTTON	PINB
#define BUTTON_PIN	2
#define MASK_BUTTON	(1 << BUTTON_PIN)

// Led
#define DDR_LED	DDRB
#define PORT_LED PORTB
#define LED_PIN	3
#define MASK_LED (1 << LED_PIN)

// Debouncing maros
#define CONFIDENCE_LEVEL 500

/* Declaración de funciones */

/* Principal */

int main(void)
{
	/* Replace with your application code */
	// Boton como entrada
	DDR_BUTTON &= ~(MASK_BUTTON);
	// Led como salida
	DDR_LED |= (MASK_LED);
	PORT_LED &= ~(MASK_LED); // Led apagado
	
	bool button_press = false; // Estado del boton
	uint16_t pressed_button_counter = 0; // Contador de muestras de boton presionado
	uint16_t released_button_counter = 0; // Contador de muestras de boton suelto
	
	while (1)
	{
		if (bit_is_set(PIN_BUTTON, BUTTON_PIN))
		{
			pressed_button_counter++;
			if(pressed_button_counter > CONFIDENCE_LEVEL)
			{
				if (!button_press)
				{
					PORT_LED |= MASK_LED; // Prendemos el LED
					button_press = true;
				}
				pressed_button_counter = 0;
			}
		}
		else
		{
			released_button_counter++;
			if(released_button_counter > CONFIDENCE_LEVEL)
			{
				PORT_LED &= ~MASK_LED;
				button_press = false;
				released_button_counter = 0;
			}
		}
	}
}

/* Definición de funcione */