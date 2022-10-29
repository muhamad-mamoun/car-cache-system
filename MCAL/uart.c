/*
===========================================================================================================
Author       : Mamoun
Module       : UART
File Name    : uart.c
Date Created : Oct 10, 2022
Description  : Source file for the UART driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "uart.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : UART_init
 * [Description]   : Initialize the UART peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_init(const UART_configurationsType* a_ptr2configuration)
{
	uint16 UBRR_value;
	SET_BIT(UCSRA,U2X);                                            /* Enable the double speed mode  */
	SET_BIT(UCSRB,TXEN);                                           /* Enable the UART transmitter   */
	SET_BIT(UCSRB,RXEN);                                           /* Enable the UART receiver      */
	CLEAR_BIT(UCSRC,UMSEL);                                        /* Select the asynchronous mode  */
	UCSRC = (UCSRC&0XCF)|(a_ptr2configuration->parityMode<<4);     /* Set the parity mode           */
	WRITE_BIT(UCSRC,USBS,a_ptr2configuration->stopBitSize);        /* Choose the number of stop bit */
	UCSRC = (UCSRC&0XF9)|(6);                                      /* Select the size of the data   */

	/* Calculate the UBRR value corresponding to the required baudrate */
	UBRR_value = (uint16)((F_CPU/(8U * a_ptr2configuration->baudrateValue))-1);
	UBRRH = (UBRR_value>>8);                                  /* Assign the last 4-bit in the UBRRH */
	UBRRL = UBRR_value;                                       /* Assign the first 8-bit in the UBRRL */
}

/*===========================================================================================================
 * [Function Name] : UART_sendByte
 * [Description]   : Transmit a specific byte to another device.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_sendByte(const uint8 a_data)
{
	/* Wait until the Data Register Empty flag is set to one */
	/* The flag is set when the Tx buffer is empty and ready for transmitting a new byte */
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	/* Write the required data in the UDR register to be transmitted */
	/* This step also clears the UDRE flag */
	UDR = a_data;
}

/*===========================================================================================================
 * [Function Name] : UART_sendString
 * [Description]   : Transmit a specific string to another device.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_sendString(const uint8* a_ptr2data)
{
	/* Loop on the string characters until the NULL character */
	for(uint8 counter=0; *(a_ptr2data+counter) != '\0'; counter++)
	{
		/* Send every character to the UART_sendByte to be transmitted. */
		UART_sendByte(*(a_ptr2data+counter));
	}
}

/*===========================================================================================================
 * [Function Name] : UART_receiveByte
 * [Description]   : Receive a byte from another device.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART_receiveByte(void)
{
	/* Wait until the Receive Complete flag is set to one */
	/* The flag is set to one when there are unread data in the receive buffer */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/* Read the received byte and return it */
	/* This step also clears the RXC flag */
	return UDR;
}

/*===========================================================================================================
 * [Function Name] : UART_receiveString
 * [Description]   : Receive a string from another device.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART_receiveString(uint8* const a_ptr2string)
{
	uint8 counter = 0;

	/* Read the received character and store it in the array */
	*(a_ptr2string+counter) = UART_receiveByte();

	/* Check if the received character is the pre-agreed terminator character */
	while(*(a_ptr2string+counter) != UART_MESSAGE_TERMINATOR)
	{
		counter++;
		/* Read the next character and store it in the array */
		*(a_ptr2string+counter) = UART_receiveByte();
	}

	/* Replace the pre-agreed terminator character with a NULL character */
	*(a_ptr2string+counter) = '\0';
}
