/*
===========================================================================================================
Author       : Mamoun
Module       : Input Capture Unit
File Name    : icu.h
Date Created : Oct 6, 2022
Description  : Header file for the AVR ICU driver.
===========================================================================================================
*/


#ifndef ICU_H_
#define ICU_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	FALLING,RISING
}ICU_edgeSelectionType;

typedef enum
{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_clockPrescalerType;

typedef struct
{
	ICU_edgeSelectionType edge;
	ICU_clockPrescalerType prescaler;
}ICU_configurationsType;

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : ICU_init
 * [Description]   : Initialize the ICU with specific configurations.
 * [Arguments]     : <a_configurations>      -> Pointer to structure.
 *                                              This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_init(ICU_configurationsType* a_ptr2configurations);


/*===========================================================================================================
 * [Function Name] : ICU_setEdgeDetection
 * [Description]   : Select the required edge to be detected.
 * [Arguments]     : <a_edge>      -> Indicates to the required edge.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_setEdgeDetection(ICU_edgeSelectionType a_edge);


/*===========================================================================================================
 * [Function Name] : ICU_getInputCaptureValue
 * [Description]   : Read the input capture register value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
uint16 ICU_getInputCaptureValue(void);


/*===========================================================================================================
 * [Function Name] : ICU_clearTimerValue
 * [Description]   : Clear the timer register value.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_clearTimerValue(void);


/*===========================================================================================================
 * [Function Name] : ICU_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_setCallBack(void (*a_ptr2callBackFunction)(void));


/*===========================================================================================================
 * [Function Name] : ICU_DeInit
 * [Description]   : Disable the Timer1 to stop the ICU Driver
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void ICU_DeInit(void);

#endif /* ICU_H_ */
