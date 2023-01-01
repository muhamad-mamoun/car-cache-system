/*
===========================================================================================================
Author       : Mamoun
Module       : Timer0
File Name    : timer0.h
Date Created : Nov 1, 2022
Description  : Header file for the AVR Timer0 driver.
===========================================================================================================
*/


#ifndef TIMER0_H_
#define TIMER0_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

typedef enum
{
	TIMER0_NORMAL,
	TIMER0_TOGGLE,
	TIMER0_NON_INVERTING,
	TIMER0_INVERTING
}TIMER0_compareOutputModeType;

typedef enum
{
	TIMER0_NO_CLOCK,
	TIMER0_FCPU_1,
	TIMER0_FCPU_8,
	TIMER0_FCPU_64,
	TIMER0_FCPU_256,
	TIMER0_FCPU_1024,
	TIMER0_COUNTER_FALLING,
	TIMER0_COUNTER_RISING
}TIMER0_clockPrescalerType;

typedef struct
{
	uint8 initial_value;
	TIMER0_clockPrescalerType prescaler;
}TIMER0_OVERFLOW_configurationsType;

typedef struct
{
	uint8 compare_value;
	TIMER0_clockPrescalerType prescaler;
}TIMER0_CTC_configurationsType;

typedef struct
{
	uint8 duty_cycle;
	TIMER0_clockPrescalerType prescaler;
	TIMER0_compareOutputModeType OC0_output_mode;
}TIMER0_PWM_configurationsType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : TIMER0_OVERFLOW_init
 * [Description]   : Initialize Timer0 to run in Overflow mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_OVERFLOW_init(const TIMER0_OVERFLOW_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER0_CTC_init
 * [Description]   : Initialize Timer0 to run in CTC mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_CTC_init(const TIMER0_CTC_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER0_PWM_init
 * [Description]   : Initialize Timer1 to run in Fast PWM mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_PWM_init(const TIMER0_PWM_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER0_setCallBack
 * [Description]   : Save the address of the call back function in a global variable.
 * [Arguments]     : <a_ptr2callbackfunc>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_setCallBack(void (*a_ptr2callbackfunc)(void));


/*===========================================================================================================
 * [Function Name] : TIMER0_pause
 * [Description]   : Disable TIMER0 counting.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_pause(void);


/*===========================================================================================================
 * [Function Name] : TIMER0_resume
 * [Description]   : Take TIMER0 back to continue the previous operation.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_resume(void);


/*===========================================================================================================
 * [Function Name] : TIMER0_Deinit
 * [Description]   : De-Initialize TIMER0 by resetting all registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_Deinit(void);

#endif /* TIMER0_H_ */
