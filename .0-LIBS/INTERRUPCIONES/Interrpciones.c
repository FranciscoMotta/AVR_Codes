/*
 * Interrpciones.c
 *
 * Created: 18/01/2023 21:16:01
 *  Author: jmott
 */ 

#include <Interrpciones.h>

void Interrupciones_Init (_interrupciones_config_t *ints_params)
{
	// Habilitaciones del control de las interrupciones
	
	EICRA |= ((ints_params->int0_control & 0x03) << ISC00);
	EICRA |= ((ints_params->int1_control & 0x03) << ISC10);
	EICRA |= ((ints_params->int2_control & 0x03) << ISC20);
	EICRA |= ((ints_params->int3_control & 0x03) << ISC30);
	
	EICRB |= ((ints_params->int4_control & 0x03) << ISC40);
	EICRB |= ((ints_params->int5_control & 0x03) << ISC50);
	EICRB |= ((ints_params->int6_control & 0x03) << ISC60);
	EICRB |= ((ints_params->int7_control & 0x03) << ISC70);
		
	// Habilitacion de las interrupciones

	EIMSK |= ((ints_params->int0_enable & 0x01) << INT0) | ((ints_params->int1_enable & 0x01) << INT1);	
	EIMSK |= ((ints_params->int2_enable & 0x01) << INT2) | ((ints_params->int3_enable & 0x01) << INT3);	
	EIMSK |= ((ints_params->int4_enable & 0x01) << INT4) | ((ints_params->int5_enable & 0x01) << INT5);	
	EIMSK |= ((ints_params->int6_enable & 0x01) << INT6) | ((ints_params->int7_enable & 0x01) << INT7);	
	/*
	Si se habilita las interrupciones, se colocan los pines habilitados como entradas
	*/
	
	INTERRUPTS_DDR_03 &= ~(EIMSK & 0x0F); 
	INTERRUPTS_DDR_47 &= ~(EIMSK & 0xF0);
	
	// Limpieza de las banderas
	
	EIFR = ints_params->banderas_ints;
	
	// Habilitamos los pullups
	if (ints_params->pull_up)
	{
		INTERRUPTS_PORT_03 |= (EIMSK & 0x0F);
		INTERRUPTS_PORT_47 |= (EIMSK & 0xF0);
	} 
	else
	{
		INTERRUPTS_PORT_03 &= ~(EIMSK & 0x0F);
		INTERRUPTS_PORT_47 &= ~(EIMSK & 0xF0);
	}
	
	// Activamos las interrupciones
	sei();
}