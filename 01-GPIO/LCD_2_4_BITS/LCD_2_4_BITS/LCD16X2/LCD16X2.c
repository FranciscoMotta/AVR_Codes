/*
 * LCD16X2.c
 *
 * Created: 21/01/2023 18:51:13
 *  Author: jmott
 */ 

#include "LCD16X2.h"

void Lcd_Display_String (char *cadena)
{
	uint8_t contador = 0;
	while (cadena[contador] != '\0')
	{
		Lcd_Display_Byte(cadena[contador]);
		contador++;
	}
}

void Lcd_Display_Byte (char dato)
{
	LCD_CHARAC_MODE();
	Lcd_Send_Byte(dato); // Mandamos el caracter a mostrar
}

void Lcd_Cursor_Set (_fila_lcd fila, _columna_lcd columna)
{
	uint8_t base_pos = 0x00;
	if (!fila)
	{
		base_pos = 0x80; // Primera fila
	}
	else
	{
		base_pos = 0xC0; // Segunda filas
	}
	
	base_pos += columna; // Adición de colunmas
	LCD_COMAND_MODE(); // Entramos a modo comando
	Lcd_Send_Byte(base_pos);
	LCD_CHARAC_MODE(); // Salimos a modo caracter
}

void Lcd_Pines_Init (_control_bits_t bits)
{
	LCD_CONTROL_DDR |= MASK_PINES_CONTROL; // Pines de control como salida
	if (bits)
	{
		LCD_DATA_DDR = 0xFF; // Pines de datos como salida
		_function_set._function_set_bits.function_set_control_dl = 1; // Trabajamos a 8 bits
	} 
	else
	{
		LCD_DATA_DDR = 0x0F; // Dejamos los bits menos significativos 
		_function_set._function_set_bits.function_set_control_dl = 0; // Trabajamos a 8 bits
	}
}

void Lcd_Send_Byte (char dato)
{
	if(_function_set._function_set_bits.function_set_control_dl)
	{
		LCD_DATA_PORT = dato;
		LCD_TOGGLE_EN();	
	}
	else 
	{
		uint8_t higher_bits = (dato & 0xF0) >> 4;
		uint8_t lower_bits = (dato & 0x0F);
		LCD_DATA_PORT = higher_bits;
		LCD_TOGGLE_EN();
		LCD_DATA_PORT = lower_bits;
		LCD_TOGGLE_EN();
	}
}