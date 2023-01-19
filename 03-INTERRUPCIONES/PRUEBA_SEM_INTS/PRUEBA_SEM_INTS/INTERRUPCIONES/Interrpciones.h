/*
 * Interrpciones.h
 *
 * Created: 18/01/2023 21:15:45
 *  Author: jmott
 */ 


#ifndef INTERRPCIONES_H_
#define INTERRPCIONES_H_

// Inclusiones

#include <avr/interrupt.h>

// Macros

#define INTERRUPTS_DDR_03  DDRD
#define INTERRUPTS_PORT_03 PORTD

#define INTERRUPTS_DDR_47  DDRE
#define INTERRUPTS_PORT_47 PORTE

// Enumeraciones y estructuras

typedef enum
{
	INT0_ACTIV_NIVEL_BAJO = 0b00,
	INT0_ACTIV_CUALQ_FLANCO,
	INT0_ACTIV_FLANCO_BAJ,
	INT0_ACTIV_FLANCO_SUB			
}_control_bits_int0_interrupciones_t;

typedef enum
{
	INT1_ACTIV_NIVEL_BAJO = 0b00,
	INT1_ACTIV_CUALQ_FLANCO,
	INT1_ACTIV_FLANCO_BAJ,
	INT1_ACTIV_FLANCO_SUB
}_control_bits_int1_interrupciones_t;

typedef enum
{
	INT2_ACTIV_NIVEL_BAJO = 0b00,
	INT2_ACTIV_CUALQ_FLANCO,
	INT2_ACTIV_FLANCO_BAJ,
	INT2_ACTIV_FLANCO_SUB
}_control_bits_int2_interrupciones_t;

typedef enum
{
	INT3_ACTIV_NIVEL_BAJO = 0b00,
	INT3_ACTIV_CUALQ_FLANCO,
	INT3_ACTIV_FLANCO_BAJ,
	INT3_ACTIV_FLANCO_SUB
}_control_bits_int3_interrupciones_t;

typedef enum
{
	INT4_ACTIV_NIVEL_BAJO = 0b00,
	INT4_ACTIV_CUALQ_FLANCO,
	INT4_ACTIV_FLANCO_BAJ,
	INT4_ACTIV_FLANCO_SUB
}_control_bits_int4_interrupciones_t;

typedef enum
{
	INT5_ACTIV_NIVEL_BAJO = 0b00,
	INT5_ACTIV_CUALQ_FLANCO,
	INT5_ACTIV_FLANCO_BAJ,
	INT5_ACTIV_FLANCO_SUB
}_control_bits_int5_interrupciones_t;

typedef enum
{
	INT6_ACTIV_NIVEL_BAJO = 0b00,
	INT6_ACTIV_CUALQ_FLANCO,
	INT6_ACTIV_FLANCO_BAJ,
	INT6_ACTIV_FLANCO_SUB
}_control_bits_int6_interrupciones_t;

typedef enum
{
	INT7_ACTIV_NIVEL_BAJO = 0b00,
	INT7_ACTIV_CUALQ_FLANCO,
	INT7_ACTIV_FLANCO_BAJ,
	INT7_ACTIV_FLANCO_SUB
}_control_bits_int7_interrupciones_t;

typedef enum{
	INT0_DISABLE = 0,
	INT0_ENABLE
}_enable_int0_interrupciones_t;

typedef enum{
	INT1_DISABLE = 0,
	INT1_ENABLE
}_enable_int1_interrupciones_t;

typedef enum{
	INT2_DISABLE = 0,
	INT2_ENABLE
}_enable_int2_interrupciones_t;

typedef enum{
	INT3_DISABLE = 0,
	INT3_ENABLE
}_enable_int3_interrupciones_t;

typedef enum{
	INT4_DISABLE = 0,
	INT4_ENABLE
}_enable_int4_interrupciones_t;

typedef enum{
	INT5_DISABLE = 0,
	INT5_ENABLE
}_enable_int5_interrupciones_t;

typedef enum{
	INT6_DISABLE = 0,
	INT6_ENABLE
}_enable_int6_interrupciones_t;

typedef enum{
	INT7_DISABLE = 0,
	INT7_ENABLE
}_enable_int7_interrupciones_t;

typedef enum{
	INTS_CLEAR = 0x00,
	INTS_SETS = 0xFF
}_interrupts_flags_interrupciones_t;

typedef	enum{
	INTS_PULL_UP_DISABLE = 0,
	INTS_PULL_UP_ENABLE
}_interrupts_pullup_interrupciones_t;

typedef struct{
	
	_control_bits_int0_interrupciones_t int0_control;
	_control_bits_int1_interrupciones_t int1_control;
	_control_bits_int2_interrupciones_t int2_control;
	_control_bits_int3_interrupciones_t int3_control;
	_control_bits_int4_interrupciones_t int4_control;
	_control_bits_int5_interrupciones_t int5_control;
	_control_bits_int6_interrupciones_t int6_control;
	_control_bits_int7_interrupciones_t int7_control;
	
	_enable_int0_interrupciones_t int0_enable;
	_enable_int1_interrupciones_t int1_enable;
	_enable_int2_interrupciones_t int2_enable;
	_enable_int3_interrupciones_t int3_enable;
	_enable_int4_interrupciones_t int4_enable;
	_enable_int5_interrupciones_t int5_enable;
	_enable_int6_interrupciones_t int6_enable;
	_enable_int7_interrupciones_t int7_enable;
	
	_interrupts_flags_interrupciones_t banderas_ints;

	_interrupts_pullup_interrupciones_t pull_up;	
	
}_interrupciones_config_t;

void Interrupciones_Init (_interrupciones_config_t *ints_params);

#endif /* INTERRPCIONES_H_ */