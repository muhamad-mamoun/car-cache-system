/*
===========================================================================================================
Author       : Mamoun
Module       : Common Macros
File Name    : common_macros.h
Date Created : Oct 1, 2022
Description  : Common macros used in the code.
===========================================================================================================
*/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG = (REG) | (1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG = (REG) & (~(1<<BIT)))

/* Write a value (1 or 0) in a certain bit in any register */
#define WRITE_BIT(REG,BIT,VAL) (REG = ((REG & (~(1<<BIT))) | (VAL<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG = (REG) ^ (1<<BIT))

/* Check if a specific bit is set in any register and return non-zero if yes */
#define BIT_IS_SET(REG,BIT) ((REG) & (1<<BIT))

/* Check if a specific bit is cleared in any register and return one if yes */
#define BIT_IS_CLEAR(REG,BIT) (!((REG) & (1<<BIT)))

/* Get the value of a certain bit (1 or 0) in any register */
#define GET_BIT(REG,BIT) (((REG) & (1<<BIT)) ? (1u) : (0u))

/* Rotate right any 8-bit register with a specific number of rotates */
#define ROTATE_R(REG,VAL) ((REG>>VAL) | (REG<<(8-VAL)))

/* Rotate left any 8-bit register with a specific number of rotates */
#define ROTATE_L(REG,VAL) ((REG<<VAL) | (REG>>(8-VAL)))

/* Rotate right any register with any size of bits with a specific number of rotates */
#define ROTATE_R_ANY(REG,VAL,BITS) ((REG>>VAL) | (REG<<(BITS-VAL)))

/* Rotate left any register with any size of bits with a specific number of rotates */
#define ROTATE_L_ANY(REG,VAL,BITS) ((REG<<VAL) | (REG>>(BITS-VAL)))

#endif /* COMMON_MACROS_H_ */
