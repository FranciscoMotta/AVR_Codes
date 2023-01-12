/*
 * LCD_FIRST_SIMPLE.c
 * Trabajaremos el control del LCD a 8bits
 * Created: 11/01/2023 21:45:34
 * Author : jmott
 */ 

#define F_CPU 16000000UL

/* Inclusión de archivos */

#include <avr/io.h>
#include <util/delay.h>
/* Definicion de macros */

union{
		uint8_t entry_mode_set;
		struct
		{
			char entry_mode_set_id : 1;
			char entry_mode_set_sh : 1;
			char entry_mode_set_db2 : 1;
			char entry_mode_set_db3 : 1;
			char entry_mode_set_db4 : 1;
			char entry_mode_set_db5 : 1;
			char entry_mode_set_db6 : 1;
			char entry_mode_set_db7 : 1;
		} _entry_mode_bits;
	}_entry_mode;

union{
		uint8_t display_on_off_control;
		struct{
			char display_on_off_control_B : 1; // Blink On-Off
			char display_on_off_control_C : 1; // Cursor On-Off
			char display_on_off_control_D : 1; // Display On-Off
			char display_on_off_control_db3 : 1; // No importa
			char display_on_off_control_db4 : 1;
			char display_on_off_control_db5 : 1;
			char display_on_off_control_db6 : 1;
			char display_on_off_control_db7 : 1; 
			}_display_on_off_bits;
	}_display_on_off;

union{
		uint8_t function_set_control;
		struct{
			char function_set_control_db0 : 1; // No importa
			char function_set_control_db1 : 1; // No importa
			char function_set_control_f : 1; // Matriz de puntos
			char function_set_control_n : 1; // Display line number control
			char function_set_control_dl : 1; // inferface control
			char function_set_control_db5 : 1; // No importa
			char function_set_control_db6 : 1;
			char function_set_control_db7 : 1; 
			}_function_set_bits;
	}_function_set;
	
// Macros de pines de control
#define LCD_CONTROL_DDR		DDRD
#define LCD_CONTROL_PORT	PORTD	
#define LCD_PIN_RS			1
#define LCD_PIN_RW			2
#define LCD_PIN_EN          3
#define MASK_PINES_CONTROL (1 << LCD_PIN_EN) | (1 << LCD_PIN_RS) | (1 << LCD_PIN_RW)
#define LCD_TOGGLE_EN()   LCD_CONTROL_PORT |= (1 << LCD_PIN_EN); _delay_ms(1) ; LCD_CONTROL_PORT &= ~(1 << LCD_PIN_EN); // Secuencia de enable 
#define LCD_COMAND_MODE() LCD_CONTROL_PORT &= ~(1 << LCD_PIN_RS); // Modo comando
#define LCD_CHARAC_MODE() LCD_CONTROL_PORT |= (1 << LCD_PIN_RS); // Modo caracter

// Macros de pines de datos

#define  LCD_DATA_DDR		DDRB
#define  LCD_DATA_PORT		PORTB

// Macros de datos de control

#define COMAND_CLEAR_LCD	0x01
#define COMAND_RETURN_HOME_LCD	0x02
#define LCD_UPPER_ROW		0
#define LCD_LOWER_ROW		1

// Macros de GPIO Secundarios

#define LED_DDR		DDRD
#define LED_PORT	PORTD
#define LED		4
#define LED_AS_OUTPUT() LED_DDR |= (1 << LED); 

typedef enum
{
	LCD_1_COL = 0,
	LCD_2_COL,
	LCD_3_COL,
	LCD_4_COL,
	LCD_5_COL,
	LCD_6_COL,
	LCD_7_COL,
	LCD_8_COL,
	LCD_9_COL,
	LCD_10_COL,
	LCD_11_COL,
	LCD_12_COL,
	LCD_13_COL,
	LCD_14_COL,
	LCD_15_COL,
	LCD_16_COL
}_columna_lcd;

typedef enum
{
	LCD_1_FIL = 0,
	LCD_2_FIL	 
}_fila_lcd;

/* Declaración de funciones */

void Lcd_Pines_Init (void);
void Lcd_Send_Byte (char dato);
void Lcd_Init_Conf (void);
void Lcd_Cursor_Set (_fila_lcd fila, _columna_lcd columna);
void Lcd_Display_Byte (char dato);
void Lcd_Display_String (char *cadena);
/* Principal */

int main(void)
{
	/* Manejo de pines secundarios */
	LED_AS_OUTPUT();
	
	/* Manejo del LCD */
	Lcd_Pines_Init(); // Iniciamos los pines del LCD
	Lcd_Init_Conf(); // Iniciamos el LCD
	
	/* Mandaremos los caracteres */
	Lcd_Cursor_Set(LCD_1_FIL, LCD_1_COL);
	Lcd_Display_Byte('b');
	Lcd_Cursor_Set(LCD_2_FIL, LCD_1_COL);
	Lcd_Display_String("Hola :)");
	
	while (1)
	{
		LED_PORT ^= (1 << LED);
		_delay_ms(1000);
	}
}

/* Definición de funciones */

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

void Lcd_Init_Conf (void)
{
	/* Iniciamos la configuración del LCD */
	LCD_CONTROL_PORT &= ~(1 << LCD_PIN_RW);
	LCD_COMAND_MODE();
	Lcd_Send_Byte(COMAND_CLEAR_LCD);
	Lcd_Send_Byte(COMAND_RETURN_HOME_LCD);
	_entry_mode._entry_mode_bits.entry_mode_set_db2 = 1;
	_entry_mode._entry_mode_bits.entry_mode_set_id = 0;
	_entry_mode._entry_mode_bits.entry_mode_set_sh = 1;
	Lcd_Send_Byte(_entry_mode.entry_mode_set);
	_display_on_off._display_on_off_bits.display_on_off_control_db3 = 1;
	_display_on_off._display_on_off_bits.display_on_off_control_D = 1; // Display ON
	_display_on_off._display_on_off_bits.display_on_off_control_C = 1; // Cursor ON
	_display_on_off._display_on_off_bits.display_on_off_control_B = 0; // Blink ON
	Lcd_Send_Byte(_display_on_off.display_on_off_control);
	_function_set._function_set_bits.function_set_control_db5 = 1;
	_function_set._function_set_bits.function_set_control_dl = 1; // Trabajamos a 8 bits
	_function_set._function_set_bits.function_set_control_n = 1; // Matriz de 5x11
	_function_set._function_set_bits.function_set_control_f = 1; // Trabajamos a 2 lineas
	Lcd_Send_Byte(_function_set.function_set_control);
}

void Lcd_Pines_Init (void)
{
	LCD_CONTROL_DDR |= MASK_PINES_CONTROL; // Pines de control como salida
	LCD_DATA_DDR |= 0xFF; // Pines de datos como salida
} 

void Lcd_Send_Byte (char dato)
{
	LCD_DATA_PORT = dato;
	LCD_TOGGLE_EN();
}