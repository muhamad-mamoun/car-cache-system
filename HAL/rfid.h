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
#define RFID_COMMAND_REG                     (0x01) /* Starts and stops command execution.            */
#define RFID_COMIEN_REG                      (0x02) /* Enable/Disable interrupt request control bits. */
#define RFID_DIVIEN_REG                      (0x03) /* Enable/Disable interrupt request control bits. */
#define RFID_COMIRQ_REG                      (0x04) /* Interrupt request bits.                        */
#define RFID_DIVIRQ_REG                      (0x05) /* Interrupt request bits.                        */
#define RFID_ERROR_REG                       (0x06) /* Error status of the last command executed.     */
#define RFID_STATUS1_REG                     (0x07) /* Communication status bits.                     */
#define RFID_STSTUS2_REG                     (0x08) /* Receiver and transmitter status bits.          */
#define RFID_CONTROL_REG                     (0x0C) /* Miscellaneous control registers.               */
#define RFID_FIFO_DATA_REG                   (0x09) /* Input and output of 64 byte FIFO buffer.       */
#define RFID_FIFO_LEVEL_REG                  (0x0A) /* Number of bytes stored in the FIFO buffer.     */
#define RFID_WATER_LEVEL_REG                 (0x0B) /* Level of FIFO underflow and overflow warning.  */
#define RFID_BIT_FRAMING_REG                 (0x0D) /* Adjustments for bit-oriented frames.           */
#define RFID_TEST_PIN_EN_REG                 (0X33) /* Selects the speed of the UART interface.       */
#define RFID_SERIAL_SPEED_REG                (0X1F) /* Disable the MX and DTRQ signals.               */

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
                                       < User-defined Data Types >
===========================================================================================================*/



/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/



#endif /* HAL_RFID_H_ */
