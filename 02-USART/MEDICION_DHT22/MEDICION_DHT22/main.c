/*
 * MEDICION_DHT22.c
 *
 * Created: 21/01/2023 21:53:24
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include "project_defines.h"
#include "FM_USART.h"
#include "FM_DHT22.h"

/* Definicion de macros */

/* Declaración de funciones */

void UART_Initialice (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	UART_Initialice();
	DHT22_INIT();
	printf("MEDICION DHT22\n\r");
	
	float temperatura_app;
	float humedad_app;
	
	while (1)
	{
		bool state_read = DHT22_Read_Temp_Hum(&temperatura_app, &humedad_app, GRADOS_CELCIUS);
		if (state_read)
		{
			printf("Temp: %.2f - Hum: %.2f\n\r", temperatura_app, humedad_app);
		}
		else
		{
			printf("Comunicacion error!\n\r");
		}
		_delay_ms(1000);
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