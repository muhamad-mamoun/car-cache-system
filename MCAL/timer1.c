/*
===========================================================================================================
Author       : Mamoun
Module       : Timer1
File Name    : timer1.c
Date Created : Nov 1, 2022
Description  : Source file for the AVR Timer1 driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

static TIMER1_clockPrescalerType g_last_prescaler_value = TIMER1_NO_CLOCK;
static volatile void (*g_ptr2callbackfunc)(void) = NULL_PTR;

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/

ISR(TIMER1_OVF_vect)
{
	if(g_ptr2callbackfunc != NULL_PTR)
	{
		(*g_ptr2callbackfunc)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_ptr2callbackfunc != NULL_PTR)
	{
		(*g_ptr2callbackfunc)();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_ptr2callbackfunc != NULL_PTR)
	{
		(*g_ptr2callbackfunc)();
	}
}

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : TIMER1_OVERFLOW_init
 * [Description]   : Initialize Timer1 to run in Overflow mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_OVERFLOW_init(const TIMER1_OVERFLOW_configurationsType* a_ptr2configurations)
{
	TIMER1_Deinit();                   /* De-Initialize Timer1 to reset the previous configurations. */
	TCCR1A |= (1<<FOC1A);                                       /* Specifies a non-PWM mode.         */
	TCCR1A |= (1<<FOC1B);                                       /* Specifies a non-PWM mode.         */
	TIMSK |= (1<<TOIE1);                                        /* Enable Overflow Interrupt.        */
	TCNT1 = a_ptr2configurations->initial_value;                /* Set Timer1 initial value.         */
	TCCR1B = (TCCR1B & 0XF8)|(a_ptr2configurations->prescaler); /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER1_CTC_init
 * [Description]   : Initialize Timer1 to run in CTC mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_CTC_init(const TIMER1_CTC_configurationsType* a_ptr2configurations)
{
	TIMER1_Deinit();                   /* De-Initialize Timer1 to reset the previous configurations. */
	TCCR1A |= (1<<FOC1A);                                       /* Specifies a non-PWM mode.         */
	TCCR1A |= (1<<FOC1B);                                       /* Specifies a non-PWM mode.         */
	TCCR1B |= (1<<WGM12);                                       /* Set Timer1 to CTC mode.           */
	TIMSK |= (1<<OCIE1A);                                       /* Enable Compare Match Interrupt.   */
	OCR1A = a_ptr2configurations->compare_value;                /* Set Timer1 compare value.         */
	TCCR1B = (TCCR1B & 0XF8)|(a_ptr2configurations->prescaler); /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER1_PWM_init
 * [Description]   : Initialize Timer1 to run in Fast PWM mode with specific configurations.
 * [Arguments]     : <a_ptr2configurations>      -> Pointer to structure.
 *                                                  This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_PWM_init(const TIMER1_PWM_configurationsType* a_ptr2configurations)
{
	/* Calculate the required PWM frequency and duty-cycle based on the configurations. */
	uint16 OCR1A_value = (F_CPU/(a_ptr2configurations->frequency*a_ptr2configurations->prescaler_divider))-1;
	uint16 OCR1B_value = (uint16)(OCR1A_value * (a_ptr2configurations->duty_cycle/100.00));

	TIMER1_Deinit();                   /* De-Initialize Timer1 to reset the previous configurations. */
	TCCR1A = (TCCR1A & 0XCF)|((a_ptr2configurations->OC1B_output_mode)<<4);        /* Set OC1B mode. */
	TCCR1A |= (1<<WGM10)|(1<<WGM11);                            /* Set Timer1 to Fast PWM mode (15). */
	TCCR1B |= (1<<WGM12)|(1<<WGM13);                            /* Set Timer1 to Fast PWM mode (15). */
	OCR1A = OCR1A_value;                                        /* Set the required PWM frequency.   */
	OCR1B = OCR1B_value;                                        /* Set the required PWM duty-cycle.  */
	TCCR1B = (TCCR1B & 0XF8)|(a_ptr2configurations->prescaler); /* Select the required prescaler.    */

	/* Store the prescaler value to be used in resume function */
	g_last_prescaler_value = a_ptr2configurations->prescaler;
}

/*===========================================================================================================
 * [Function Name] : TIMER1_setCallBack
 * [Description]   : Save the address of the call back function in a global variable.
 * [Arguments]     : <a_ptr2callbackfunc>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_setCallBack(void (*a_ptr2callbackfunc)(void))
{
	g_ptr2callbackfunc = a_ptr2callbackfunc;
}

/*===========================================================================================================
 * [Function Name] : TIMER1_pause
 * [Description]   : Disable TIMER1 counting.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_pause(void)
{
	/* Disable Clock Source To Pause Timer1. */
	TCCR1B = (TCCR1B & 0XF8);
}

/*===========================================================================================================
 * [Function Name] : TIMER1_resume
 * [Description]   : Take TIMER1 back to continue the previous operation.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_resume(void)
{
	/* Set the previous prescaler to resume Timer1. */
	TCCR1B = (TCCR1B & 0XF8)|(g_last_prescaler_value);
}

/*===========================================================================================================
 * [Function Name] : TIMER1_Deinit
 * [Description]   : De-Initialize TIMER1 by resetting all registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void TIMER1_Deinit(void)
{
	g_ptr2callbackfunc = NULL_PTR;
	TIMSK = (TIMSK & 0XC3);
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
}
