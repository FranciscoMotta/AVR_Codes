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
#include <avr/interrupt.h>
#include <FM_USART.h>

/* Definicion de macros */

#define DDR_LEDS	DDRC
#define PORT_LEDS	PORTC
#define LED1		0
#define LED2		1
#define LED3		2
#define MASK_LEDS	(1 << LED1) | (1 << LED2) | (1 << LED3)
#define MASK_LED1 (1 << LED1)
#define MASK_LED2 (1 << LED2)
#define MASK_LED3 (1 << LED3)

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
		if (strstr(rx_buffer, "led=on"))
		{
			printf("\n\r");
			PORT_LEDS |= (MASK_LEDS);
			printf("Leds ON\n\r");
		}
		else if (strstr(rx_buffer, "led=off"))
		{
			printf("\n\r");
			PORT_LEDS &= ~(MASK_LEDS);
			printf("leds OFF\n\r");
		}
	}
	else
	{
		rx_buffer[rx_counter] = dato;
		rx_counter++;
	}
}

/* Declaración de funciones */

void UART_Initialice (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	cli();
	DDR_LEDS |= (MASK_LEDS)); // Leds como salidas
	PORT_LEDS &= ~(MASK_LEDS); // Leds apagados
	UART_Initialice(); // Iniciamos el UART
	sei();
	printf("Hi!\n\r");
	while (1)
	{
		
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
	my_uart.interrupcion_tx = UART_DISABLE_INTERRUPT_TXC0;
	my_uart.longitud_caracter = UART_CHARACTER_SIZE_8B;
	my_uart.modo_funcionamiento = UART_MODO_ASINCRONO;
	my_uart.multiprocesador_mode = UART_MULTI_PROCESOR_DISABLE;
	my_uart.noveno_bit_tx = NINTH_BIT_UART_LOW;
	my_uart.paridad = UART_PARIDAD_DESACTIVADA;
	my_uart.velocidad_doble_normal = UART_NORMAL_SPEED;
	
	UART0_Init(&my_uart);
}