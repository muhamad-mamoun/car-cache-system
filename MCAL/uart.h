/*
===========================================================================================================
Author       : Mamoun
Module       : UART
File Name    : uart.h
Date Created : Oct 10, 2022
Description  : Header file for the UART driver.
===========================================================================================================
*/


#ifndef UART_H_
#define UART_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define UART_MESSAGE_TERMINATOR     ';'     /* Pre-agreed string terminator character between Tx and Rx */

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	UART_SINGLE_STOP_BIT,UART_DOUBLE_STOP_BIT
}UART_stopBitSizeType;

typedef enum
{
	UART_PARITY_DISABLED,UART_EVEN_PARITY=2,UART_ODD_PARITY=3
}UART_parityModeType;

typedef struct
{
	UART_stopBitSizeType stopBitSize;
	UART_parityModeType parityMode;
	uint32 baudrateValue;
}UART_configurationsType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : UART_init
 * [Description]   : Initialize the UART peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_init(const UART_configurationsType* a_ptr2configuration);

/*===========================================================================================================
 * [Function Name] : UART_sendByte
 * [Description]   : Transmit a specific byte to another device.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_sendByte(const uint8 a_data);

/*===========================================================================================================
 * [Function Name] : UART_sendString
 * [Description]   : Transmit a specific string to another device.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_sendString(const uint8* a_ptr2data);

/*===========================================================================================================
 * [Function Name] : UART_receiveByte
 * [Description]   : Receive a byte from another device.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART_receiveByte(void);

/*===========================================================================================================
 * [Function Name] : UART_receiveString
 * [Description]   : Receive a string from another device.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_receiveString(uint8* const a_ptr2string);

#endif /* UART_H_ */
