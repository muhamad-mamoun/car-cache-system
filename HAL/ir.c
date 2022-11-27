/*
===========================================================================================================
Author       : Mamoun
Module       : IR
File Name    : ir.c
Date Created : Nov 27, 2022
Description  : Source file for the IR driver.
===========================================================================================================
*/


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "ir.h"
#include "../MCAL/gpio.h"

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : IR_init
 * [Description]   : Initialize the IR by adjusting its pin direction.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void IR_init(void)
{
	GPIO_setupPinDirection(IR_PORT_ID,IR_PIN_ID,INPUT_PIN);
}

/*===========================================================================================================
 * [Function Name] : IR_checkState
 * [Description]   : Read the state of the IR if it is receiving or not.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the state of the IR.
 ==========================================================================================================*/
IR_stateType IR_checkState(void)
{
	IR_stateType ir_state;
	if(GPIO_readPin(IR_PORT_ID,IR_PIN_ID))
	{
		ir_state = IR_RECEIVING;
	}
	else
	{
		ir_state = IR_NOT_RECEIVING;
	}
	return ir_state;
}
