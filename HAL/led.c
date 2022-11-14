/*
===========================================================================================================
Author       : Mamoun
Module       : LED
File Name    : led.c
Date Created : Nov 15, 2022
Description  : Source file for the LCD driver.
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
 * [Description]   : Initialize the LED by adjusting its pin direction and disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_init(void)
{
	GPIO_setupPinDirection(LED_PORT_ID,LED_PIN_ID,OUTPUT_PIN);
	GPIO_writePin(LED_PORT_ID,LED_PIN_ID,LOW_PIN);
}

/*===========================================================================================================
 * [Function Name] : LED_on
 * [Description]   : Turn the LED ON.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_on(void)
{
	GPIO_writePin(LED_PORT_ID,LED_PIN_ID,HIGH_PIN);
}

/*===========================================================================================================
 * [Function Name] : LED_off
 * [Description]   : Turn the LED OFF.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_off(void)
{
	GPIO_writePin(LED_PORT_ID,LED_PIN_ID,LOW_PIN);
}
