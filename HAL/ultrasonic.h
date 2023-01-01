/*
===========================================================================================================
Author       : Mamoun
Module       : Ultrasonic Sensor
File Name    : ultrasonic.h
Date Created : Oct 15, 2022
Description  : Header file for the ultrasonic sensor driver.
===========================================================================================================
*/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define ULTRASONIC_TRIGGER_PORT_ID                    (PORTD_ID)
#define ULTRASONIC_TRIGGER_PIN_ID                     (PIN7_ID)

#define ICU_NUM_OF_EDGES                              (2)
#define SOUND_WAVE_SPEED                              (34000UL)
#define ICU_PS_VALUE                                  (8)

/*===========================================================================================================
                                         < Functions Prototypes >
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
void ULTRASONIC_init(void);


/*===========================================================================================================
 * [Function Name] : ULTRASONIC_edgeProcessing
 * [Description]   : Change the edge type and get the input capture value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ULTRASONIC_edgeProcessing(void);


/*===========================================================================================================
 * [Function Name] : ULTRASONIC_trigger
 * [Description]   : Write a high pulse on the trigger pin for 10us.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ULTRASONIC_trigger(void);


/*===========================================================================================================
 * [Function Name] : ULTRASONIC_readDistance
 * [Description]   : Get the pulse width time and calculate the distance.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the calculated distance.
 ==========================================================================================================*/
uint16 ULTRASONIC_readDistance(void);

#endif /* ULTRASONIC_H_ */
