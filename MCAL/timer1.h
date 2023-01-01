/*
===========================================================================================================
Author       : Mamoun
Module       : Timer1
File Name    : timer1.h
Date Created : Nov 1, 2022
Description  : Header file for the AVR Timer1 driver.
===========================================================================================================
*/


#ifndef TIMER1_H_
#define TIMER1_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	TIMER1_NORMAL,
	TIMER1_TOGGLE,
	TIMER1_NON_INVERTING,
	TIMER1_INVERTING
}TIMER1_compareOutputModeType;

typedef enum
{
	TIMER1_NO_CLOCK,
	TIMER1_FCPU_1,
	TIMER1_FCPU_8,
	TIMER1_FCPU_64,
	TIMER1_FCPU_256,
	TIMER1_FCPU_1024,
	TIMER1_COUNTER_FALLING,
	TIMER1_COUNTER_RISING
}TIMER1_clockPrescalerType;

typedef struct
{
	uint16 initial_value;
	TIMER1_clockPrescalerType prescaler;
}TIMER1_OVERFLOW_configurationsType;

typedef struct
{
	uint16 compare_value;
	TIMER1_clockPrescalerType prescaler;
}TIMER1_CTC_configurationsType;

typedef struct
{
	uint8 duty_cycle;
	uint32 frequency;
	uint16 prescaler_divider; /* The devider value (1, 8, 64, 256, or 1024). */
	TIMER1_clockPrescalerType prescaler;
	TIMER1_compareOutputModeType OC1B_output_mode;
}TIMER1_PWM_configurationsType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : TIMER1_OVERFLOW_init
 * [Description]   : Initialize Timer1 to run in Overflow mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_OVERFLOW_init(const TIMER1_OVERFLOW_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER1_CTC_init
 * [Description]   : Initialize Timer1 to run in CTC mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_CTC_init(const TIMER1_CTC_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER1_PWM_init
 * [Description]   : Initialize Timer1 to run in Fast PWM mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_PWM_init(const TIMER1_PWM_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : TIMER1_PWM_setDutyCycle
 * [Description]   : Set the required PWM duty-cycle.
 * [Arguments]     : <a_duty_cycle>      -> Indicates to the required duty-cycle percent (0% - 100%).
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_PWM_setDutyCycle(uint8 a_duty_cycle);


/*===========================================================================================================
 * [Function Name] : TIMER1_setCallBack
 * [Description]   : Save the address of the call back function in a global variable.
 * [Arguments]     : <a_ptr2callbackfunc>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_setCallBack(void (*a_ptr2callbackfunc)(void));


/*===========================================================================================================
 * [Function Name] : TIMER1_pause
 * [Description]   : Disable TIMER1 counting.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_pause(void);


/*===========================================================================================================
 * [Function Name] : TIMER1_resume
 * [Description]   : Take TIMER1 back to continue the previous operation.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_resume(void);


/*===========================================================================================================
 * [Function Name] : TIMER1_Deinit
 * [Description]   : De-Initialize TIMER1 by resetting all registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_Deinit(void);

#endif /* TIMER1_H_ */
