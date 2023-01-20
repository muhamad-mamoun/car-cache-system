/*
===========================================================================================================
Project      : Car-Cache System
File Name    : car_cache_system.c
Date Created : Jan 1, 2023
Description  : Vertical Rotary Car Parking System.
===========================================================================================================
*/


#ifndef APP_CAR_CACHE_SYSTEM_H_
#define APP_CAR_CACHE_SYSTEM_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../HAL/ir.h"
#include "../HAL/led.h"
#include "../HAL/lcd.h"
#include "../HAL/rfid.h"
#include "../HAL/servo.h"
#include "../HAL/laser.h"
#include "../HAL/buzzer.h"
#include "../HAL/ultrasonic.h"
#include "../HAL/stepper_motor.h"
#include "../MCAL/external_interrupts.h"
#include "../MCAL/internal_eeprom.h"
#include "../MCAL/timer0.h"
#include "../MCAL/gpio.h"
#include "../OTHERS/std_types.h"
#include "../OTHERS/common_macros.h"
#include <util/delay.h>
#include <avr/io.h>

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define SYSTEM_PARKING_SPACES                    (6)
#define PARKING_SPACES_DATA_ADDRESS              (0x000)

#define NULL_PARKING_SPACE_ID           0

#define PARKING_ASSISTANT_LEDS_PORT_ID           (PORTB_ID)
#define PARKING_ASSISTANT_RED_LED_PIN_ID         (PIN7_ID)
#define PARKING_ASSISTANT_GREEN_LED_PIN_ID       (PIN6_ID)
#define RFID_LEDS_PORT_ID                          (PORTB_ID)
#define RFID_RED_LED_PIN_ID                      (PIN7_ID)
#define RFID_GREEN_LED_PIN_ID                    (PIN6_ID)
#define PARKING_ASSISTANT_SAFE_DISTANCE          (10)
#define DISTANCE_FROM_SENSOR_TO_GATE             (10)
#define WAITING_TIME_TO_CLOSE_GATE               (5000)
#define ALLOWED_NUMBER_OF_DENIED_ACCESSES          (3)
#define NUMBER_OF_COMPARE_MATCH_PER_SECONDS       (62)

/*===========================================================================================================
                                       < Shared Global Variables >
===========================================================================================================*/



/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/

typedef enum
{
	EMPTY_SPACE,BUSY_SPACE
}SYSTEM_parkingSpaceStateType;

typedef enum
{
	GATE_CLOSED,GATE_OPEN
}SYSTEM_gateStateType;

typedef struct
{
	uint8 parking_space_id;
	sint32 rfid_card_id;
	uint64 steps_to_gate;
	STEPPER_directionType direction_to_gate;
	SYSTEM_parkingSpaceStateType busy_parking_space_flag;
}SYSTEM_parkingSpaceDataType;

typedef enum
{
	ROTATION_TO_GATE,ROTATION_TO_HOME
}SYSTEM_garageRotationStateType;

typedef enum
{
	ACCESS_DENIED,ACCESS_GRANTED
}SYSTEM_AccessStateType;

/*===========================================================================================================
                                         < Function-like Macros >
===========================================================================================================*/

#define ClearPreviousMessages() LCD_clearRow(2);LCD_clearRow(3)

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


void SYSTEM_init(void);

void SystemTimeHandling(void);

void DisplayLaunchMessage(void);

void FetchParkingSpacesData(void);

void UpdateParkingSpaceData(uint8 a_parking_space_id, SYSTEM_parkingSpaceStateType a_busy_parking_space_flag);

void ActivateInsertCarEvent(void);

void InsertCarEvent(void);

void ActivateRetrieveCarEvent(void);

void RetrieveCarEvent(void);

void ActivateReturnHomeEvent(void);

void ReturnHomeEvent(void);

SYSTEM_AccessStateType ValidateUserAccess(uint8* a_parking_space_id_ptr);

void AccessGrantedHandling(void);

void AccessDeniedHandling(uint8 a_scanned_card_id);

uint8 FindEmptyParkingSpace(void);

void RotateGarage(SYSTEM_garageRotationStateType a_garage_rotation_state, uint8 a_parking_space_id);

void ParkingAssistant(void);

void CheckUserExitGarage(void);

void CheckCarExitGarage(void);

uint8 GetParkingSpaceID(uint32 a_card_id);

void OpenGarageGate(void);

void CloseGarageGate(void);






#endif /* APP_CAR_CACHE_SYSTEM_H_ */
