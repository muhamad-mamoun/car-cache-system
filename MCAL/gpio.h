/*
===========================================================================================================
Author       : Mamoun
Module       : GPIO
File Name    : gpio.h
Date Created : Oct 6, 2022
Description  : Header file for the AVR GPIO peripheral driver.
===========================================================================================================
*/


#ifndef GPIO_H_
#define GPIO_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define GPIO_REG_GAP              (3u)    /* The gap between two ports in the memory */

#define NUM_OF_PORTS              (4u)    /* The number of IO ports in the MC */
#define NUM_OF_PINS_PER_PORT      (8u)    /* The number of pins in every port */

#define PORTA_ID                  (0u)
#define PORTB_ID                  (1u)
#define PORTC_ID                  (2u)
#define PORTD_ID                  (3u)

#define PIN0_ID                   (0u)
#define PIN1_ID                   (1u)
#define PIN2_ID                   (2u)
#define PIN3_ID                   (3u)
#define PIN4_ID                   (4u)
#define PIN5_ID                   (5u)
#define PIN6_ID                   (6u)
#define PIN7_ID                   (7u)

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	LOW_PIN , HIGH_PIN
}GPIO_pinStateType;

typedef enum
{
	LOW_PORT , HIGH_PORT=0XFF
}GPIO_portStateType;

typedef enum
{
	INPUT_PIN , OUTPUT_PIN
}GPIO_pinDirectionType;

typedef enum
{
	INPUT_PORT , OUTPUT_PORT=0XFF
}GPIO_portDirectionType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : GPIO_setupPinDirection
 * [Description]   : Setup the direction of a certain pin (input or output).
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 *                   <a_direction>  -> Indicates to the required direction.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_setupPinDirection(uint8 a_portID, uint8 a_pinID, GPIO_pinDirectionType a_direction);


/*===========================================================================================================
 * [Function Name] : GPIO_setupPortDirection
 * [Description]   : Setup the direction of a certain port (input or output).
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 *                   <a_direction>  -> Indicates to the required direction.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_setupPortDirection(uint8 a_portID, GPIO_portDirectionType a_direction);


/*===========================================================================================================
 * [Function Name] : GPIO_writePin
 * [Description]   : Write a certain value (high or low) in a certain pin.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 *                   <a_value>      -> Indicates to the required value (high or low).
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_writePin(uint8 a_portID, uint8 a_pinID, GPIO_pinStateType a_value);


/*===========================================================================================================
 * [Function Name] : GPIO_writePort
 * [Description]   : Write a certain value (high or low) in a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 *                   <a_value>      -> Indicates to the required value (high or low).
 * [return]        : The function returns void.
 ==========================================================================================================*/
void GPIO_writePort(uint8 a_portID, uint8 a_value);


/*===========================================================================================================
 * [Function Name] : GPIO_readPin
 * [Description]   : Read the value of a certain pin in a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which pin is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns the value of the pin in uint8 size.
 ==========================================================================================================*/
uint8 GPIO_readPin(uint8 a_portID, uint8 a_pinID);


/*===========================================================================================================
 * [Function Name] : GPIO_readPort
 * [Description]   : Read the value of a certain port.
 * [Arguments]     : <a_portID>     -> Indicates to the port number.
 * [return]        : The function returns the value of the port in uint8 size.
 ==========================================================================================================*/
uint8 GPIO_readPort(uint8 a_portID);

#endif /* GPIO_H_ */
