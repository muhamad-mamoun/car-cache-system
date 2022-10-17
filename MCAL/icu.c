/*
===========================================================================================================
Author       : Mamoun
Module       : Input Capture Unit
File Name    : icu.c
Date Created : Oct 6, 2022
Description  : Source file for the AVR ICU driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "icu.h"
#include "gpio.h"
#include "../OTHERS/common_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

volatile static void (*g_ptr2func)(void) = NULL_PTR;

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/

ISR(TIMER1_CAPT_vect)
{
	if(g_ptr2func != NULL_PTR)
	{
		(*g_ptr2func)();
	}
}

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : ICU_init
 * [Description]   : Initialize the ICU with specific configurations.
 * [Arguments]     : <a_configurations>      -> Pointer to structure.
 *                                              This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_init(ICU_configurations* a_configurations)
{
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,OUTPUT_PIN);          /* Set PD6/ICP as output pin */
	SET_BIT(TCCR1A,FOC1A);                                        /* Specifies a non-PWM mode */
	SET_BIT(TCCR1A,FOC1B);                                        /* Specifies a non-PWM mode */
	WRITE_BIT(TCCR1B,ICES1,a_configurations->edge);               /* Select the required edge */
	TCCR1B = (TCCR1B&0XF8)|(a_configurations->clock);             /* Select the required clock */
	TCNT1 = 0;                                                    /* Clear timer register value */
	ICR1 = 0;                                                     /* Clear ICU register value */
	SET_BIT(TIMSK,TICIE1);                                        /* Enable ICU interrupt */
}

/*===========================================================================================================
 * [Function Name] : ICU_setEdgeDetection
 * [Description]   : Select the required edge to be detected.
 * [Arguments]     : <a_edge>      -> Indicates to the required edge.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_setEdgeDetection(ICU_edgeSelectionType a_edge)
{
	WRITE_BIT(TCCR1B,ICES1,a_edge);                               /* Select the required edge */
}

/*===========================================================================================================
 * [Function Name] : ICU_getInputCaptureValue
 * [Description]   : Read the input capture register value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;                                                  /* Return ICU register value */
}

/*===========================================================================================================
 * [Function Name] : ICU_clearTimerValue
 * [Description]   : Clear the timer register value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;                                                    /* Clear timer register value */
}

/*===========================================================================================================
 * [Function Name] : ICU_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_setCallBack(void(*a_ptr2func)(void))
{
	g_ptr2func = a_ptr2func;
}

/*===========================================================================================================
 * [Function Name] : ICU_DeInit
 * [Description]   : Disable the Timer1 to stop the ICU Driver
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_DeInit(void)
{
	/* Reset/Clear all registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,TICIE1);                                      /* Disable ICU interrupt */
}
