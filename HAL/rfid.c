/*
=============================================================================================================
Author       : Mamoun
Module       : RDM6300 RFID
File Name    : rfid.c
Date Created : Dec 21, 2022
Description  : Source file for the RDM6300 RFID Reader driver.
=============================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "rfid.h"
#include "../MCAL/uart.h"
#include <stdlib.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : RFID_init
 * [Description]   : Initialize the RFID module by initializing the UART with specific configurations.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void RFID_init(void)
{
	UART_configurationsType UART_configurations = {UART_SINGLE_STOP_BIT,UART_PARITY_DISABLED,9600};
	UART_init(&UART_configurations);
}

/*===========================================================================================================
 * [Function Name] : RFID_readCard
 * [Description]   : Read the card/tag ID using UART.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the card/tag ID.
 ==========================================================================================================*/
sint32 RFID_readCard(void)
{
	long card_id = 0;
	uint8 bytes_counter = 0;
	uint8 data_buffer[RFID_FRAME_LENGTH] = {'\0'};
	uint8 card_id_buffer[RFID_ID_LENGTH+1] = {'\0'};

	for(bytes_counter = 0; bytes_counter < RFID_FRAME_LENGTH; bytes_counter++)
	{
		*(data_buffer + bytes_counter) = UART_receiveByte();
	}

	for(bytes_counter = 0; bytes_counter < RFID_ID_LENGTH; bytes_counter++)
	{
		*(card_id_buffer + bytes_counter) = *(data_buffer + bytes_counter + 3);
	}

	*(card_id_buffer + bytes_counter) = '\0';

	card_id = strtol(card_id_buffer,NULL,16);

	return card_id;
}
