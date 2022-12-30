/*
===========================================================================================================
Author       : Mamoun
Module       : Buzzer
File Name    : buzzer.c
Date Created : Oct 15, 2022
Description  : Source file for the buzzer driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "buzzer.h"
#include "../MCAL/gpio.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : BUZZER_init
 * [Description]   : Initialize the buzzer by adjusting its pin direction and disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,OUTPUT_PIN);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOW_PIN);
}

/*===========================================================================================================
 * [Function Name] : BUZZER_on
 * [Description]   : Turn the buzzer ON.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void BUZZER_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,HIGH_PIN);
}

/*===========================================================================================================
 * [Function Name] : BUZZER_off
 * [Description]   : Turn the buzzer OFF.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void BUZZER_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOW_PIN);
}
