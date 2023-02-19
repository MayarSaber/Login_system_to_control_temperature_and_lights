/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - EXTI_program.c 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
/*LIB Layer*/
#include	"STD_TYPES.h"
#include	"BIT_MATH.h"

/*MCAL - EXTI*/
#include	"EXTI_interface.h"
#include	"EXTI_private.h"
#include	"EXTI_config.h"

/*Global pointer to function*/
///void (* EXTI_pfEXTI0_Func)(void);		//TO hold the address of the application that's needed to be passed to ISR of EXTI0
///void (* EXTI_pfEXTI1_Func)(void);		//TO hold the address of the application that's needed to be passed to ISR of EXTI1
///void (* EXTI_pfEXTI2_Func)(void);		//TO hold the address of the application that's needed to be passed to ISR of EXTI2

static void(*EXTI_ApfEXTI[3])(void) = {NULL , NULL , NULL};	//Array of pointers to function to hold the address of the applications that's needed to be passed to ISR of EXTI0/1/2



u8 EXTI_u8SetCallBack(u8 Copy_u8EXTIIndex , void(*Copy_pf)(void))
/**Function to send the address of the ISR application function to ISR**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_u8EXTIIndex <= EXTI_u8_INTERRUPT2) && (Copy_pf != NULL))
	{
		EXTI_ApfEXTI[Copy_u8EXTIIndex] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/***************************************************************************/

u8 EXTI_u8InterruptEnable(u8 Copy_u8EXTIIndex , u8 Copy_EdgeIndex)
/**Function used to enable a specific interrupt in a specific edge**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	switch(Copy_EdgeIndex)
	{
		case EXTI_u8_LOW_LEVEL:
		switch(Copy_u8EXTIIndex)
		{
			case EXTI_u8_INTERRUPT0:
			CLR_BIT(EXTI_u8_MCUCR_REG , 0);			// Select Edge source => Low Level ISC01 ISC00  --> 0 0
			CLR_BIT(EXTI_u8_MCUCR_REG , 1);
			
			SET_BIT(EXTI_u8_GICR_REG , 6);			//Enable EXTI0 => PIE INT0 --> 1
			break;
			
			case EXTI_u8_INTERRUPT1:
			CLR_BIT(EXTI_u8_MCUCR_REG , 2);			// Select Edge source => Low Level ISC11 ISC10  --> 0 0
			CLR_BIT(EXTI_u8_MCUCR_REG , 3);
			
			SET_BIT(EXTI_u8_GICR_REG , 7);			//Enable EXTI1 => PIE INT1 --> 1
			break;
			
			case EXTI_u8_INTERRUPT2:
			Local_u8ErrorState = STD_TYPES_NOK;	//Low level isn't applicable in INT2
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
		break;
		
		
		case EXTI_u8_LOGICAL_CHANGE:
		switch(Copy_u8EXTIIndex)
		{
			case EXTI_u8_INTERRUPT0:
			SET_BIT(EXTI_u8_MCUCR_REG , 0);			// Select Edge source => Logical Change ISC01 ISC00  --> 0 1
			CLR_BIT(EXTI_u8_MCUCR_REG , 1);
			
			SET_BIT(EXTI_u8_GICR_REG , 6);			//Enable EXTI0 => PIE INT0 --> 1
			break;
			
			case EXTI_u8_INTERRUPT1:
			SET_BIT(EXTI_u8_MCUCR_REG , 2);			// Select Edge source => Low Level ISC11 ISC10  --> 0 1
			CLR_BIT(EXTI_u8_MCUCR_REG , 3);
			
			SET_BIT(EXTI_u8_GICR_REG , 7);			//Enable EXTI1 => PIE INT1 --> 1
			break;
			
			case EXTI_u8_INTERRUPT2:				//Logical change isn't applicable in INT2
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
		break;
		
	
		case EXTI_u8_FALLING_EDGE:
		switch(Copy_u8EXTIIndex)
		{
			case EXTI_u8_INTERRUPT0:
			CLR_BIT(EXTI_u8_MCUCR_REG , 0);			// Select Edge source => Falling Edge ISC01 ISC00  --> 1 0
			SET_BIT(EXTI_u8_MCUCR_REG , 1);
			
			SET_BIT(EXTI_u8_GICR_REG , 6);			//Enable EXTI0 => PIE INT0 --> 1
			break;
			
			case EXTI_u8_INTERRUPT1:
			CLR_BIT(EXTI_u8_MCUCR_REG , 2);			// Select Edge source => Falling Edge ISC11 ISC10  --> 1 0
			SET_BIT(EXTI_u8_MCUCR_REG , 3);
			
			SET_BIT(EXTI_u8_GICR_REG , 7);			//Enable EXTI1 => PIE INT1 --> 1
			break;
			
			case EXTI_u8_INTERRUPT2:
			CLR_BIT(EXTI_u8_MCUCSR_REG , 6);		// Select Edge source => Falling Edge ISC2  --> 0
			
			SET_BIT(EXTI_u8_GICR_REG , 5);			//Enable EXTI2 => PIE INT2 --> 1
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
		break;
		
		
		case EXTI_u8_RISING_EDGE:
		switch(Copy_u8EXTIIndex)
		{
			case EXTI_u8_INTERRUPT0:
			SET_BIT(EXTI_u8_MCUCR_REG , 0);			// Select Edge source => Raising Edge ISC01 ISC00  --> 1 1
			SET_BIT(EXTI_u8_MCUCR_REG , 1);
			
			SET_BIT(EXTI_u8_GICR_REG , 6);			//Enable EXTI0 => PIE INT0 --> 1
			break;
			
			case EXTI_u8_INTERRUPT1:
			SET_BIT(EXTI_u8_MCUCR_REG , 2);			// Select Edge source => Raising Edge ISC11 ISC10  --> 1 1
			SET_BIT(EXTI_u8_MCUCR_REG , 3);
			
			SET_BIT(EXTI_u8_GICR_REG , 7);			//Enable EXTI1 => PIE INT1 --> 1
			break;
			
			case EXTI_u8_INTERRUPT2:
			SET_BIT(EXTI_u8_MCUCSR_REG , 6);		// Select Edge source => Raising Edge ISC2  --> 0
			
			SET_BIT(EXTI_u8_GICR_REG , 5);			//Enable EXTI2 => PIE INT2 --> 1
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
		break;
		
		default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}
	
	return Local_u8ErrorState;
}

/***************************************************************************/

u8 EXTI_u8InterruptDisable(u8 Copy_u8EXTIIndex)
/**Function used to disable a specific interrupt**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8EXTIIndex)
	{
		case EXTI_u8_INTERRUPT0:
		CLR_BIT(EXTI_u8_GICR_REG , 6);		//Disable EXTI0 => PIE INT2 --> 0
		break;
		
		case EXTI_u8_INTERRUPT1:
		CLR_BIT(EXTI_u8_GICR_REG , 7);		//Disable EXTI1 => PIE INT2 --> 0
		break;
		
		case EXTI_u8_INTERRUPT2:			//Disable EXTI2 => PIE INT2 --> 0
		CLR_BIT(EXTI_u8_GICR_REG , 5);
		break;
		
		default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}
	return Local_u8ErrorState;
}

/***************************************************************************/

void __vector_1(void)		__attribute__((signal));	/**ISR function of the EXTI0**/
void __vector_1(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INTERRUPT0] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INTERRUPT0]();
	}
	
}

/***************************************************************************/

void __vector_2(void)		__attribute__((signal));	/**ISR function of the EXTI1**/
void __vector_2(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INTERRUPT1] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INTERRUPT1]();
	}
	
}

/***************************************************************************/

void __vector_3(void)		__attribute__((signal));	/**ISR function of the EXTI2**/
void __vector_3(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INTERRUPT2] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INTERRUPT2]();
	}
}
