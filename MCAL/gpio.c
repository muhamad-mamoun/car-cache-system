/*
===========================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio.c
Date Created : Oct 6, 2022
Description  : Source file for the AVR GPIO peripheral driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "gpio.h"
#include "../OTHERS/std_types.h"
#include "../OTHERS/common_macros.h"
#include <avr/io.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : GPIO_setupPinDirection
 * [Description]   : Setup the direction of a certain pin (input or output).
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 *                   <a_direction>  -> Indicates to the required direction.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_setupPinDirection(uint8 a_portID, uint8 a_pinID, GPIO_pinDirectionType a_direction)
{
	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		volatile uint8* const registerAddress = (&DDRA)-(a_portID*GPIO_REG_GAP);
		WRITE_BIT(*registerAddress,a_pinID,a_direction);
	}
	else
	{
		/* Do Nothing */
	}
}

/*===========================================================================================================
 * [Function Name] : GPIO_setupPortDirection
 * [Description]   : Setup the direction of a certain port (input or output).
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 *                   <a_direction>  -> Indicates to the required direction.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_setupPortDirection(uint8 a_portID, GPIO_portDirectionType a_direction)
{
	if(a_portID < NUM_OF_PORTS)
	{
		volatile uint8* const registerAddress = (&DDRA)-(a_portID*GPIO_REG_GAP);
		*registerAddress = a_direction;
	}
	else
	{
		/* Do Nothing */
	}
}

/*===========================================================================================================
 * [Function Name] : GPIO_writePin
 * [Description]   : Write a certain value (high or low) in a certain pin.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 *                   <a_value>      -> Indicates to the required value (high or low).
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_writePin(uint8 a_portID, uint8 a_pinID, GPIO_pinStateType a_value)
{
	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		volatile uint8* const registerAddress = (&PORTA)-(a_portID*GPIO_REG_GAP);
		WRITE_BIT(*registerAddress,a_pinID,a_value);
	}
	else
	{
		/* Do Nothing */
	}
}

/*===========================================================================================================
 * [Function Name] : GPIO_writePort
 * [Description]   : Write a certain value (high or low) in a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 *                   <a_value>      -> Indicates to the required value.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_writePort(uint8 a_portID, uint8 a_value)
{
	if(a_portID < NUM_OF_PORTS)
	{
		volatile uint8* const registerAddress = (&PORTA)-(a_portID*GPIO_REG_GAP);
		*registerAddress = a_value;
	}
	else
	{
		/* Do Nothing */
	}
}

/*===========================================================================================================
 * [Function Name] : GPIO_readPin
 * [Description]   : Read the value of a certain pin in a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns the value of the pin in uint8 size.
 ==========================================================================================================*/
uint8 GPIO_readPin(uint8 a_portID, uint8 a_pinID)
{
	GPIO_pinStateType pinValue = LOW_PIN;

	if(a_portID < NUM_OF_PORTS || a_pinID < NUM_OF_PINS_PER_PORT)
	{
		volatile const uint8* const registerAddress = (&PINA)-(a_portID*GPIO_REG_GAP);
		pinValue = GET_BIT(*registerAddress,a_pinID);
		return pinValue;
	}
	else
	{
		return pinValue;
	}
}

/*===========================================================================================================
 * [Function Name] : GPIO_readPort
 * [Description]   : Read the value of a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 * [return]        : The function returns the value of the port in uint8 size.
 ==========================================================================================================*/
uint8 GPIO_readPort(uint8 a_portID)
{
	uint8 portValue = 0;

	if(a_portID < NUM_OF_PORTS)
	{
		volatile const uint8* const registerAddress = (&PINA)-(a_portID*GPIO_REG_GAP);
		portValue = *registerAddress;
		return portValue;
	}
	else
	{
		return portValue;
	}
}
