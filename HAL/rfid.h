/*
===========================================================================================================
Author       : Mamoun
Module       : RFID
File Name    : rfid.h
Date Created : Nov 27, 2022
Description  : Header file for the RFID driver (using UART).
===========================================================================================================
*/


#ifndef HAL_RFID_H_
#define HAL_RFID_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "../OTHERS/std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

#define RFID_CARD_ID_LENGTH                  (20)

/* RFID Registers List */
#define RFID_COMMAND_REG                     (0X01)
#define RFID_TEST_PIN_EN_REG                 (0X33)
#define RFID_SERIAL_SPEED_REG                (0X1F)

/* RFID Commmand List */
#define RFID_IDLE_COMMAND                    (0X00)  /* No action, Cancels current command execution. */
#define RFID_MEM_COMMAND                     (0X01)  /* Stores 25 bytes into the internal buffer.     */
#define RFID_GENERATE_RANDOM_ID_COMMAND      (0X02)  /* Generates a 10-byte random ID number.         */
#define RFID_CALC_CRC_COMMAND                (0X03)  /* Activates the CRC coprocessor.                */
#define RFID_TRANSMIT_COMMAND                (0X04)  /* Transmits data from the FIFO buffer.          */
#define RFID_NO_CMD_CHANGE_COMMAND           (0X07)  /* No command change.                            */
#define RFID_RECEIVE_COMMAND                 (0X08)  /* Activates the receiver circuits.              */
#define RFID_TRANSCEIVE_COMMAND              (0X0C)  /* Transmits data and activates the receiver.    */
#define RFID_SOFT_RESET_COMMAND              (0X0F)  /* Resets the MFRC522.                           */

/*===========================================================================================================
                                       < Shared Global Variables >
===========================================================================================================*/



/*===========================================================================================================
                                       < User-defined Data Types >
===========================================================================================================*/



/*===========================================================================================================
                                         < Function-like Macros >
===========================================================================================================*/



/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/



#endif /* HAL_RFID_H_ */
