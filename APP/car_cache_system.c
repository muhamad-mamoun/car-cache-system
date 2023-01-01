/*
===========================================================================================================
Project      : Car-Cache System
File Name    : car_cache_system.c
Date Created : Jan 1, 2023
Description  : Vertical Rotary Car Parking System.
===========================================================================================================
*/

#warning "The project is not finished yet."

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "car_cache_system.h"

/*===========================================================================================================
                                           < Global Variables >
===========================================================================================================*/

uint64 g_steps_to_home = 0;

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/



/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ==========================================================================================================*/
int main(void)
{
	SYSTEM_init();
	while(1);
}

void SYSTEM_init(void)
{
	ENABLE_GLOBAL_INT();

	LCD_init();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("Welcome!",2,6);

	IR_init();
	RFID_init();
	BUZZER_init();
	STEPPER_init();

	LED_init(PORTB_ID,PIN6_ID);
	LED_init(PORTB_ID,PIN7_ID);
	LED_init(PORTC_ID,PIN6_ID);
	LED_init(PORTC_ID,PIN7_ID);

	MEEPROM_voidInit();
	// read the data from eeprom.

	INT0_init(INT0_RISING_EDGE);
	INT1_init(INT1_RISING_EDGE);
	INT2_init(INT2_RISING_EDGE);
	INT0_setCallBack(SYSTEM_enterCar);
	INT1_setCallBack(SYSTEM_retrieveCar);
	INT2_setCallBack(SYSTEM_returnHome);

	_delay_ms(3000);
	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);
}

void SYSTEM_enterCar(void)
{

}

void SYSTEM_retrieveCar(void)
{

}

void SYSTEM_returnHome(void)
{
	// assure that the gate is closed.
	STEPPER_rotate(a_direction,g_steps_to_home);
}




