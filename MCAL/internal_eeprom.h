/*****************************************************************************************************
 * Created	 : 12 - NOV 2022
 * Author	 : Abdullah Khalid
 * Version	 : 01
 * File Name : INTERNAL_EEPROM.h
 ****************************************************************************************************/ 


#ifndef INTERNAL_EEPROM_H_
#define INTERNAL_EEPROM_H_

#include "../OTHERS/std_types.h"

#define DISABLE				0
#define ENABLE				1

#define INTERRUPT_STATE		DISABLE


/* Function Name : MEEPROM_voidInit
 *----------------------------------------------------------------------------------------------------
 * Initializing EEPROM (Determine Interrupt State). 
 *----------------------------------------------------------------------------------------------------
 * Arguments	 : NONE 
 *----------------------------------------------------------------------------------------------------
 * Return Type	 : void (no return).
 *
 ******************************************************************************************************/


void MEEPROM_voidInit(void);

/* Function Name : MEEPROM_voidWrite
 *----------------------------------------------------------------------------------------------------
 * Used to write data to EEPROM. 
 *----------------------------------------------------------------------------------------------------
 * Arguments	 : Copy_u16Adress --------> Adress of EEPROM, where data will be written to.
 *               : Copyu8Data     --------> Data to be written.
 *----------------------------------------------------------------------------------------------------
 * Return Type	 : void (no return).
 *
 ******************************************************************************************************/

void MEEPROM_voidWrite(uint16 Copy_u16Adress , uint8 Copyu8Data);

/* Function Name : MEEPROM_u8Read
 *----------------------------------------------------------------------------------------------------
 * Used to read data from EEPROM. 
 *----------------------------------------------------------------------------------------------------
 * Arguments	 : Copy_u16Adress --------> Adress of EEPROM, where data will be read from.
 *----------------------------------------------------------------------------------------------------
 * Return Type	 : Unsigned character (8 Bits).
 *
 ******************************************************************************************************/

uint8 MEEPROM_u8Read(uint16 Copy_u16Adress);




#endif /* INTERNAL_EEPROM_H_ */
