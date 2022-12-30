/*
=============================================================================================================
Author       : Mamoun
Module       : Servo Motor
File Name    : servo.h
Date Created : Dec 19, 2022
Description  : Header file for the MG90S Servo motor driver.
=============================================================================================================
*/


#ifndef SERVO_H_
#define SERVO_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define SERVO_CONTROL_PORT_ID          (PORTD_ID)
#define SERVO_CONTROL_PIN_ID           (PIN4_ID)

#define SERVO_ZERO_DEG_TIME            (1000.00)             /* Time for 0 deg. = 1000 us. */

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : SERVO_init
 * [Description]   : Initialize the servo motor by: - Adjusting its pin direction.
 *                                                  - Set-up its PWM configurations.
 *                                                  - Disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SERVO_init(void);


/*===========================================================================================================
 * [Function Name] : SERVO_rotate
 * [Description]   : Rotate the servo motor with a specific angle
 * [Arguments]     : <a_angle_in_degree>      -> Indicates to the required angle.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void SERVO_setAngle(uint8 a_angle_in_degrees);

#endif /* SERVO_H_ */
