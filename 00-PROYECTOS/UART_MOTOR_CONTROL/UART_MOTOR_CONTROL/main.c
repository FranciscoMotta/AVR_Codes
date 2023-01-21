/*
 * UART_MOTOR_CONTROL.c
 *
 * Created: 20/01/2023 20:11:47
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "FM_USART.h"
#include "Interrpciones.h"

/* Definicion de macros */

// PILOTOS

#define LEDS_DDR			DDRC	
#define LEDS_PORT			PORTC	
#define LED_VERDE			0
#define LED_ROJA			1
#define LED_AMBAR			2
#define MASK_LEDS			(1 << LED_VERDE) | (1 << LED_ROJA) | (1 << LED_AMBAR)
#define LED_ROJA_ON()		LEDS_PORT |= (1 << LED_ROJA);
#define LED_ROJA_OFF()		LEDS_PORT &= ~(1 << LED_ROJA);
#define LED_VERDE_ON()		LEDS_PORT |= (1 << LED_VERDE);
#define LED_VERDE_OFF()		LEDS_PORT &= ~(1 << LED_VERDE);
#define LED_AMBAR_ON()		LEDS_PORT |= (1 << LED_AMBAR);
#define LED_AMBAR_OFF()		LEDS_PORT &= ~(1 << LED_AMBAR);
#define LED_AMBAR_TOGGLE()	LEDS_PORT ^= (1 << LED_AMBAR);

// MOTOR

#define MOTOR_DDR			DDRC
#define MOTOR_PORT			PORTC
#define MOTOR				3
#define MASK_MOTOR			(1 << MOTOR)
#define MOTOR_ON()			MOTOR_PORT |= (MASK_MOTOR);
#define MOTOR_OFF()			MOTOR_PORT &= ~(MASK_MOTOR);

/* Variables globales */

volatile bool state_motor = false;

/* Funciones de servicio a interrupciones */

char rx_buffer[20];
volatile uint8_t rx_counter = 0;

ISR(USART0_RX_vect)
{
	char dato = UDR0;
	if (dato == '*')
	{
		rx_buffer[rx_counter] = '\0';
		rx_counter = 0;
		if (strstr(rx_buffer, "motor=on"))
		{
			printf("\n\r");
			state_motor = true;
			printf("MOTOR ON\n\r");
		}
		else if (strstr(rx_buffer, "motor=off"))
		{
			printf("\n\r");
			state_motor = false;
			printf("MOTOR OFF\n\r");
		}
	}
	else
	{
		rx_buffer[rx_counter] = dato;
		rx_counter++;
	}
}

ISR(INT0_vect)
{
	state_motor = false;
	fprintf("parada emergencia\n\r");
}

ISR(INT1_vect)
{
	state_motor = true;
	fprintf("marcha directa\n\r");
}

/* Declaración de funciones */

void UART_Initialice (void);
void Init_Interrupt0 (void);
void Init_Interrupt1 (void);
void Init_GPIO_Motor (void);

void System_Init (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	// Inicio del systema
	cli();
	System_Init();
	sei();
	printf("INICIANDO SISTEMA...\n\r");
	state_motor = true;
	for (uint8_t init_counter = 0 ; init_counter < 6 ; init_counter ++)
	{
		LED_AMBAR_TOGGLE();
		_delay_ms(500);
	}
	printf("SISTEMA LISTO...\n\r");
	LED_AMBAR_OFF();
	while (1)
	{
		if (state_motor)
		{
			MOTOR_ON();
			LED_VERDE_ON();
			LED_ROJA_OFF();
		} 
		else
		{
			MOTOR_OFF();
			LED_VERDE_OFF();
			LED_ROJA_ON();
		}
	}
}

/* Definición de funciones */

void System_Init (void)
{
	UART_Initialice(); // Iniciamos el UART
	Init_Interrupt0(); // Iniciamos la interrupcion INT0
	Init_Interrupt1(); // Iniciamos la interrupcion INT1
	Init_GPIO_Motor(); // Iniciamos los pilotos
}

void Init_GPIO_Motor (void)
{
	LEDS_DDR |= MASK_LEDS; // Pilotos como salidas
	MOTOR_DDR |= MASK_MOTOR; // Motor como salida
	
	// Apagamos los GPIO de salida
	
	LEDS_PORT &= ~MASK_LEDS;
	MOTOR_PORT &= ~MASK_MOTOR;
	
}

void UART_Initialice (void)
{
	_my_uart_0_config_t my_uart;
	
	my_uart.baudios = BAUDRATE_9600;
	my_uart.bit_de_parada = UART_1_BIT_PARADA;
	my_uart.habilitar_rx = UART_ENABLE_RX0;
	my_uart.habilitar_tx = UART_ENABLE_TX0;
	my_uart.interrupcion_rx = UART_ENABLE_INTERRUPT_RXC0;
	my_uart.interrupcion_tx = UART_DISABLE_INTERRUPT_TXC0;
	my_uart.longitud_caracter = UART_CHARACTER_SIZE_8B;
	my_uart.modo_funcionamiento = UART_MODO_ASINCRONO;
	my_uart.multiprocesador_mode = UART_MULTI_PROCESOR_DISABLE;
	my_uart.noveno_bit_tx = NINTH_BIT_UART_LOW;
	my_uart.paridad = UART_PARIDAD_DESACTIVADA;
	my_uart.velocidad_doble_normal = UART_NORMAL_SPEED;
	
	UART0_Init(&my_uart);
}

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
