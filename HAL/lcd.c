/*
===========================================================================================================
Author       : Mamoun
Module       : LCD
File Name    : lcd.c
Date Created : Oct 8, 2022
Description  : Source file for the LCD driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "lcd.h"
#include "../MCAL/gpio.h"
#include "../OTHERS/common_macros.h"
#include <util/delay.h>
#include <stdio.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : LCD_init
 * [Description]   : Initialize the LCD by :
 *                   1- Setup the LCD pins direction.
 *                   2- Setup the LCD data mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_EN_PORT_ID,LCD_EN_PIN_ID,OUTPUT_PIN);

#if (LCD_DATA_BITS_MODE == 8)

	GPIO_setupPortDirection(LCD_DATA_PORT_ID,OUTPUT_PORT);

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 4)

	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DATA4_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DATA5_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DATA6_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DATA7_PIN_ID,OUTPUT_PIN);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/*===========================================================================================================
 * [Function Name] : LCD_sendCommand
 * [Description]   : Send a specific command to the LCD.
 * [Arguments]     : <a_command>      -> Indicates to the required command.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_sendCommand(uint8 a_command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOW_PIN);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,HIGH_PIN);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 8)

	GPIO_writePort(LCD_DATA_PORT_ID,a_command);

#elif (LCD_DATA_BITS_MODE == 4)

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA4_PIN_ID,GET_BIT(a_command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA5_PIN_ID,GET_BIT(a_command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA6_PIN_ID,GET_BIT(a_command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA7_PIN_ID,GET_BIT(a_command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOW_PIN);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,HIGH_PIN);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA4_PIN_ID,GET_BIT(a_command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA5_PIN_ID,GET_BIT(a_command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA6_PIN_ID,GET_BIT(a_command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA7_PIN_ID,GET_BIT(a_command,3));

#endif

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOW_PIN);
	_delay_ms(1);
}

/*===========================================================================================================
 * [Function Name] : LCD_displayCharacter
 * [Description]   : Display a specific character on the LCD at the cursor position.
 * [Arguments]     : <a_character>      -> Indicates to the required character.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayCharacter(uint8 a_character)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,HIGH_PIN);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,HIGH_PIN);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 8)

	GPIO_writePort(LCD_DATA_PORT_ID,a_character);

#elif (LCD_DATA_BITS_MODE == 4)

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA4_PIN_ID,GET_BIT(a_character,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA5_PIN_ID,GET_BIT(a_character,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA6_PIN_ID,GET_BIT(a_character,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA7_PIN_ID,GET_BIT(a_character,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOW_PIN);
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,HIGH_PIN);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA4_PIN_ID,GET_BIT(a_character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA5_PIN_ID,GET_BIT(a_character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA6_PIN_ID,GET_BIT(a_character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DATA7_PIN_ID,GET_BIT(a_character,3));

#endif

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT_ID,LCD_EN_PIN_ID,LOW_PIN);
	_delay_ms(1);
}

/*===========================================================================================================
 * [Function Name] : LCD_displayString
 * [Description]   : Display a specific string on the LCD at the cursor position.
 * [Arguments]     : <a_character_Ptr>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayString(const uint8* const a_character_Ptr)
{
	uint8 counter = 0;
	while( *(a_character_Ptr+counter) != '\0' )
	{
		LCD_displayCharacter(*(a_character_Ptr+counter));
		counter++;
	}
}

/*===========================================================================================================
 * [Function Name] : LCD_moveCursor
 * [Description]   : Move the cursor to a specific position on the LCD.
 * [Arguments]     : <a_row>         -> Indicates to the row number of the required position.
 *                   <a_column>      -> Indicates to the column number of the required position.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_moveCursor(uint8 a_row, uint8 a_column)
{
	uint8 DDRAM_address = 0X00;

	switch (a_row)
	{
	case 0 :
		DDRAM_address = a_column + 0X00;
		break;
	case 1 :
		DDRAM_address = a_column + 0X40;
		break;
	case 2 :
		DDRAM_address = a_column + 0X10;
		break;
	case 3 :
		DDRAM_address = a_column + 0X50;
		break;
	}

	LCD_sendCommand((DDRAM_address&0X7F) | (0X80));
}

/*===========================================================================================================
 * [Function Name] : LCD_displayStringRowColumn
 * [Description]   : Display a specific string in a specific position on the LCD.
 * [Arguments]     : <a_row>         -> Indicates to the row number of the required position.
 *                   <a_column>      -> Indicates to the column number of the required position.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayStringRowColumn(const uint8* const a_character_Ptr, uint8 a_row, uint8 a_column)
{
	LCD_moveCursor(a_row,a_column);
	LCD_displayString(a_character_Ptr);
}

/*===========================================================================================================
 * [Function Name] : LCD_displayInteger
 * [Description]   : Convert a specific integer value to string.
 *                   Then, display this string on the LCD.
 * [Arguments]     : <a_data>         -> Indicates to the integer value.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayInteger(int a_data)
{
	char buffer[16];
	itoa(a_data,buffer,10);
	LCD_displayString(buffer);
}

/*===========================================================================================================
 * [Function Name] : LCD_clearScrean
 * [Description]   : Clear the screen of the LCD.
 *                   Also this function deletes the DDRAM of the LCD.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_clearScrean(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}
