/*
===========================================================================================================
Author       : Mamoun
Module       : External Interrupts
File Name    : external_interrupts.h
Date Created : Oct 30, 2022
Description  : Header File for all AVR external interrupts driver.
===========================================================================================================
*/


#ifndef MCAL_EXTERNAL_INTERRUPTS_H_
#define MCAL_EXTERNAL_INTERRUPTS_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define DISABLE                   (0u)
#define ENABLE                    (1u)

#define EXTERNAL_INTERRUPT_0      (ENABLE)
#define EXTERNAL_INTERRUPT_1      (ENABLE)
#define EXTERNAL_INTERRUPT_2      (ENABLE)

/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

#if (EXTERNAL_INTERRUPT_0 == ENABLE)
typedef enum
{
	INT0_LOW_LEVEL,INT0_ANY_LOGICAL,INT0_FALLING_EDGE,INT0_RISING_EDGE
}INT0_senseControlType;
#endif

#if (EXTERNAL_INTERRUPT_1 == ENABLE)
typedef enum
{
	INT1_LOW_LEVEL,INT1_ANY_LOGICAL,INT1_FALLING_EDGE,INT1_RISING_EDGE
}INT1_senseControlType;
#endif

#if (EXTERNAL_INTERRUPT_2 == ENABLE)
typedef enum
{
	INT2_FALLING_EDGE,INT2_RISING_EDGE
}INT2_senseControlType;
#endif

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


#if (EXTERNAL_INTERRUPT_0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT0_init
 * [Description]   : Initialize external interrupt 0 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_init(INT0_senseControlType a_edgeType);


/*===========================================================================================================
 * [Function Name] : INT0_disable
 * [Description]   : Disable the external interrupt 0.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_disable(void);


/*===========================================================================================================
 * [Function Name] : INT0_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_setCallBack(void(*a_ptr2func)(void));
#endif


#if (EXTERNAL_INTERRUPT_1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT1_init
 * [Description]   : Initialize external interrupt 1 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_init(INT1_senseControlType a_edgeType);


/*===========================================================================================================
 * [Function Name] : INT1_disable
 * [Description]   : Disable the external interrupt 1.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_disable(void);


/*===========================================================================================================
 * [Function Name] : INT1_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_setCallBack(void(*a_ptr2func)(void));
#endif


#if (EXTERNAL_INTERRUPT_2 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT2_init
 * [Description]   : Initialize external interrupt 2 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_init(INT2_senseControlType a_edgeType);


/*===========================================================================================================
 * [Function Name] : INT2_disable
 * [Description]   : Disable the external interrupt 2.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_disable(void);


/*===========================================================================================================
 * [Function Name] : INT2_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_setCallBack(void(*a_ptr2func)(void));
#endif

#endif /* MCAL_EXTERNAL_INTERRUPTS_H_ */
