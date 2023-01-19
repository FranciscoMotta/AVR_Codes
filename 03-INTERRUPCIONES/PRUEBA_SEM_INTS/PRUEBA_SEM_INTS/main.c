/*
 * PRUEBA_SEM_INTS.c
 *
 * Created: 19/01/2023 15:47:08
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "Interrpciones.h"

/* Definicion de macros */

#define soft_reset() do { wdt_enable(WDTO_15MS); for (;;); } while (0);

// MACROS DEL SEMÁFORO

// luz verde

#define LUZ_VERDE_DDR			DDRC
#define LUZ_VERDE_PORT			PORTC
#define LUZ_VERDE				0
#define LUZ_VERDE_MASK			(1 << LUZ_VERDE)
#define LUZ_VERDE_ON()			LUZ_VERDE_PORT |= (LUZ_VERDE_MASK);
#define LUZ_VERDE_OFF()			LUZ_VERDE_PORT &= ~(LUZ_VERDE_MASK); 
#define LUZ_VERDE_OUTPUT()		LUZ_VERDE_DDR |= (LUZ_VERDE_MASK);

// luz ambar

#define LUZ_AMBAR_DDR			DDRC
#define LUZ_AMBAR_PORT			PORTC
#define LUZ_AMBAR				1
#define LUZ_AMBAR_MASK			(1 << LUZ_AMBAR)
#define LUZ_AMBAR_ON()			LUZ_AMBAR_PORT |= (LUZ_AMBAR_MASK);
#define LUZ_AMBAR_OFF()			LUZ_AMBAR_PORT &= ~(LUZ_AMBAR_MASK);
#define LUZ_AMBAR_OUTPUT()		LUZ_AMBAR_DDR |= (LUZ_AMBAR_MASK);

// luz roja

#define LUZ_ROJA_DDR			DDRC
#define LUZ_ROJA_PORT			PORTC
#define LUZ_ROJA				2
#define LUZ_ROJA_MASK			(1 << LUZ_ROJA)
#define LUZ_ROJA_ON()			LUZ_ROJA_PORT |= (LUZ_ROJA_MASK);
#define LUZ_ROJA_OFF()			LUZ_ROJA_PORT &= ~(LUZ_ROJA_MASK);
#define LUZ_ROJA_OUTPUT()		LUZ_ROJA_DDR |= (LUZ_ROJA_MASK);

/* Variables globales */

typedef enum
{
	LUZ_VERDE_ACTIVADA = 0,
	LUZ_AMBAR_ACTIVADA,
	LUZ_ROJA_ACTIVADA
}_state_sem_t;

_state_sem_t actual_state = LUZ_VERDE_ACTIVADA;

bool stop_state = false;

/* Funciones de servicio a interrupciones */

ISR(INT0_vect)
{
	LUZ_VERDE_OFF();
	LUZ_ROJA_ON();
	LUZ_AMBAR_OFF();
	_delay_ms(5000);
	soft_reset();
}

ISR(INT1_vect, ISR_ALIASOF(INT0_vect));

/* Declaración de funciones */

void Init_Luces_Semaforo (void);
void Init_Interrupciones (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	Init_Luces_Semaforo();
	Init_Interrupciones();
	while (1)
	{
		switch(actual_state)
		{
			case LUZ_VERDE_ACTIVADA:
				LUZ_VERDE_ON();
				LUZ_ROJA_OFF();
				LUZ_AMBAR_OFF();
				_delay_ms(3000);
				actual_state = LUZ_AMBAR_ACTIVADA;
			break;
			case LUZ_AMBAR_ACTIVADA:
				LUZ_VERDE_OFF();
				LUZ_ROJA_OFF();
				LUZ_AMBAR_ON();
				_delay_ms(500);
				actual_state = LUZ_ROJA_ACTIVADA;
			break;
			case LUZ_ROJA_ACTIVADA:
				LUZ_VERDE_OFF();
				LUZ_ROJA_ON();
				LUZ_AMBAR_OFF();
				_delay_ms(2000);
				actual_state = LUZ_VERDE_ACTIVADA;
			break;
		}
	}
}

/* Definición de funciones */

void Init_Interrupciones (void)
{
	_interrupciones_config_t my_ints01;
	
	// Int0
	
	my_ints01.banderas_ints = INTS_CLEAR;
	my_ints01.int0_control = INT0_ACTIV_FLANCO_SUB;
	my_ints01.int0_enable = INT0_ENABLE;
	
	// Int1
	
	my_ints01.int1_control = INT1_ACTIV_FLANCO_SUB;
	my_ints01.int1_enable = INT0_ENABLE;
	my_ints01.pull_up = INTS_PULL_UP_DISABLE;
	
	Interrupciones_Init(&my_ints01);
}

void Init_Luces_Semaforo (void)
{
	// Pines de las luces como salidas
	
	LUZ_VERDE_OUTPUT();
	LUZ_AMBAR_OUTPUT();
	LUZ_ROJA_OUTPUT();
	
	// Luces inician apagadas
	
	LUZ_VERDE_OFF();
	LUZ_AMBAR_OFF();
	LUZ_ROJA_OFF();
}
