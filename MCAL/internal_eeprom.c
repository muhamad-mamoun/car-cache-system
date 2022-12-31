/***********************************************************************
 * Created	 : 12 - NOV 2022
 * Author	 : Abdullah Khalid
 * Version	 : 01
 * File Name : INTERNAL_EEPROM.c
 **********************************************************************/

#include "internal_eeprom.h"
#include "../MCAL/gpio.h"
#include "../OTHERS/common_macros.h"
#include <avr/io.h>

void MEEPROM_voidInit(void)
{
#if		INTERRUPT_STATE == ENABLE

	SET_BIT(EECR,3);

#elif	INTERRUPT_STATE == DISABLE

	CLEAR_BIT(EECR,3);

#endif
}

void MEEPROM_voidWrite(uint16 Copy_u16Adress , uint8 Copyu8Data)
{
	// Disable Interrupts to avoid data corruption,because this is a critical section.
	static uint8 Localu8_Global_interrupt_flag = 0;
	if(GET_BIT(SREG,7))
	{
		Localu8_Global_interrupt_flag = 1;
		CLEAR_BIT(SREG,7);
	}

	// Wait for flag to be zero to verify that there isn't any other operations.
	while(GET_BIT(EECR,1));

	// Write data to buffer register.
	EEDR = Copyu8Data;

	// write address of data to address buffer register.
	EEAR = Copy_u16Adress;

	// Enable master write bit.
	SET_BIT(EECR,2);

	// Set EEWE bit to start writing to EEPROM
	SET_BIT(EECR,1);

	// Re_enable Global Interrupt in case it was activated.
	if(Localu8_Global_interrupt_flag == 1)
	{
		Localu8_Global_interrupt_flag = 0;
		SET_BIT(SREG,7);
	}
}

uint8 MEEPROM_u8Read(uint16 Copy_u16Adress)
{
	// Wait for flag to be zero to verify that there isn't any other operations.
	while(GET_BIT(EECR,1));

	// write address of data to address buffer register.
	EEAR = Copy_u16Adress;

	// Set EERE bit to start reading from EEPROM
	SET_BIT(EECR,0);

	// Return data from data register			
	return EEDR;
}
