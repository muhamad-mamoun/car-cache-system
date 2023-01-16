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

uint8 g_timer_compare_match_counter = 0;
TIMER0_CTC_configurationsType g_TIMER0_configurations = {240,TIMER0_FCPU_1024};
SYSTEM_gateStateType g_last_gate_state = GATE_CLOSED;
static volatile void (*g_ptr2eventHandlingFunction)(void) = NULL_PTR;
uint8 g_timer_seconds_counter = 0;
uint8 g_landed_parking_space_id = NULL_PARKING_SPACE_ID;
SYSTEM_parkingSpaceDataType g_parking_spaces_data[SYSTEM_PARKING_SPACES] = {{1,12689,0,CLOCKWISE,EMPTY_SPACE},
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

	TIMER0_CTC_init(a_ptr2configurations);
	TIMER0_pause();

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
	INT0_setCallBack(ActivateEnterCarEvent);
	INT1_setCallBack(ActivateRetrieveCarEvent);
	INT2_setCallBack(ActivateReturnHomeEvent);

	_delay_ms(2000);
	DisplayLaunchMessage();

	ENABLE_GLOBAL_INT();
}

void DisplayLaunchMessage(void)
{
	LCD_clearScrean();
	LCD_displayStringRowColumn("Car-Cache System",0,2);
	LCD_displayStringRowColumn("» Enter a car.",2,0);
	LCD_displayStringRowColumn("» Retrieve a car.",3,0);
}

//void SystemTimeOperation(void)
//{
//	g_timer_compare_match_counter++;
//	if(g_timer_compare_match_counter == 65)
//	{
//		g_timer_seconds_counter++;
//	}
//}

void SYSTEM_alarmOperations(void)
{

}

void FetchParkingSpacesData(void)  // DONE
{
	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		(g_parking_spaces_data + counter)->busy_parking_space_flag = MEEPROM_u8Read(PARKING_SPACES_DATA_ADDRESS + counter);
	}
}

void UpdateParkingSpaceData(uint8 a_parking_space_id, SYSTEM_parkingSpaceStateType a_busy_parking_space_flag)  // DONE
{
	MEEPROM_voidWrite(PARKING_SPACES_DATA_ADDRESS + a_parking_space_id - 1,a_busy_parking_space_flag);
}

void ActivateEnterCarEvent(void)  // DONE
{
	/* Set the Enter Car event as the current event. */
	g_ptr2eventHandlingFunction = EnterCarEvent;
}


/*==========================================================================
 * write the function s 1- 2- 3-
 =========================================================================*/
void EnterCarEvent(void)  // DONE
{
	uint8 parking_space_id = FindEmptyParkingSpace();

	if(parking_space_id == NULL_PARKING_SPACE_ID)
	{
		ClearPreviousMessages();
		LCD_displayStringRowColumn("We Are Sorry",2,4);
		LCD_displayStringRowColumn("No Empty Spaces!",3,2);
		_delay_ms(4000);
	}
	else
	{
		ClearPreviousMessages();
		LCD_displayStringRowColumn("The Space Is Landing",2,0);
		LCD_displayStringRowColumn("Please Wait...",3,3);

		RotateGarage(ROTATION_TO_GATE,parking_space_id);
		g_landed_parking_space_id = parking_space_id;

		ClearPreviousMessages();
		LCD_displayStringRowColumn("You Are Welcome.",2,2);

		OpenGarageGate();
		ParkingAssistant();
		CheckUserExit();
		_delay_ms(5000);
		CloseGarageGate();

		RotateGarage(ROTATION_TO_HOME,g_landed_parking_space_id);
		g_landed_parking_space_id = NULL_PARKING_SPACE_ID;

		SYSTEM_updateparkingSpaceData(parking_space_id,BUSY_SPACE);
		(g_parking_spaces_data + parking_space_id - 1)->busy_parking_space_flag = BUSY_SPACE;
	}

	DisplayLaunchMessage();
	g_ptr2eventHandlingFunction = NULL_PTR;
}

void ActivateRetrieveCarEvent(void)  // DONE
{
	/* Set the Retrieve Car event as the current event. */
	g_ptr2eventHandlingFunction = RetrieveCarEvent;
}

void RetrieveCarEvent(void)
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
	if(parking_space_id == NULL_PARKING_SPACE_ID)
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
		SYSTEM_rotateGarage(ROTATION_TO_GATE,parking_space_id);
		// 4- open gate
		SYSTEM_openGate();
		// 5- ultrasonic and timer to close the gate
		// .....
		SYSTEM_closeGate();
		// 6- go to home position
		SYSTEM_updateparkingSpaceData(parking_space_id,EMPTY_SPACE);
		(g_parking_spaces_data + parking_space_id - 1)->busy_parking_space_flag = EMPTY_SPACE;
		// zeroing the counter here (3 times).
	}

	DisplayLaunchMessage();
	g_ptr2eventHandlingFunction = NULL_PTR;
}

void ActivateReturnHomeEvent(void)  // DONE
{
	/* Set the Return Home event as the current event. */
	g_ptr2eventHandlingFunction = ReturnHomeEvent;
}

void ReturnHomeEvent(void)
{
	ClearPreviousMessages();
	LCD_displayStringRowColumn("Back To Home",2,4);

	_delay_ms(1000);
	CloseGarageGate();

	_delay_ms(2000);
	RotateGarage(ROTATION_TO_HOME,g_landed_parking_space_id);
	g_landed_parking_space_id = NULL_PARKING_SPACE_ID;

	DisplayLaunchMessage();
	g_ptr2eventHandlingFunction = NULL_PTR;
}

uint8 FindEmptyParkingSpace(void)  // DONE
{
	uint8 parking_space_id = NULL_PARKING_SPACE_ID;
	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		if((g_parking_spaces_data + counter)->busy_parking_space_flag == EMPTY_SPACE)
		{
			parking_space_id = (g_parking_spaces_data + counter)->parking_space_id;
			break;
		}
	}
	return parking_space_id;
}

void RotateGarage(SYSTEM_garageRotationStateType a_garage_rotation_state, uint8 a_parking_space_id)  // DONE
{
	uint64 rotation_steps;
	STEPPER_directionType rotation_direction;

	if(a_parking_space_id != NULL_PARKING_SPACE_ID)
	{
		rotation_steps = (g_parking_spaces_data + a_parking_space_id - 1)->steps_to_gate;
		rotation_direction = (g_parking_spaces_data + a_parking_space_id - 1)->direction_to_gate;
		if(a_garage_rotation_state == ROTATION_TO_HOME) rotation_direction ^= 1;

		DISABLE_GLOBAL_INT();
		STEPPER_rotate(rotation_direction,rotation_steps);
		ENABLE_GLOBAL_INT();
	}
}

void ParkingAssistant(void)  // DONE *
{
	uint16 calculated_distance;

	LED_off(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_GREEN_LED_PIN_ID);
	LED_on(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_RED_LED_PIN_ID);
	ULTRASONIC_init();

	// !!!!!!!!!!!!!!!!!!!!!!!! NOT IDEAL !!!!!!!!!!!!!!!!!!!!!!!!
	do
	{
		calculated_distance = ULTRASONIC_readDistance();
	}while(calculated_distance > PARKING_ASSISTANT_SAFE_DISTANCE);

	LED_off(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_RED_LED_PIN_ID);
	LED_on(PARKING_ASSISTANT_LEDS_PORT_ID,PARKING_ASSISTANT_GREEN_LED_PIN_ID);
}

void CheckUserExit(void)  // DONE
{
	LASER_on();
	_delay_ms(100);
	while(IR_checkState() == IR_RECEIVING);
}

void SYSTEM_checkCarExit(void)
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

uint8 GetParkingSpaceID(uint32 a_card_id)  // DONE
{
	uint8 parking_space_id = NULL_PARKING_SPACE_ID;
	for(uint8 counter = 0; counter < SYSTEM_PARKING_SPACES; counter++)
	{
		if((g_parking_spaces_data + counter)->rfid_card_id == a_card_id)
		{
			parking_space_id = (g_parking_spaces_data + counter)->parking_space_id;
			break;
		}
	}
	return parking_space_id;
}

void OpenGarageGate(void)  // DONE
{
	if(g_last_gate_state == GATE_CLOSED)
	{
		SERVO_init();
		SERVO_setAngle(90);
		g_last_gate_state = GATE_OPEN;
	}
}

void CloseGarageGate(void)  // DONE
{
	if(g_last_gate_state == GATE_OPEN)
	{
		SERVO_init();
		SERVO_setAngle(0);
		g_last_gate_state = GATE_CLOSED;
	}
}
