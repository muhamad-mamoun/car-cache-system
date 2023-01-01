/*
===========================================================================================================
Author       : Mamoun
Module       : Ultrasonic Sensor
File Name    : ultrasonic.c
Date Created : Oct 15, 2022
Description  : Source file for the ultrasonic sensor driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "ultrasonic.h"
#include "../MCAL/icu.h"
#include "../MCAL/gpio.h"
#include "../OTHERS/common_macros.h"
#include <util/delay.h>

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

static uint16 g_pulseWidthTime = 0;
static volatile uint8 g_edgeCounter = 0;
static volatile ICU_configurationsType g_ICU_configurations = {RISING,F_CPU_8};

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : ULTRASONIC_init
 * [Description]   : Initialize the ultrasonic by :
 *                   1- Initialize the ICU module.
 *                   2- Setup the call-back function (ULTRASONIC_edgeProcessing).
 *                   3- Setup the trigger pin direction as output pin.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ULTRASONIC_init(void)
{
	ICU_init(&g_ICU_configurations);
	ICU_setCallBack(ULTRASONIC_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,OUTPUT_PIN);
}

/*===========================================================================================================
 * [Function Name] : ULTRASONIC_edgeProcessing
 * [Description]   : Change the edge type and get the input capture value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ULTRASONIC_edgeProcessing(void)
{
	g_edgeCounter++;
	switch (g_edgeCounter)
	{
	case 1 :
		ICU_setEdgeDetection(FALLING);
		ICU_clearTimerValue();
		break;
	case 2 :
		g_pulseWidthTime = ICU_getInputCaptureValue();
		ICU_setEdgeDetection(RISING);
		ICU_clearTimerValue();
		break;
	}
}

/*===========================================================================================================
 * [Function Name] : ULTRASONIC_trigger
 * [Description]   : Write a high pulse on the trigger pin for 10us.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ULTRASONIC_trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,HIGH_PIN);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOW_PIN);
}

/*===========================================================================================================
 * [Function Name] : ULTRASONIC_readDistance
 * [Description]   : Get the pulse width time and calculate the distance.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the calculated distance.
 ==========================================================================================================*/
uint16 ULTRASONIC_readDistance(void)
{
	int distance = 0;
	g_edgeCounter = 0;
	ULTRASONIC_trigger();
	while(g_edgeCounter != ICU_NUM_OF_EDGES);
	distance = (int)(((uint64)g_pulseWidthTime * ICU_PS_VALUE * SOUND_WAVE_SPEED)/(2 * F_CPU));
	return distance;
}
