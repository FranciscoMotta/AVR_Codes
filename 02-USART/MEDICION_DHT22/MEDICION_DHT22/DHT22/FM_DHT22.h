/*
 * FM_DTH22.h
 *
 * Created: 22/01/2023 15:32:00
 *  Author: jmott
 */ 


#ifndef FM_DHT22_H_
#define FM_DHT22_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h> 

/************************************************************************/
/*                              DHT-22                                  */
/************************************************************************/

#define PORT_DHT22		PORTC	
#define DDR_DHT22		DDRC
#define PIN_DHT22		PINC
#define DHT22			0
#define MASK_DHT22		(1 << DHT22)
/************************************************************************/
/*                          TIEMPOS DHT22                               */
/************************************************************************/

#define HOST_PULL_LOW_INIT		18000
#define HOST_PULL_UP_INIT		30

#define SENSOR_PULL_LOW_RESP	80
#define SENSOR_PULL_UP_RESP		80	

#define SENSOR_WAIT_RESPONSE	40
#define SENSOR_LONG_WAIT		100

#define STEP_GENERAL_US_COUNTE	1

#define TRAMA_LENGHT_DHT22_BYTE	5
#define	BITS_PER_BYTE			8

#define LOW_TIME_SIGNAL			27
#define HIGH_TIME_SIGNAL		70

#define MASK_NEGATIVA			0x8000
#define NUMERIC_NEG_MASK		~(MASK_NEGATIVA)

typedef enum
{
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
}_pin_puerto_DHT22_t;


typedef enum
{
	GRADOS_CELCIUS = 0,
	GRADOS_FAHRENHEIT,
	GRADOS_KELVIN
}_format_temperatura_t;

void DHT22_INIT (void);
bool DHT22_Check_Com (void);
bool DHT22_Read_Temp_Hum (float *temperatura, float *humedad, _format_temperatura_t formato);

#endif /* FM_DHT22_H_ */