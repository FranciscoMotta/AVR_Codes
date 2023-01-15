/*
 * USART_CONF.c
 *
 * Created: 15/01/2023 14:40:01
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <FM_USART.h>

/* Definicion de macros */

#define DDR_LEDS	DDRB
#define PORT_LEDS	PORTB
#define LED1		0
#define LED2		1
#define LED3		2
#define MASK_LEDS	(1 << LED1) | (1 << LED2) | (1 << LED3)
#define MASK_LED1 (1 << LED1)
#define MASK_LED2 (1 << LED2)
#define MASK_LED3 (1 << LED3)

/* Declaración de funciones */

void UART_Initialice (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	DDR_LEDS |= MASK_LEDS; // Leds como salidas
	PORT_LEDS &= ~MASK_LEDS; // Leds apagados
	UART_Initialice(); // Iniciamos el UART
	UART0_Escribir_Cadena("Hola\n\r");
	while (1)
	{
		uint8_t dato_uart = UART0_Leer_Byte();
		if (dato_uart != '\0')
		{
			switch (dato_uart)
			{
				case '1':
				PORT_LEDS |= (MASK_LED1);
				UART0_Escribir_Cadena("Led 1 ON\n\r");
				break;
				case '2':
				PORT_LEDS |= (MASK_LED2);
				UART0_Escribir_Cadena("Led 2 ON\n\r");
				break;
				case '3':
				PORT_LEDS |= (MASK_LED3);
				UART0_Escribir_Cadena("Led 3 ON\n\r");
				break;
				default:
				PORT_LEDS &= ~(MASK_LEDS);
				UART0_Escribir_Cadena("Leds OFF\n\r");
				break;
			}
		}
	}
}

/* Definición de funciones */

void UART_Initialice (void)
{
	_my_uart_0_config_t my_uart;
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