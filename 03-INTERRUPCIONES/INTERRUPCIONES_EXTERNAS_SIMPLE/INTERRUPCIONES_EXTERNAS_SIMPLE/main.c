/*
 * INTERRUPCIONES_EXTERNAS_SIMPLE.c
 *
 * Created: 18/01/2023 20:44:58
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Interrpciones.h>

/* Definicion de macros */
	
#define LED_DDR			DDRC
#define LED_PORT		PORTC
#define LED				0
#define MASK_LED		(1 << LED)
#define LED_OUTPUT()	LED_DDR |= (MASK_LED);
#define LED_TOGGLE()	LED_PORT ^= (MASK_LED);

#define ROUGE_LED_DDR	DDRC
#define ROUGE_LED_PORT	PORTC
#define ROUGE_LED		4
#define MASK_ROUGE_LED (1 << ROUGE_LED)
#define ROUGE_LED_OUTPUT() ROUGE_LED_DDR |= (MASK_ROUGE_LED);
#define ROUGE_LED_TOGGLE() ROUGE_LED_PORT ^= MASK_ROUGE_LED;

/* Declaración de funciones */

void Init_Interrupt0 (void);
void Init_Interrupt1 (void);

/* Funciones de servicio a interrupciones */

ISR (INT0_vect)
{
	LED_PORT ^= MASK_LED;
}

ISR(INT1_vect, ISR_ALIASOF(INT0_vect));

/* Principal */

int main(void)
{
	/* Replace with your application code */
	LED_OUTPUT();
	ROUGE_LED_OUTPUT();
	LED_PORT |= MASK_LED;
	Init_Interrupt0();
	Init_Interrupt1();
	while (1)
	{
		ROUGE_LED_TOGGLE();
		_delay_ms(100);
	}
}

/* Definición de funciones */
void Init_Interrupt0 (void)
{
	_interrupciones_config_t my_int0;
	my_int0.int0_control = INT0_ACTIV_FLANCO_SUB;
	my_int0.int0_enable = INT0_ENABLE;
	my_int0.banderas_ints = INTS_CLEAR;
	my_int0.pull_up = INTS_PULL_UP_DISABLE;
	Interrupciones_Init(&my_int0); 
}


void Init_Interrupt1(void)
{
	_interrupciones_config_t my_int1;
	my_int1.int1_control = INT1_ACTIV_FLANCO_SUB;
	my_int1.int1_enable = INT1_ENABLE;
	my_int1.banderas_ints = INTS_CLEAR;
	my_int1.pull_up = INTS_PULL_UP_DISABLE;
	Interrupciones_Init(&my_int1);
}