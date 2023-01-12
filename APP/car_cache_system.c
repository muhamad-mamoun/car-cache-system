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

SYSTEM_gateStateType g_last_gate_state = GATE_CLOSED;
static volatile void (*g_ptr2eventHandlingFunction)(void) = NULL_PTR;
uint8 g_timer_minutes_counter = 0;
uint64 g_steps_to_home = 0;
uint8 g_landed_space_id = 0;
SYSTEM_parkingSpaceDataType g_parking_spaces[SYSTEM_PARKING_SPACES] = {{1,12689,0,CLOCKWISE,EMPTY_SPACE},
		                                                               {2,0,0,COUNTERCLOCKWISE,EMPTY_SPACE},
									                           	       {3,0,0,CLOCKWISE,EMPTY_SPACE},
											                           {4,0,0,COUNTERCLOCKWISE,EMPTY_SPACE},
											                           {5,0,0,CLOCKWISE,EMPTY_SPACE},
											                           {6,0,0,COUNTERCLOCKWISE,EMPTY_SPACE}};

//SYSTEM_returnHomeDataType g_way_to_home = {0,CLOCKWISE};


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
	LASER_init();
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

void SystemTimeOperation(void)
{
	g_timer_minutes_counter++;
}

void SYSTEM_alarmOperations(void)
{

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
	/* Set the Enter Car event as the current event. */
	g_ptr2eventHandlingFunction = SYSTEM_enterCar;
}

void SYSTEM_enterCar(void)
{
	/*==========================================================================
	 *
	 *
	 *
	 *
	 *
	 =========================================================================*/
	// Event Handling...
	uint8 parking_space_id;
	parking_space_id = SYSTEM_findEmptyParkingSpace();
	if(parking_space_id == 0)
	{
		LCD_clearScrean();
		LCD_displayStringRowColumn("Car-Cache System",0,2);
		LCD_displayStringRowColumn("We Are Sorry",2,4);
		LCD_displayStringRowColumn("No Empty Spaces!",3,2);
		_delay_ms(4000);
	}
	else
	{
		LCD_clearScrean();
		LCD_displayStringRowColumn("Car-Cache System",0,2);
		LCD_displayStringRowColumn("The Space Is Landing",2,0);
		LCD_displayStringRowColumn("Please Wait...",2,3);
		// 1- rotate motor
		SYSTEM_rotateGarage(SPACE_DOWN,parking_space_id);

		LCD_clearScrean();
		LCD_displayStringRowColumn("Car-Cache System",0,2);
		LCD_displayStringRowColumn("You Are Welcome.",2,2);

		// 2- open the gate
		SYSTEM_openGate();
		// 3- parking assistant
		SYSTEM_parkingAssistant();
		// 4- user detection using IR
		LASER_on();
		_delay_ms(100);
		while(IR_checkState() == IR_RECEIVING);
		// 5- waiting min, close the gate, and return home
//		TIMER0_CTC_init(a_ptr2configurations);
//		TIMER0_setCallBack(SYSTEM_timingOperations);

		SYSTEM_closeGate();
		// 6- update space data (array & EEPROM)
		SYSTEM_updateparkingSpaceData(parking_space_id,BUSY_SPACE);
		(g_parking_spaces + parking_space_id - 1)->available_flag = BUSY_SPACE;
	}

	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);
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
			break;
		}
	}
	return parking_space_id;
}

void SYSTEM_rotateGarage(SYSTEM_garageRotationStateType a_garage_rotation_state, uint8 a_space_id)
{
	uint64 rotation_steps;
	STEPPER_directionType rotation_direction;

	if(a_space_id != 0)
	{
		rotation_steps = (g_parking_spaces + a_space_id - 1)->steps_to_gate;
		rotation_direction = (g_parking_spaces + a_space_id - 1)->direction_to_gate;
		if(a_garage_rotation_state == SPACE_UP) rotation_direction ^= 1;

		DISABLE_GLOBAL_INT();
		STEPPER_rotate(rotation_direction,rotation_steps);
		ENABLE_GLOBAL_INT();
	}
}

void SYSTEM_parkingAssistant(void)
{
	uint16 distance;

	ULTRASONIC_init();
	LED_off(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_GREEN_LED_PIN_ID);
	LED_on(PARKING_ASSISTANT_GREEN_LED_PIN_ID,PARKING_ASSISTANT_RED_LED_PIN_ID);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!! NOT IDEAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	do
	{
		distance = ULTRASONIC_readDistance();
	}while(distance > PARKING_ASSISTANT_SAFE_DISTANCE);

	LED_off(PARKING_ASSISTANT_GREEN_LED_PIN_ID,PARKING_ASSISTANT_RED_LED_PIN_ID);
	LED_on(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_GREEN_LED_PIN_ID);
}

void SYSTEM_checkUserExit(void)
{
	TIMER0_CTC_configurationsType TIMER0_configurations = {};
	TIMER0_setCallBack(SystemTimeOperation);
	TIMER0_CTC_init(&TIMER0_configurations);
	g_timer_minutes_counter = 0;

	while(((ULTRASONIC_readDistance() < DISTANCE_FROM_SENSOR_TO_GATE)\
		 ||(g_timer_minutes_counter < WAITING_TIME_TO_CLOSE_GATE))\
		 &&(g_last_gate_state == GATE_OPEN));

	if(g_last_gate_state == GATE_OPEN)
	{
		SYSTEM_closeGate();
	}
}

void SYSTEM_setRetrieveCarEvent(void)
{
	/* Set the Retrieve Car event as the current event. */
	g_ptr2eventHandlingFunction = SYSTEM_retrieveCar;
}

void SYSTEM_retrieveCar(void)
{
	/*==========================================================================
	 *
	 *
	 *
	 *
	 *
	 =========================================================================*/
	uint8 parking_space_id;
	uint32 scanned_card_id;
	// Event Handling...
	// 1- get card id
	// user interface message here ...
	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("Scan Your Card",2,3);
	LCD_displayStringRowColumn("«« HERE ««",3,5);

	// use function time-out here ...
	scanned_card_id = RFID_readCard();
	LCD_displayStringRowColumn("Card ID: ",2,3);
	LCD_displayInteger(scanned_card_id);

	// 2- search for this id
	parking_space_id = SYSTEM_findThisParkingSpace(scanned_card_id);
	if(parking_space_id == 0)
	{
		// user interface message here ...
		LCD_displayStringRowColumn("ACCESS DENIED!",3,3);
		_delay_ms(4000);
		// turn on buzzer and red led
		// counter here to activate the buzzer alarm (3 times).
	}
	else
	{
		LCD_displayStringRowColumn("ACCESS GRANTED",3,3);
		// turn on green led
		// 3- rotate motor
		SYSTEM_rotateGarage(SPACE_DOWN,parking_space_id);
		// 4- open gate
		SYSTEM_openGate();
		// 5- ultrasonic and timer to close the gate
		// .....
		SYSTEM_closeGate();
		// 6- go to home position
		SYSTEM_updateparkingSpaceData(parking_space_id,EMPTY_SPACE);
		(g_parking_spaces + parking_space_id - 1)->available_flag = EMPTY_SPACE;
		// zeroing the counter here (3 times).
	}

	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);
	g_ptr2eventHandlingFunction = NULL_PTR;
}

uint8 SYSTEM_findThisParkingSpace(uint32 a_card_id)
{
	uint8 parking_space_id = 0;
	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		if((g_parking_spaces + counter)->rfid_card_id == a_card_id)
		{
			parking_space_id = (g_parking_spaces + counter)->space_id;
			break;
		}
	}
	return parking_space_id;
}

void SYSTEM_setReturnHomeEvent(void)
{
	/* Set the Return Home event as the current event. */
	g_ptr2eventHandlingFunction = SYSTEM_returnHome;
}

void SYSTEM_returnHome(void)
{
	if(g_last_gate_state == GATE_OPEN)
	{
		SYSTEM_closeGate();
	}

	SYSTEM_rotateGarage(SPACE_UP,g_landed_space_id);

	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);
	g_ptr2eventHandlingFunction = NULL_PTR;
}

void SYSTEM_openGate(void)
{
	SERVO_init();
	SERVO_setAngle(90);
	g_last_gate_state = GATE_OPEN;
}

void SYSTEM_closeGate(void)
{
	SERVO_init();
	SERVO_setAngle(0);
	g_last_gate_state = GATE_CLOSED;
}
