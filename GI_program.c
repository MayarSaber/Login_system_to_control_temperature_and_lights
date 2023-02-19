/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - GI_program.c	 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
/*LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "GI_interface.h"
#include "GI_private.h"

void GI_voidEnable(void)
{
	SET_BIT(SREG , 7);
}

void GI_voidDisable(void)
{
	CLR_BIT(SREG , 7);
}
