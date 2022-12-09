/*
===========================================================================================================
Author       : Mamoun
Module       : Stepper Motor
File Name    : stepper_motor.h
Date Created : Dec 6, 2022
Description  : Header file for the Stepper Motor driver.
===========================================================================================================
*/


#ifndef HAL_STEPPER_MOTOR_H_
#define HAL_STEPPER_MOTOR_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define STEPPER_DIRECTION_PORT_ID          (PORTB_ID)
#define STEPPER_DIRECTION_PIN_ID           (PIN6_ID)

#define STEPPER_STEPS_PORT_ID              (PORTB_ID)
#define STEPPER_STEPS_PIN_ID               (PIN7_ID)

#define ACCELERATION_STEPS                 (9000U)
#define CONSTANT_SPEED_LOW_DELAY           (1)
#define CONSTANT_SPEED_HIGH_DELAY          (2)

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	COUNTERCLOCKWISE,CLOCKWISE  // test and confirm. if not, swap.
}STEPPER_directionType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : STEPPER_init
 * [Description]   : Initialize the stepper motor by adjusting its pin direction,
 *                   and disable it in the beginning.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void STEPPER_init(void);


/*===========================================================================================================
 * [Function Name] : STEPPER_rotate
 * [Description]   : Rotate the stepper motor with specific steps in a specific direction.
 *                   Rotation is accelerated up and down to make a smooth movement.
 * [Arguments]     : <a_direction>      -> Indicates to the required direction.
 *                   <a_steps>          -> Indicates to the required number of steps.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void STEPPER_rotate(STEPPER_directionType a_direction, uint32 a_steps);

#endif /* HAL_STEPPER_MOTOR_H_ */
