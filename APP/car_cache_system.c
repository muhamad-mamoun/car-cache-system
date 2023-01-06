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

static volatile void (*g_ptr2eventHandlingFunction)(void) = NULL_PTR;

uint64 g_steps_to_home = 0;
SYSTEM_parkingSpaceData g_parking_spaces[SYSTEM_PARKING_SPACES] = {{1,12689,0,CLOCKWISE,EMPTY_SPACE},
		                                                           {2,0,0,COUNTERCLOCKWISE,EMPTY_SPACE},
									                         	   {3,0,0,CLOCKWISE,EMPTY_SPACE},
											                       {4,0,0,COUNTERCLOCKWISE,EMPTY_SPACE},
											                       {5,0,0,CLOCKWISE,EMPTY_SPACE},
											                       {6,0,0,COUNTERCLOCKWISE,EMPTY_SPACE}};

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
	while(1)
	{
		if(g_ptr2eventHandlingFunction != NULL_PTR)
		{
			(*g_ptr2eventHandlingFunction)();
		}
	}
}

void SYSTEM_init(void)
{
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
	SYSTEM_retrieveParkingSpaceData();

	INT0_init(INT0_RISING_EDGE);
	INT1_init(INT1_RISING_EDGE);
	INT2_init(INT2_RISING_EDGE);
	INT0_setCallBack(SYSTEM_setEnterCarEvent);
	INT1_setCallBack(SYSTEM_setRetrieveCarEvent);
	INT2_setCallBack(SYSTEM_setReturnHomeEvent);

	_delay_ms(2000);
	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);

	ENABLE_GLOBAL_INT();
}

void SYSTEM_retrieveParkingSpaceData(void)
{
	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		(g_parking_spaces + counter)->available_flag = MEEPROM_u8Read(PARKING_SPACES_DATA_ADDRESS + counter);
	}
}

void SYSTEM_updateParkingSpaceData(uint8 a_space_id, SYSTEM_parkingSpaceStateType a_available_flag)
{
	MEEPROM_voidWrite(PARKING_SPACES_DATA_ADDRESS + a_space_id - 1,a_available_flag);
}

void SYSTEM_setEnterCarEvent(void)
{
	g_ptr2eventHandlingFunction = SYSTEM_enterCar;
}

void SYSTEM_enterCar(void)
{
	// Event Handling...
	uint8 parking_space_id;
	parking_space_id = SYSTEM_findEmptyParkingSpace();
	if(parking_space_id == 0)
	{
		// No available spaces
		LCD_displayStringRowColumn("Sorry!",2,7);
		LCD_displayStringRowColumn("No Empty Spaces!",2,2);
	}
	else
	{
		// rotate the garage, ...
		// 1- rotate motor
		// 2- open the gate
		SYSTEM_openGate();
		// 3- parking assistant
		// 4- user detection using IR
		while(IR_checkState() == IR_RECEIVING);
		// 5- waiting min, close the gate, and return home
		SYSTEM_closeGate();
		// 6- update space data (array & EEPROM)
		SYSTEM_updateparkingSpaceData(parking_space_id,BUSY_SPACE);
		(g_parking_spaces + parking_space_id - 1)->available_flag = BUSY_SPACE;
	}
	g_ptr2eventHandlingFunction = NULL_PTR;
}

uint8 SYSTEM_findEmptyParkingSpace(void)
{
	uint8 parking_space_id = 0;

	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		if((g_parking_spaces + counter)->available_flag == EMPTY_SPACE)
		{
			parking_space_id = (g_parking_spaces + counter)->space_id;
		}
	}

	return parking_space_id;
}

void SYSTEM_setRetrieveCarEvent(void)
{
	g_ptr2eventHandlingFunction = SYSTEM_retrieveCar;
}

void SYSTEM_retrieveCar(void)
{
	// Event Handling...
	// 1- get card id
	// 2- search for this id
	// 3- rotate motor
	// 4- open gate
	// 5- ultrasonic and timer to close the gate
	// 6- go to home position
	SYSTEM_updateparkingSpaceData(,);
	g_ptr2eventHandlingFunction = NULL_PTR;
}

void SYSTEM_setReturnHomeEvent(void)
{
	/* Set the Return Home event as the current event. */
	g_ptr2eventHandlingFunction = SYSTEM_returnHome;
}

void SYSTEM_returnHome(void)
{
	// assure that the gate is closed.
//	STEPPER_rotate(a_direction,g_steps_to_home);
	// Event Handling...
	g_ptr2eventHandlingFunction = NULL_PTR;
}

void SYSTEM_openGate(void)
{
	SERVO_init();
	SERVO_setAngle(90);
}

void SYSTEM_closeGate(void)
{
	SERVO_init();
	SERVO_setAngle(0);
}
