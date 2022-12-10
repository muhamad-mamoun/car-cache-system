/*
===========================================================================================================
Author       : Mamoun
Module       : RFID
File Name    : rfid.c
Date Created : Nov 27, 2022
Description  : Source file for the RFID driver (using UART).
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "rfid.h"
#include "../MCAL/uart.h"

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

UART_configurationsType UART_configurations = {UART_SINGLE_STOP_BIT,UART_PARITY_DISABLED,9600};

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : RFID_init
 * [Description]   : Initialize the RFID module.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_init(void)
{
	UART_init(&UART_configurations);
	RFID_wakeUpDelay();
	UART_configurations.baudrateValue = 128000;
	UART_init(&UART_configurations);
	RFID_powerDownMode_ON();
	RFID_writeData(RFID_TEST_PIN_EN_REG,0X00); /* Disable MX and DTRQ */
	RFID_writeData(RFID_SERIAL_SPEED_REG,0X74); /* Change the default BR to 128 KBR */
}

/*===========================================================================================================
 * [Function Name] : RFID_readData
 * [Description]   : Read the value of a particular register in the RFID module.
 * [Arguments]     : <a_address>      -> the address of the required register.
 * [return]        : The function returns void.
 ==========================================================================================================*/
uint8 RFID_readData(uint8 a_address)
{
	uint8 data;
	UART_sendByte((a_address & 0X3F)|(1<<7));
	data = UART_receiveByte();
	return data;
}

/*===========================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_writeData(uint8 a_address, uint8 a_data)
{
	UART_sendByte((a_address & 0X3F));
	UART_sendByte(a_data);
}

/*===========================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_wakeUpDelay(void)
{
	uint8 data = RFID_readData(0X00); /* Dummy Byte */
}

/*===========================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_sendCommand(uint8 a_command)
{
	RFID_writeData(RFID_COMMAND_REG,(a_command & 0X0F));
}

/*===========================================================================================================
 * [Function Name] : RFID_powerDownMode_ON
 * [Description]   :
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_powerDownMode_ON(void)
{
	RFID_writeData(RFID_COMMAND_REG,(RFID_NO_CMD_CHANGE_COMMAND)|(1<<4));
}

/*===========================================================================================================
 * [Function Name] : RFID_powerDownMode_OFF
 * [Description]   :
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_powerDownMode_OFF(void)
{
	RFID_writeData(RFID_COMMAND_REG,RFID_NO_CMD_CHANGE_COMMAND);
	/* Wait until it becomes 0 */
	while(RFID_readData(RFID_COMMAND_REG)&(1<<4));  /* Take care of infinite loop! */
}

/*===========================================================================================================
 * [Function Name] : RFID_readCardID
 * [Description]   : Read the ID of the scanned card/tag.
 * [Arguments]     : <a_ptr2buffer>      -> Pointer to the buffer array to store the ID.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_readCardID(uint8* a_ptr2buffer)
{
	for(uint8 digit_counter = 0; digit_counter < RFID_CARD_ID_LENGTH; digit_counter++)
	{
		*(a_ptr2buffer + digit_counter) = UART_receiveByte();
	}
}
