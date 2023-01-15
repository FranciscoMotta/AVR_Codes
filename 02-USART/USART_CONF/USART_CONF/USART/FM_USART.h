/*
 * FM_USART.h
 *
 * Created: 15/01/2023 14:52:10
 *  Author: jmott
 */ 


#ifndef FM_USART_H_
#define FM_USART_H_

#define F_CPU 16000000UL	

#include <avr/io.h>

/* Definición de macros */

#define TX0_PIN	PINE1
#define RX0_PIN PINE0
#define UART0_DDR DDRE

/* Estructuras - Enumeraciones - Typedef */

// BITS RW REGISTRO UCSR0A

typedef enum
{
	UART_NORMAL_SPEED = 0,
	UART_DOUBLE_SPEED 
}_u2x0_bit_uart_t;

typedef enum
{
	UART_MULTI_PROCESOR_DISABLE = 0,
	UART_MULTI_PROCESOR_ENABLE
}_mpcm0_bit_uart_t;

// BITS RW REGISTRO UCSR0B

typedef enum
{
	UART_DISABLE_INTERRUPT_RXC0 = 0,
	UART_ENABLE_INTERRUPT_RXC0
}_rxcie0_bit_uart_t;

typedef enum
{
	UART_DISABLE_INTERRUPT_TXC0 = 0,
	UART_ENABLE_INTERRUPT_TXC0
}_txcie0_bit_uart_t;

typedef enum
{
	UART_DISABLE_RX0 = 0,
	UART_ENABLE_RX0
}_rxen0_bit_uart_t;


typedef enum
{
	UART_DISABLE_TX0 = 0,
	UART_ENABLE_TX0	
}_txen0_bit_uart_t;

typedef enum
{
	UART_CHARACTER_SIZE_5B = 0b000,
	UART_CHARACTER_SIZE_6B,
	UART_CHARACTER_SIZE_7B, 
	UART_CHARACTER_SIZE_8B, 
	UART_CHARACTER_SIZE_9B = 0b111
}_ucsz_reg_uart_t;

typedef enum
{
	NINTH_BIT_UART_LOW = 0,
	NINTH_BIT_UART_HIGH
}_ninth_bit_9_bit_transmit_uart_t;

// BITS RW REGISTRO UCSR0C

typedef enum
{
	UART_MODO_ASINCRONO = 0b00,
	UART_MODO_SINCRONO,
	UART_MODO_RESERVADO,
	SPI_MASTER
}_umsel_reg_uart_t;

typedef enum
{
	UART_PARIDAD_DESACTIVADA = 0b00,
	UART_PARIDAD_RESERVADA,
	UART_PARIDAD_ACTIVADA_EVEN,
	UART_PARIDAD_ACTIVADA_ODD
}_upm_reg_uart_t;

typedef enum
{
	UART_1_BIT_PARADA = 0,
	UART_2_BIT_PARADA
}_usbs0_bit_uart_t;

// Valores de velocidad de transmisión de bits

typedef enum
{
	BAUDRATE_2400 = 2400,
	BAUDRATE_4800 = 4800,
	BAUDRATE_9600 = 9600,
	BAUDRATE_19200 = 19200,
	BAUDRATE_28800 = 28800,
	BAUDRATE_38400 = 38400,
	BAUDRATE_57600 = 57600,
	BAUDRATE_76800 = 76800,
	BAUDRATE_1152000 = 115200
}_baudrate_uart_t;

// Estructura para la inicialización inicial
typedef struct
{
	_u2x0_bit_uart_t velocidad_doble_normal;
	_mpcm0_bit_uart_t multiprocesador_mode;
	_rxcie0_bit_uart_t interrupcion_rx;
	_txcie0_bit_uart_t interrupcion_tx;
	_rxen0_bit_uart_t habilitar_rx;
	_txen0_bit_uart_t habilitar_tx;
	_ucsz_reg_uart_t longitud_caracter;
	_ninth_bit_9_bit_transmit_uart_t noveno_bit_tx;
	_umsel_reg_uart_t modo_funcionamiento;
	_upm_reg_uart_t paridad;
	_usbs0_bit_uart_t bit_de_parada;
	_baudrate_uart_t baudios;
}_my_uart_0_config_t;

/* Prototipos de funciones */

void UART0_Init (_my_uart_0_config_t *uart_params);
unsigned char UART0_Leer_Byte (void);
void UART0_Escribir_Byte (unsigned char dato);
void UART0_Escribir_Cadena (char *cadena);
#endif /* FM_USART_H_ */