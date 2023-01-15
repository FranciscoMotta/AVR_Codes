/*
 * FM_Push_Boton_Lib.c
 *
 * Created: 14/01/2023 21:09:35
 *  Author: jmott
 */ 

#include <avr/io.h>
#include "FM_Push_Boton_Lib.h"

/* Librería de inicialización del boton a leer */
void Inicializacion_Boton (_boton_pin_t boton, _pull_up_state_t pullup)
{
	if (pullup)
	{
		PORT_BOTON |= (1 << boton);
	}
	else
	{
		PORT_BOTON &= ~(1 << boton);
	}
	DDR_BOTON &= ~(1 << boton); // Boton como salida
}


/* Funcion para leer un boton sin rebote simple */
uint32_t contador_boton_presionado = 0;
uint32_t contador_boton_soltado = 0;
bool estado_boton = false;

bool Leer_Boton_Sin_Rebote_Simple (_boton_pin_t boton)
{
	char mascara_boton = (1 << boton);
	if (PIN_BOTON & mascara_boton)
	{
		contador_boton_presionado++;
		if (contador_boton_presionado > NIVEL_DE_SEGURIDAD)
		{
			if(estado_boton == false)
			{
				estado_boton = true;
				return 1;
			}
			contador_boton_presionado = 0;
		}
	}
	else 
	{
		contador_boton_soltado++;
		if (contador_boton_soltado > NIVEL_DE_SEGURIDAD)
		{
			estado_boton = false;
			contador_boton_soltado = 0;
		}
	}
	return 0;
}