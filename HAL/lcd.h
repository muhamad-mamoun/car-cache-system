/*
===========================================================================================================
Author       : Mamoun
Module       : LCD
File Name    : lcd.h
Date Created : Oct 8, 2022
Description  : Header file for the LCD driver.
===========================================================================================================
*/


#ifndef LCD_H_
#define LCD_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define LCD_DATA_BITS_MODE                    (8u)

/* The LCD has only two modes: 8-bits and 4-bits. */
#if ((LCD_DATA_BITS_MODE != 8) && (LCD_DATA_BITS_MODE != 4))
#error "Invalid LCD data bit mode, The LCD has only two modes: 8-bits and 4-bits."
#endif

#define LCD_RS_PORT_ID                        (PORTD_ID)
#define LCD_RS_PIN_ID                         (PIN0_ID)

#define LCD_EN_PORT_ID                        (PORTD_ID)
#define LCD_EN_PIN_ID                         (PIN2_ID)

#define LCD_DATA_PORT_ID                      (PORTC_ID)

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DATA4_PIN_ID                      (PIN3_ID)
#define LCD_DATA5_PIN_ID                      (PIN4_ID)
#define LCD_DATA6_PIN_ID                      (PIN5_ID)
#define LCD_DATA7_PIN_ID                      (PIN6_ID)

#endif

/* LCD common commands */
#define LCD_CLEAR_SCREEN                      (0x01)
#define LCD_GO_TO_HOME                        (0x02)
#define LCD_TWO_LINES_EIGHT_BITS_MODE         (0x38)
#define LCD_TWO_LINES_FOUR_BITS_MODE          (0x28)
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1    (0x33)
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2    (0x32)
#define LCD_CURSOR_OFF                        (0x0C)
#define LCD_CURSOR_ON                         (0x0E)
#define LCD_SET_CURSOR_LOCATION               (0x80)

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : LCD_init
 * [Description]   : Initialize the LCD by :
 *                   1- Setup the LCD pins direction.
 *                   2- Setup the LCD data mode.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_init(void);


/*===========================================================================================================
 * [Function Name] : LCD_sendCommand
 * [Description]   : Send a specific command to the LCD.
 * [Arguments]     : <a_command>      -> Indicates to the required command.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_sendCommand(uint8 a_command);


/*===========================================================================================================
 * [Function Name] : LCD_displayCharacter
 * [Description]   : Display a specific character on the LCD at the cursor position.
 * [Arguments]     : <a_character>      -> Indicates to the required character.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayCharacter(uint8 a_character);


/*===========================================================================================================
 * [Function Name] : LCD_displayString
 * [Description]   : Display a specific string on the LCD at the cursor position.
 * [Arguments]     : <a_character_Ptr>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayString(const uint8* const a_character_Ptr);


/*===========================================================================================================
 * [Function Name] : LCD_moveCursor
 * [Description]   : Move the cursor to a specific position on the LCD.
 * [Arguments]     : <a_row>         -> Indicates to the row number of the required position.
 *                   <a_column>      -> Indicates to the column number of the required position.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_moveCursor(uint8 a_row, uint8 a_column);


/*===========================================================================================================
 * [Function Name] : LCD_displayStringRowColumn
 * [Description]   : Display a specific string in a specific position on the LCD.
 * [Arguments]     : <a_row>         -> Indicates to the row number of the required position.
 *                   <a_column>      -> Indicates to the column number of the required position.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayStringRowColumn(const uint8* const a_character_Ptr, uint8 a_row, uint8 a_column);


/*===========================================================================================================
 * [Function Name] : LCD_displayInteger
 * [Description]   : Convert a specific integer value to string.
 *                   Then, display this string on the LCD.
 * [Arguments]     : <a_data>         -> Indicates to the integer value.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_displayInteger(uint32 a_data);


/*===========================================================================================================
 * [Function Name] : LCD_clearScrean
 * [Description]   : Clear the screen of the LCD.
 *                   Also this function deletes the DDRAM of the LCD.
 *                   Then, display this string on the LCD.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LCD_clearScrean(void);

#endif /* LCD_H_ */
