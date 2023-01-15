/*
 * FM_USART.c
 *
 * Created: 15/01/2023 14:52:28
 *  Author: jmott
 */ 

#include <FM_USART.h>

void UART0_Init (_my_uart_0_config_t *uart_params)
{
	/* Configuración de pines */
	
	UART0_DDR |= (1 << TX0_PIN);
	UART0_DDR &= ~(1 << RX0_PIN);
	
	/* Inicializacion de los regitros de trabajo */
	
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	
	/* Configuracion */
	
	// Registro UCSR0A
	
	UCSR0A &= ~(1 << TXC0);
	UCSR0A |= (uart_params->velocidad_doble_normal << U2X0);
	UCSR0A |= (uart_params->multiprocesador_mode << MPCM0);
	if (UCSR0A & (1 << U2X0))
	{
		UBRR0 = (F_CPU / (8 * uart_params->baudios)) - 1;
	} 
	else
	{
		UBRR0 = (F_CPU / (16 * uart_params->baudios)) - 1;
	}
	
	// Registro UCSR0B
	
	UCSR0B |= (uart_params->interrupcion_rx << RXCIE0) | (uart_params->habilitar_tx << TXCIE0) | (uart_params->noveno_bit_tx << TXB80);
	UCSR0B |= (uart_params->habilitar_rx << RXEN0) | (uart_params->habilitar_tx << TXEN0);
	
	uint8_t long_caracter = uart_params->longitud_caracter;
	uint8_t primer_bit_long = (long_caracter & 0x04) >> UCSZ02;
	
	UCSR0B |= (primer_bit_long << UCSZ02);
	
	// Registro UCSR0C
	
	uint8_t umsel_bits = (uart_params->modo_funcionamiento) & 0x03;
	UCSR0B |= ((umsel_bits & 0x02) >> 1) << UMSEL01;
	UCSR0B |= ((umsel_bits & 0x01)) << UMSEL00;
	
	uint8_t upm_bits = (uart_params->paridad) & 0x03;
	UCSR0C |= (((upm_bits & 0x02) >> 1) << UPM01) | ((upm_bits & 0x01) << UPM00);
	UCSR0C |= (uart_params->bit_de_parada << USBS0);
	UCSR0C |= (((long_caracter & 0x02) >> 1) << UCSZ01) | ((long_caracter & 0x01) << UCSZ00);
	UCSR0C |= (1 << UCPOL0);
}

/* Funcion para leer un byte del terminal serial */
unsigned char UART0_Leer_Byte (void)
{
	if (UCSR0A & (1 << RXC0))
	{
		return UDR0;
	} 
	else
	{
		return 0;
	}
}

/* Función para escribir un dato por el terminal serial*/
void UART0_Escribir_Byte (unsigned char dato)
{
	while (!(UCSR0A & (1 << UDRE0))); // Bucle mientras el registro UDR0 esté vacio
	UDR0 = dato;
}

/* Funcion para escribir una cadena de datos */
void UART0_Escribir_Cadena (char *cadena)
{
	uint16_t contador_item_cadena = 0;
	while (cadena[contador_item_cadena] != '\0')
	{
		UART0_Escribir_Byte(cadena[contador_item_cadena]);
		contador_item_cadena++;
	}
}