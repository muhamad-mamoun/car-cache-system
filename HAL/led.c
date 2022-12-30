/*
===========================================================================================================
Author       : Mamoun
Module       : LED
File Name    : led.c
Date Created : Nov 15, 2022
Description  : Source file for the LED driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "led.h"
#include "../MCAL/gpio.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : LED_init
 * [Description]   : Initialize a specific LED by: - Adjusting its pin direction.
 *                                                 - Disable it in the beginning.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_init(uint8 a_portID, uint8 a_pinID)
{
	GPIO_setupPinDirection(a_portID,a_pinID,OUTPUT_PIN);     /* Adjust LED pin direction.    */
	GPIO_writePin(a_portID,a_pinID,LOW_PIN);                 /* Disable it in the beginning. */
}

/*===========================================================================================================
 * [Function Name] : LED_on
 * [Description]   : Turn a specific LED ON.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_on(uint8 a_portID, uint8 a_pinID)
{
	GPIO_writePin(a_portID,a_pinID,HIGH_PIN);                /* Turn the LED ON. */
}

/*===========================================================================================================
 * [Function Name] : LED_off
 * [Description]   : Turn a specific LED OFF.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_off(uint8 a_portID, uint8 a_pinID)
{
	GPIO_writePin(a_portID,a_pinID,LOW_PIN);                /* Turn the LED OFF. */
}
