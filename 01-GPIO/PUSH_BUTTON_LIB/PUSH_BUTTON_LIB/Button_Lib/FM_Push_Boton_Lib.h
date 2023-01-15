/*
 * FM_Push_Boton_Lib.h
 *
 * Created: 14/01/2023 21:09:21
 *  Author: jmott
 */ 


#ifndef FM_PUSH_BOTON_LIB_H_
#define FM_PUSH_BOTON_LIB_H_

#include <stdbool.h>

/************************************************************************/
/*          FUNCION DE LECTURA DE UN BOTON SIN REBOTE                   */
/************************************************************************/

// Macros del boton

#define DDR_BOTON DDRB
#define PORT_BOTON PORTB
#define PIN_BOTON PINB

// Macros del antirrebote

#define NIVEL_DE_SEGURIDAD	500

// Enumeraciones

typedef enum
{
	BOTON_1 = 0x00,
	BOTON_2,
	BOTON_3,
	BOTON_4,
	BOTON_5,
	BOTON_6,
	BOTON_7,
	BOTON_8
}_boton_pin_t;

typedef enum
{
	PULL_UP_DISABLE = 0,
	PULL_UP_ENABLE
}_pull_up_state_t;
/* Declaración de funciones */

/* Funcion para inicializar el boton */
void Inicializacion_Boton (_boton_pin_t boton, _pull_up_state_t pullup);

/* Funcion para leer un boton sin rebote simple */
bool Leer_Boton_Sin_Rebote_Simple (_boton_pin_t boton);

#endif /* FM_PUSH_BOTON_LIB_H_ */