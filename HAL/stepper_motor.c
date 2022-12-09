/*
===========================================================================================================
Author       : Mamoun
Module       : Stepper Motor
File Name    : stepper_motor.c
Date Created : Dec 6, 2022
Description  : Source file for the Stepper Motor driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "stepper_motor.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : STEPPER_init
 * [Description]   : Initialize the stepper motor by adjusting its pin direction,
 *                   and disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void STEPPER_init(void)
{
	GPIO_setupPinDirection(STEPPER_DIRECTION_PORT_ID,STEPPER_DIRECTION_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,OUTPUT_PIN);
	GPIO_writePin(STEPPER_DIRECTION_PORT_ID,STEPPER_DIRECTION_PIN_ID,LOW_PIN);
	GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,LOW_PIN);
}

/*===========================================================================================================
 * [Function Name] : STEPPER_rotate
 * [Description]   : Rotate the stepper motor with specific steps in a specific direction.
 *                   Rotation is accelerated up and down to make a smooth movement.
 * [Arguments]     : <a_direction>      -> Indicates to the required direction.
 *                   <a_steps>          -> Indicates to the required number of steps.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void STEPPER_rotate(STEPPER_directionType a_direction, uint32 a_steps)
{
	uint32 steps_counter;
	float64 variable_delay;

	GPIO_writePin(STEPPER_DIRECTION_PORT_ID,STEPPER_DIRECTION_PIN_ID,a_direction);

	for(steps_counter = 0, variable_delay = 28.5; steps_counter < ACCELERATION_STEPS; steps_counter++, variable_delay-=0.003)
	{
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,HIGH_PIN);
		_delay_ms(variable_delay);
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,LOW_PIN);
		_delay_ms(variable_delay);
	}

	for(steps_counter = 0; steps_counter < (a_steps-(2*ACCELERATION_STEPS)); steps_counter++)
	{
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,HIGH_PIN);
		_delay_ms(CONSTANT_SPEED_HIGH_DELAY);
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,LOW_PIN);
		_delay_ms(CONSTANT_SPEED_LOW_DELAY);
	}

	for(steps_counter = 0, variable_delay = 1.5; steps_counter < ACCELERATION_STEPS; steps_counter++, variable_delay+=0.003)
	{
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,HIGH_PIN);
		_delay_ms(variable_delay);
		GPIO_writePin(STEPPER_STEPS_PORT_ID,STEPPER_STEPS_PIN_ID,LOW_PIN);
		_delay_ms(variable_delay);
	}
}
