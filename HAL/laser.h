/*
===========================================================================================================
Author       : Mamoun
Module       : Laser
File Name    : laser.h
Date Created : Jan 10, 2023
Description  : Header file for the Laser driver.
===========================================================================================================
*/


#ifndef HAL_LASER_H_
#define HAL_LASER_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define LASER_PORT_ID          (PORTC_ID)
#define LASER_PIN_ID           (PIN4_ID)

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : LASER_init
 * [Description]   : Initialize a specific Laser by: - Adjusting its pin direction.
 *                                                   - Disable it in the beginning.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_init(void);


/*===========================================================================================================
 * [Function Name] : LASER_on
 * [Description]   : Turn the Laser ON.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_on(void);


/*===========================================================================================================
 * [Function Name] : LASER_off
 * [Description]   : Turn the Laser OFF.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the Laser is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LASER_off(void);

#endif /* HAL_LASER_H_ */
