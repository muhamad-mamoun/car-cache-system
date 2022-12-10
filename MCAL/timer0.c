/*
=============================================================================================================
Author       : Mamoun
Module       : Timer0
File Name    : timer0.c
Date Created : Dec 1, 2022
Description  : Source file for the AVR Timer0 driver.
=============================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

static TIMER0_clockPrescalerType g_last_prescaler_value = TIMER0_NO_CLOCK;
static volatile void (*g_ptr2callbackfunc)(void) = NULL_PTR;

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/

ISR(TIMER0_OVF_vect)
{
	if(g_ptr2callbackfunc != NULL_PTR)
	{
		/* Call the Call-Back function in the application. */
		(*g_ptr2callbackfunc)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_ptr2callbackfunc != NULL_PTR)
	{
		/* Call the Call-Back function in the application. */
		(*g_ptr2callbackfunc)();
	}
}

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : TIMER0_OVERFLOW_init
 * [Description]   : Initialize Timer0 to run in Overflow mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_OVERFLOW_init(const TIMER0_OVERFLOW_configurationsType* a_ptr2configurations)
{
	TIMER0_Deinit();                   /* De-Initialize Timer0 to reset the previous configurations. */
	TCCR0 |= (1<<FOC0);                                         /* Specifies a non-PWM mode.         */
	TIMSK |= (1<<TOIE0);                                        /* Enable Overflow Interrupt.        */
	TCNT0 = a_ptr2configurations->initial_value;                /* Set Timer0 initial value.         */
	TCCR0 = (TCCR0 & 0XF8)|(a_ptr2configurations->prescaler);   /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER0_CTC_init
 * [Description]   : Initialize Timer0 to run in CTC mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_CTC_init(const TIMER0_CTC_configurationsType* a_ptr2configurations)
{
	TIMER0_Deinit();                   /* De-Initialize Timer0 to reset the previous configurations. */
	TCCR0 |= (1<<FOC0);                                         /* Specifies a non-PWM mode.         */
	TCCR0 |= (1<<WGM01);                                        /* Set Timer0 to CTC mode.           */
	TIMSK |= (1<<OCIE0);                                        /* Enable Compare Match Interrupt.   */
	OCR0 = a_ptr2configurations->compare_value;                 /* Set Timer0 compare value.         */
	TCCR0 = (TCCR0 & 0XF8)|(a_ptr2configurations->prescaler);   /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER0_PWM_init
 * [Description]   : Initialize Timer1 to run in Fast PWM mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_PWM_init(const TIMER0_PWM_configurationsType* a_ptr2configurations)
{
	TIMER0_Deinit();                   /* De-Initialize Timer0 to reset the previous configurations. */
	TCCR0 |= (1<<WGM00);                                        /* Set Timer0 to Fast PWM mode.      */
	TCCR0 |= (1<<WGM01);                                        /* Set Timer0 to Fast PWM mode.      */
	OCR0 = (uint8)(a_ptr2configurations->duty_cycle * 2.55);    /* Set the required PWM duty-cycle.  */
	TCCR0 = (TCCR0 & 0XCF)|((a_ptr2configurations->OC0_output_mode)<<4);            /* Set OC0 mode. */
	TCCR0 = (TCCR0 & 0XF8)|(a_ptr2configurations->prescaler);   /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER0_setCallBack
 * [Description]   : Save the address of the call back function in a global variable.
 * [Arguments]     : <a_ptr2callbackfunc>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_setCallBack(void (*a_ptr2callbackfunc)(void))
{
	/* Save the address of the Call-Back function in a global pointer. */
	g_ptr2callbackfunc = a_ptr2callbackfunc;
}

/*===========================================================================================================
 * [Function Name] : TIMER0_pause
 * [Description]   : Disable TIMER0 counting.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_pause(void)
{
	/* Disable Clock Source To Pause Timer0. */
	TCCR0 = (TCCR0 & 0XF8);
}

/*===========================================================================================================
 * [Function Name] : TIMER0_resume
 * [Description]   : Take TIMER0 back to continue the previous operation.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_resume(void)
{
	/* Set the previous prescaler to resume Timer0. */
	TCCR0 = (TCCR0 & 0XF8)|(g_last_prescaler_value);
}

/*===========================================================================================================
 * [Function Name] : TIMER0_Deinit
 * [Description]   : De-Initialize TIMER0 by resetting all registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER0_Deinit(void)
{
	g_ptr2callbackfunc = NULL_PTR;
	TIMSK = (TIMSK & 0XFC);
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
}
