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
#include "LCD16X2.h"

/* Definicion de macros */

/* Declaración de funciones */

void Lcd_Init_Conf (void);

/* Principal */

int main(void)
{
	/* Replace with your application code */
	Lcd_Pines_Init(BITS_4);
	Lcd_Init_Conf();
	Lcd_Cursor_Set(LCD_1_FIL, LCD_1_COL);
	Lcd_Display_String("Hola :)");
	while (1)
	{
	}
}

/* Definición de funciones */

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
	_display_on_off._display_on_off_bits.display_on_off_control_C = 1; // Cursor ON
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
