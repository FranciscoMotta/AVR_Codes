/*
 * BUTTON_GAME.c
 *
 * Created: 13/01/2023 16:43:12
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

/* Definicion de macros */

// Jugador 1

#define DDR_BOTON_J1	DDRB
#define BOTON_J1		0
#define PIN_BOTON_J1	PINB
#define MASK_BOTON_J1	(1 << BOTON_J1)
#define PORT_BOTON_J1	PORTB

#define DDR_LEDS_J1		DDRB
#define PORT_LEDS_J1	PORTB

// Jugador 2

#define DDR_BOTON_J2	DDRC
#define BOTON_J2		0
#define PIN_BOTON_J2	PINC
#define MASK_BOTON_J2	(1 << BOTON_J2)
#define PORT_BOTON_J2	PORTC

#define DDR_LEDS_J2		DDRC
#define PORT_LEDS_J2	PORTC

// Antirrebote

#define NIVEL_DE_SEGURIDAD	500

// Animaciones

#define REPETICIONES	5

/* Declaración de funciones */

void Init_GPIO_Players (void); 

/* Variables */

uint16_t boton_presionado_contador[2];
uint16_t boton_soltado_contador[2];
bool estado_presion[2] = {false, false};
uint8_t led_contador[2] = {1, 1};

/* Principal */

int main(void)
{
	/* Replace with your application code */
	Init_GPIO_Players();
	while (1)
	{
		/* Jugador 1 */
		
		if (PIN_BOTON_J1 & MASK_BOTON_J1)
		{
			boton_presionado_contador[0]++;
			if (boton_presionado_contador[0] > NIVEL_DE_SEGURIDAD)
			{
				if (estado_presion[0] == false)
				{
					estado_presion[0] = true;
					PORT_LEDS_J1 |= (1 << led_contador[0]);
					led_contador[0]++;
					if (led_contador[0] > 7)
					{
						led_contador[0] = 1;
						PORT_LEDS_J2 = 0x01;
						led_contador[1] = 1;
						uint8_t contador = 0;
						while (contador < REPETICIONES)
						{
							PORT_LEDS_J1 = 0xFF;
							_delay_ms(100);
							PORT_LEDS_J1 = 0x01;
							_delay_ms(100);
							contador++;
						}
					}
				}
				boton_presionado_contador[0] = 0;
			}
		}
		else
		{
			boton_soltado_contador[0]++;
			if (boton_soltado_contador[0] > NIVEL_DE_SEGURIDAD)
			{
				estado_presion[0] = false;
				boton_soltado_contador[0] = 0;	
			}
		}
		
		/* Jugador 2 */
		
		if (PIN_BOTON_J2 & MASK_BOTON_J2)
		{
			boton_presionado_contador[1]++;
			if (boton_presionado_contador[1] > NIVEL_DE_SEGURIDAD)
			{
				if (estado_presion[1] == false)
				{
					estado_presion[1] = true;
					PORT_LEDS_J2 |= (1 << led_contador[1]);
					led_contador[1]++;
					if (led_contador[1] > 7)
					{
						led_contador[1] = 1;
						uint8_t contador = 0;
						PORT_LEDS_J1 = 0x01;
						led_contador[0] = 1;
						while (contador < REPETICIONES)
						{
							PORT_LEDS_J2 = 0xFF;
							_delay_ms(100);
							PORT_LEDS_J2 = 0x01;
							_delay_ms(100);
							contador++;
						}
					}
				}
				boton_presionado_contador[1] = 0;	
			}
		}
		else
		{
			boton_soltado_contador[1]++;
			if (boton_soltado_contador[1] > NIVEL_DE_SEGURIDAD)
			{
				estado_presion[1] = false;
				boton_soltado_contador[1] = 0;
			}
		}
	}
}

/* Definición de funcione */

void Init_GPIO_Players(void)
{
	// Leds como salidas
	DDR_LEDS_J1 = 0xFF;
	DDR_LEDS_J2 = 0xFF;
	
	// Botones como entrada
	DDR_BOTON_J1 &= ~MASK_BOTON_J1;
	DDR_BOTON_J2 &= ~MASK_BOTON_J2;
	
	// Pull-Up resistors
	PORT_BOTON_J1 |= MASK_BOTON_J1;
	PORT_BOTON_J2 |= MASK_BOTON_J2;
}