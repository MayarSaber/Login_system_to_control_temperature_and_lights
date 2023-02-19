/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: BIT_MATH.h			     			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/


#ifndef _BIT_MATH_H
#define _BIT_MATH_H


#define SET_BIT(VAR,BITNO)  (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO)  (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO)  (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO)  (((VAR) >> (BITNO)) & 0x01)			//We shift the register it self to get 1 or 0 and not a number

#define SET_BYTE(VAR,VALUE) (VAR = VALUE)


#endif


