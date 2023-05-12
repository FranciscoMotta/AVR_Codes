/*
 * FM_DHT22.c
 *
 * Created: 22/01/2023 15:32:50
 *  Author: jmott
 */ 

#include "FM_DHT22.h"

void DHT22_INIT (void)
{
	DDR_DHT22 |= (1 << DHT22);
	PORT_DHT22 |= (1 << DHT22);
}

bool DHT22_Check_Com (void)
{
		bool check_state = true;
		uint8_t low_response_counter = 0;
		uint8_t high_response_counter = 0;
		uint8_t counter_local = 0;
		// Inicio de comunicación del HOST al sensor
		DDR_DHT22 |= MASK_DHT22; // Ponemos el pin como salida
		PORT_DHT22 &= ~MASK_DHT22;
		_delay_us(HOST_PULL_LOW_INIT);
		PORT_DHT22 |= MASK_DHT22;
		// Respuesta del sensor
		DDR_DHT22 &= ~MASK_DHT22; // Ponemos el pin como entrada
		
		while((PIN_DHT22 & MASK_DHT22))
		{
			counter_local++;
			_delay_us(STEP_GENERAL_US_COUNTE);
			if (counter_local > SENSOR_WAIT_RESPONSE)
			{
				DDR_DHT22 |= MASK_DHT22;
				PORT_DHT22 |= MASK_DHT22;
				return 0;
			}
		}
		
		while (!(PIN_DHT22 & MASK_DHT22))
		{
			low_response_counter++;
			_delay_us(STEP_GENERAL_US_COUNTE);
			if (low_response_counter > SENSOR_PULL_LOW_RESP)
			{
				check_state = false;
			}
		}
		
		low_response_counter = 0;
		
		while(PIN_DHT22 & MASK_DHT22)
		{
			high_response_counter++;
			_delay_us(STEP_GENERAL_US_COUNTE);
			if (high_response_counter > SENSOR_PULL_UP_RESP)
			{
				check_state = false;
			}
		}
		
		high_response_counter = 0;
		return check_state;
}

bool DHT22_Read_Temp_Hum (float *temperatura, float *humedad, _format_temperatura_t formato)
{
	uint8_t bytes_buffer[TRAMA_LENGHT_DHT22_BYTE] = {0};
	uint8_t byte_counter = 0;
	uint8_t bit_counter = 0;
	uint8_t local_counter = 0;
	uint8_t byte_to_create = 0;
	if (DHT22_Check_Com())
	{
		for (byte_counter = 0 ; byte_counter < TRAMA_LENGHT_DHT22_BYTE ; byte_counter++)
		{
			byte_to_create = 0;
			for (bit_counter = 0 ; bit_counter < BITS_PER_BYTE ; bit_counter++)
			{
				while(!(PIN_DHT22 & MASK_DHT22));
				_delay_us(HIGH_TIME_SIGNAL / 2);
				if (PIN_DHT22 & MASK_DHT22)
				{
					byte_to_create |= (1 << (7 - bit_counter));
				}
				while((PIN_DHT22 & MASK_DHT22));
			}
			bytes_buffer[byte_counter] = byte_to_create;
		}
		
		uint8_t chech_sum = (uint8_t)(bytes_buffer[0] + bytes_buffer[1] + bytes_buffer[2] + bytes_buffer[3]);
		
		uint16_t tempe_prev = 0;
		uint16_t humde_prev = 0;
		
		if (chech_sum == bytes_buffer[4])
		{
			printf("check ok!\n\r");
			humde_prev = (bytes_buffer[0] << 8) | bytes_buffer[1];
			tempe_prev = (bytes_buffer[2] << 8) | bytes_buffer[3];
			
			/* Verificamos si es negativo */
			
			float tempe_neg_pos = 0.0;
			
			if (tempe_prev > MASK_NEGATIVA)
			{
				tempe_neg_pos = -1.0 * ((NUMERIC_NEG_MASK & tempe_prev) / 10.0);
			}
			else
			{
				tempe_neg_pos = tempe_prev / 10.0;
			}
			switch(formato)
			{
				case GRADOS_CELCIUS:
					*temperatura = tempe_neg_pos;
				break;
				case GRADOS_FAHRENHEIT:
					*temperatura = (tempe_neg_pos * (9.0 / 5.0)) + 32.0;
				break;
				case GRADOS_KELVIN:
					*temperatura = tempe_neg_pos + 273.15;
				break;
			}
			
			*humedad = (float)(humde_prev / 10.0);
		}
		else
		{
			return false;
		}
		
		return true;
	}
	else
	{
		return false;	
	}
}