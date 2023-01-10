/*
===========================================================================================================
Author       : Mamoun
Module       : Laser
File Name    : laser.c
Date Created : Jan 10, 2023
Description  : Source file for the LED driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "laser.h"
#include "../MCAL/gpio.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : LASER_init
 * [Description]   : Initialize a specific Laser by: - Adjusting its pin direction.
 *                                                   - Disable it in the beginning.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_init(void)
{
	GPIO_setupPinDirection(LASER_PORT_ID,LASER_PIN_ID,OUTPUT_PIN);     /* Adjust the Laser pin direction.    */
	GPIO_writePin(LASER_PORT_ID,LASER_PIN_ID,LOW_PIN);                 /* Disable it in the beginning.       */
}

/*===========================================================================================================
 * [Function Name] : LASER_on
 * [Description]   : Turn the Laser ON.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_on(void)
{
	GPIO_writePin(LASER_PORT_ID,LASER_PIN_ID,HIGH_PIN);                /* Turn the Laser ON. */
}

/*===========================================================================================================
 * [Function Name] : LASER_off
 * [Description]   : Turn the Laser OFF.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_off(void)
{
	GPIO_writePin(LASER_PORT_ID,LASER_PIN_ID,LOW_PIN);                /* Turn the Laser OFF. */
}
