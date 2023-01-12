/*
 * LED_BLINK.c
 *
 * Created: 10/01/2023 23:07:43
 * Author : jmott
 */ 

/* Inclusión de archivos */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


/* Definicion de macros */

enum{
	LED1 = 0,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED7,
	LED8
	};


#define DDR_LEDS	DDRB
#define PORT_LEDS	PORTB
#define ROUGE_LED	LED5	

/* Declaración de funciones */

/* Principal */

int main(void)
{
	// Todo el puerto B como salida 
	DDR_LEDS = 0xFF; // 0b1111111 -> DDRB
	
	// Suponemos que tenemos la siguiente secuencia 11000111
	PORT_LEDS |= (1 << LED8) | (1 << LED7) | (1 << LED3) | (1 << LED2) | (1 << LED1); 
	
	while (1)
	{
		/* Ahora solo queremos modificar el estado del ROUGE_LED sin tocar los demás LEDS */
		PORT_LEDS ^= (1 << ROUGE_LED);
		_delay_ms(500);
	}
}

/* Definición de funciones */

