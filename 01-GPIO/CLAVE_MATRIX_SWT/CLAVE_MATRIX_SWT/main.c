/*
 * CLAVE_MATRIX_SWT.c
 *
 * Created: 18/01/2023 17:11:05
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include "FM_USART.h"
#include <stdbool.h>

/* Definicion de macros */

#define DDR_MATRIX	DDRA	
#define PIN_MATRIX	PINA
#define MATRIX_DE	4
#define MATRIX_A	0
#define MATRIX_B	1
#define MATRIX_C	2
#define MATRIX_D	3
#define MASK_MATRIX (1 << MATRIX_DE) | (1 << MATRIX_A) | (1 << MATRIX_B) | (1 << MATRIX_C) | (1 << MATRIX_D)

#define DDR_LEDS	DDRC
#define PORT_LEDS	PORTC
#define LED_1		0
#define LED_2		1
#define LED_3		2
#define LED_4		3
#define MASK_LEDS	(1 << LED_1) | (1 << LED_2) | (1 << LED_3) | (1 << LED_4)

#define DDR_BUZZER DDRC
#define PORT_BUZZER PORTC
#define BUZZER	4
#define BUZZER_TOGGLE() PORT_BUZZER ^= (1 << BUZZER);

#define DDR_MOTOR_LOCK	DDRC
#define PORT_MOTOR_LOCK	PORTC
#define MOTOR	5
#define MASK_MOTOR (1 << MOTOR)
#define MOTOR_ENABLE()	PORT_MOTOR_LOCK |= MASK_MOTOR;
#define MOTOR_DISABLE()	PORT_MOTOR_LOCK &= ~MASK_MOTOR;
 
/* Declaración de funciones */

_my_uart_0_config_t my_uart;

void Init_pines (void);
void UART_Init_Local (void);

/* Variables globales */

unsigned char datos_decode_matrix[16] = {'7', '8', '9', '%',
										 '4', '5', '6', 'x',
										 '1', '2', '3', '-',
										 'p', '0', '=', '+'};

char mensaje_inicial[] = "Escribe tu clave: \r";
char mensaje_clave_in[] = "Clave ingresada\r";
char mensaje_clave_ok[] = "Clave correcta\r";
char mensaje_clave_nok[] = "Clave incorrecta\r";
char clave_save[] = "4550";
char clave_user[4];
uint8_t clave_index = 0;
uint8_t intentos = 0;
/* Principal */

int main(void)
{
	/* Replace with your application code */
	UART_Init_Local(); // Iniciamos el UART
	Init_pines(); // Iniciamos los pines del Atmega2560
	UART0_Escribir_Cadena(mensaje_inicial);
	while (1)
	{
		while (clave_index < 4)
		{
			if(PIN_MATRIX & (1 << MATRIX_DE))
			{
				while((PIN_MATRIX & (1 << MATRIX_DE)));
				uint8_t data_from_matrix = PIN_MATRIX & 0x0F;
				UART0_Escribir_Byte(datos_decode_matrix[data_from_matrix]);
				clave_user[clave_index] = datos_decode_matrix[data_from_matrix];
				clave_index++;
			}
		}
		UART0_Escribir_Byte('\r');
		clave_index = 0;
		UART0_Escribir_Cadena(mensaje_clave_in);
		uint8_t equality_counter = 0;
		for (uint8_t i = 0 ; i < 4 ; i++)
		{
			if (clave_user[i] == clave_save[i])
			{
				equality_counter++;
			}
		}
		if (equality_counter == 4)
		{
			UART0_Escribir_Cadena(mensaje_clave_ok);
			MOTOR_ENABLE();
			_delay_ms(3000);
			MOTOR_DISABLE();
			intentos = 0;
			PORT_LEDS &= ~(MASK_LEDS);
		} 
		else
		{
			UART0_Escribir_Cadena(mensaje_clave_nok);
			PORT_LEDS |= (1 << intentos);
			intentos++;
		}
		equality_counter = 0;
		if (intentos == 4)
		{
			UART0_Escribir_Cadena("Supero numero de intentos\r");
			while (1)
			{
				BUZZER_TOGGLE();
				PORT_LEDS ^= (1 << LED_1) | (1 << LED_2) | (1 << LED_3) | (1 << LED_4);
				_delay_ms(500);
			}
		}
	}
}

/* Definición de funciones */

void UART_Init_Local (void)
{
	my_uart.baudios = BAUDRATE_9600;
	my_uart.bit_de_parada = UART_1_BIT_PARADA;
	my_uart.habilitar_rx = UART_ENABLE_RX0;
	my_uart.habilitar_tx = UART_ENABLE_TX0;
	my_uart.interrupcion_rx = UART_ENABLE_INTERRUPT_RXC0;
	my_uart.interrupcion_tx = UART_DISABLE_INTERRUPT_RXC0;
	my_uart.longitud_caracter = UART_CHARACTER_SIZE_8B;
	my_uart.modo_funcionamiento = UART_MODO_ASINCRONO;
	my_uart.multiprocesador_mode = UART_MULTI_PROCESOR_DISABLE;
	my_uart.noveno_bit_tx = NINTH_BIT_UART_LOW;
	my_uart.paridad = UART_PARIDAD_ACTIVADA_EVEN;
	my_uart.velocidad_doble_normal = UART_NORMAL_SPEED;
	
	UART0_Init(&my_uart);
}

void Init_pines (void)
{
	DDR_MATRIX &= ~MASK_MATRIX; // Pines de la matriz de pulsdores como entradas
	DDR_LEDS |= MASK_LEDS; // Pines leds como salidas
	DDR_BUZZER |= (1 << BUZZER); // Pin buzzer como salida
	DDR_MOTOR_LOCK |= (1 << MOTOR); // Pin motor como salida
}