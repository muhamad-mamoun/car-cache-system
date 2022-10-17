/*
===========================================================================================================
Author       : Mamoun
Module       : Standard Types
File Name    : std_types.h
Date Created : Oct 1, 2022
Description  : Common types used in the code.
===========================================================================================================
*/


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef signed char                 sint8;
typedef unsigned char               uint8;
typedef signed short                sint16;
typedef unsigned short              uint16;
typedef signed long                 sint32;
typedef unsigned long               uint32;
typedef signed long long            sint64;
typedef unsigned long long          uint64;
typedef float                       float32;
typedef double                      float64;

typedef unsigned char               bool;

#ifndef TRUE
#define TRUE                        (0X01u)
#endif

#ifndef FALSE
#define FALSE                       (0X00u)
#endif

#ifndef HIGH
#define HIGH                        (0X01u)
#endif

#ifndef LOW
#define LOW                         (0X00u)
#endif

#ifndef NULL_PTR
#define NULL_PTR                    ((void*)0)
#endif

#endif /* STD_TYPES_H_ */
