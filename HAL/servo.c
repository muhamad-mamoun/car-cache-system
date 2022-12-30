/*
=============================================================================================================
Author       : Mamoun
Module       : Servo Motor
File Name    : servo.c
Date Created : Dec 19, 2022
Description  : Source file for the MG90S Servo motor driver.
=============================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "gpio.h"
#include "servo.h"
#include "timer1.h"

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

static TIMER1_PWM_configurationsType g_PWM_configurations = {0,50,256,TIMER1_FCPU_256,NON_INVERTING};

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : SERVO_init
 * [Description]   : Initialize the servo motor by: - Adjusting its pin direction.
 *                                                  - Set-up its PWM configurations.
 *                                                  - Disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SERVO_init(void)
{
	GPIO_setupPinDirection(SERVO_CONTROL_PORT_ID,SERVO_CONTROL_PIN_ID,OUTPUT_PIN);
	TIMER1_PWM_init(&g_PWM_configurations);
	TIMER1_pause();
}

/*===========================================================================================================
 * [Function Name] : SERVO_rotate
 * [Description]   : Rotate the servo motor with a specific angle
 * [Arguments]     : <a_angle_in_degree>      -> Indicates to the required angle.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SERVO_setAngle(uint8 a_angle_in_degrees)
{
	uint8 duty_cycle = (uint8)((((a_angle_in_degrees * 11.44) + SERVO_ZERO_DEG_TIME)/20000.00)*(100.00));
	TIMER1_PWM_setDutyCycle(duty_cycle);
	TIMER1_resume();
}
