/*
 * LCD_2_4_BITS.c
 *
 * Created: 21/01/2023 18:49:04
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "LCD16X2.h"

/* Definicion de macros */

#define DDR_PULSADORES	DDRC
#define PIN_PULSADORES	PINC
#define PORT_PULSADORES	PORTC
#define PULSADOR_1		0
#define PULSADOR_2		1
#define PULSADOR_3		2
#define PULSADOR_4		3
#define MASK_PULSA		(1 << PULSADOR_1) | (1 << PULSADOR_2) | (1 << PULSADOR_3) | (1 << PULSADOR_4)
#define MASK_PULS1		(1 << PULSADOR_1)
#define MASK_PULS2		(1 << PULSADOR_2)
#define MASK_PULS3		(1 << PULSADOR_3)
#define MASK_PULS4		(1 << PULSADOR_4)
#define PIN_PULSA1		(PIN_PULSADORES & MASK_PULS1)
#define PIN_PULSA2		(PIN_PULSADORES & MASK_PULS2)
#define PIN_PULSA3		(PIN_PULSADORES & MASK_PULS3)
#define PIN_PULSA4		(PIN_PULSADORES & MASK_PULS4)

/* State pulsadores */

bool state_p1 = false;
bool state_p2 = false;
bool state_p3 = false;
bool state_p4 = false;

/* Declaración de funciones */

void Lcd_Init_Conf (void);
void check_pulsa_ok (char *mask);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	DDR_PULSADORES &= ~MASK_PULSA; // Pulsadores como entradas
	PORT_PULSADORES |= MASK_PULSA; // Pull-ups activados
	Lcd_Pines_Init(BITS_4);
	Lcd_Init_Conf();
	Lcd_Cursor_Set(LCD_1_FIL, LCD_1_COL);
	Lcd_Display_String("FM - LCD 4 bits");
	Lcd_Cursor_Set(LCD_2_FIL, LCD_1_COL);
	Lcd_Display_String("B1:0B2:0B3:0B4:0");
	while (1)
	{
		if (!PIN_PULSA1)
		{
			while(!PIN_PULSA1);
			state_p1 = !state_p1;
			if (state_p1)
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_4_COL);
			   Lcd_Display_Byte('I');
			} 
			else
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_4_COL);
			   Lcd_Display_Byte('0');
			}
		}
		
		if (!PIN_PULSA2)
		{
			while(!PIN_PULSA2);
			state_p2 = !state_p2;
			if (state_p2)
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_8_COL);
			   Lcd_Display_Byte('I');
			} 
			else
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_8_COL);
			   Lcd_Display_Byte('0');
			}
		}
		
		if (!PIN_PULSA3)
		{
			while(!PIN_PULSA3);
			state_p3 = !state_p3;
			if (state_p3)
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_12_COL);
			   Lcd_Display_Byte('I');
			} 
			else
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_12_COL);
			   Lcd_Display_Byte('0');
			}
		}
		
		if (!PIN_PULSA4)
		{
			while(!PIN_PULSA4);
			state_p4 = !state_p4;
			if (state_p4)
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_16_COL);
			   Lcd_Display_Byte('I');
			} 
			else
			{
			   Lcd_Cursor_Set(LCD_2_FIL, LCD_16_COL);
			   Lcd_Display_Byte('0');
			}
		}
	}
}

/* Definición de funciones */

void check_pulsa_ok (char *mask)
{
	if (!mask)
	{
		while(!mask);
	}
}

void Lcd_Init_Conf (void)
{
	/* Iniciamos la configuración del LCD */
	LCD_CONTROL_PORT &= ~(1 << LCD_PIN_RW);
	LCD_COMAND_MODE();
	
	_entry_mode._entry_mode_bits.entry_mode_set_db2 = 1;
	_entry_mode._entry_mode_bits.entry_mode_set_id = 0;
	_entry_mode._entry_mode_bits.entry_mode_set_sh = 1;
	
	_display_on_off._display_on_off_bits.display_on_off_control_db3 = 1;
	_display_on_off._display_on_off_bits.display_on_off_control_D = 1; // Display ON
	_display_on_off._display_on_off_bits.display_on_off_control_C = 0; // Cursor OFF
	_display_on_off._display_on_off_bits.display_on_off_control_B = 0; // Blink ON
	
	_function_set._function_set_bits.function_set_control_db5 = 1;
	_function_set._function_set_bits.function_set_control_n = 1; // Matriz de 5x11
	_function_set._function_set_bits.function_set_control_f = 1; // Trabajamos a 2 lineas
	
	Lcd_Send_Byte(COMAND_CLEAR_LCD);
	Lcd_Send_Byte(COMAND_RETURN_HOME_LCD);
	Lcd_Send_Byte(_entry_mode.entry_mode_set);
	Lcd_Send_Byte(_display_on_off.display_on_off_control);
	Lcd_Send_Byte(_function_set.function_set_control);
}
