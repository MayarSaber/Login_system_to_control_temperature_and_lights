/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - ADC_program.c 			     ******/
/****** Version : 01		 							 ******/
/**************************************************************/

/*LIB Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL Layer*/
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static void (* ADC_pfNotificationFunction)(u16) = NULL;
static u8 ADC_u8BusyFlag = 0;


void ADC_voidInit(void)
{
	/*Initiate ADMUX VREF and Adjustment Direction*/
	///VREF
	#if ADC_u8_INITIAL_VREF == ADC_u8_VREF_AREF
		CLR_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF1_BIT);
		CLR_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF0_BIT);
	#elif ADC_u8_INITIAL_VREF == ADC_u8_INITIAL_VREF_AVCC
		CLR_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF1_BIT);
		SET_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF0_BIT);
	#elif ADC_u8_INITIAL_VREF == ADC_u8_INITIAL_VREF_Internal 	
		SET_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF1_BIT);
		SET_BIT(ADC_u8_ADMUX_REG , ADC_u8_VREF0_BIT);
	#endif
	
	///Adjustment Direction*/
	#if ADC_u8_INITIAL_ADJUSTMENT_DIRECTION == ADC_u8_INITIAL_RIGHT_ADJUST
		CLR_BIT(ADC_u8_ADMUX_REG , ADC_u8_LEFT_ADJ_BIT);
	#elif ADC_u8_INITIAL_ADJUSTMENT_DIRECTION == ADC_u8_INITIAL_LEFT_ADJUST
		SET_BIT(ADC_u8_ADMUX_REG , ADC_u8_LEFT_ADJ_BIT);
	#endif
	//---------------------------------------------------------------------
	
	///*Disable Auto Trigger*/
	//CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_AUTO_TRIGGER_ENABLE_BIT);
	
	//---------------------------------------------------------------------
	
	/*Prescaler selection*/
	
	#if	ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_02
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_2
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_4
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_8
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_16
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_32
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_64
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#elif ADC_u8_PRESCALER_SELECTION == ADC_u8_PRESCALER_128
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER0_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER1_BIT);
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_PRESCALER2_BIT);
	#endif
	//---------------------------------------------------------------------
	
		/*Enable ADC*/
	SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_ADC_ENABLE_BIT);
	
}

/************************************************************************/

u8   ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelGainSelection , u16 * Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeOutCounter = 0;
	
	if((Copy_u8ChannelGainSelection <= ADC_u8_TESTING_CHANNEL_WITH_0v) && (Copy_pu16DigitalValue != NULL))
	{
		/*Clear ADMUX0:4*/
		ADC_u8_ADMUX_REG &= 0b11100000;
		
		/*Choose Channel and gain*/
		ADC_u8_ADMUX_REG |= Copy_u8ChannelGainSelection;
		
		/*Start Conversion*/
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_START_CONVERSION_BIT);
		
		/*(Wait till flag = 1) && (Uing a time out counter to avoid the blocking state)*/		//Polling
		while((GET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_INTERRUPT_FLAG_BIT)==0) && (Local_u32TimeOutCounter < ADC_u32_TIME_OUT_MAX_VALUE))
		{
			Local_u32TimeOutCounter++;
		}
		
		if(GET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_INTERRUPT_FLAG_BIT)!=0)			//If there are no problems, we'll continue the code
		{
			/*Clear flag -- We've to clear the flag ourselves in the polling mode / In Interrupt mode it's cleared by the HW*/
			CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_INTERRUPT_FLAG_BIT);
			
			/*Read digital output*/
			*Copy_pu16DigitalValue = ADC_u16_ADCLH_REG;
		}
		
		else		//Means that there is a problem in the HW
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/************************************************************************/

u8   ADC_u8GetDigitalValueAsynch(u8 Copy_u8ChannelGainSelection , void(* Copy_pfNotificationFunc)(u16))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	if((Copy_u8ChannelGainSelection <= ADC_u8_TESTING_CHANNEL_WITH_0v) && (Copy_pfNotificationFunc != NULL) && (ADC_u8BusyFlag == 0))
	{
		/*Set Busy Flag*/					//To avoid interrupting ADC conversion by starting a new conversion
		ADC_u8BusyFlag = 1;		
		
		/*Update the global pointer to function with the address of the Notification Function*/
		ADC_pfNotificationFunction = Copy_pfNotificationFunc;
		
		/*Enable Interrupt*/
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_INTERRUPT_ENABLE_BIT);
		
		/*Clear ADMUX0:4*/
		ADC_u8_ADMUX_REG &= 0b11100000;
		
		/*Choose Channel and gain*/
		ADC_u8_ADMUX_REG |= Copy_u8ChannelGainSelection;
		
		/*Start Conversion*/
		SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_START_CONVERSION_BIT);
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/************************************************************************/

/*Prototype of ADC ISR*/
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotificationFunction != NULL)
	{
		/*Clear Busy Flag*/	
		ADC_u8BusyFlag = 0;	
		
		/*Clear PIE of ADC*/
		/*Disable Interrupt*/
		CLR_BIT(ADC_u8_ADCSRA_REG , ADC_u8_INTERRUPT_ENABLE_BIT);
		
		/*Calling Notification Function*/
		ADC_pfNotificationFunction(ADC_u16_ADCLH_REG);
	}
}

/************************************************************************/

u8 ADC_u8_AutoTriggerEnable(u8 Copy_u8AutoTriggerSource)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8AutoTriggerSource <= ADC_u8_TRIGGER_RESOURCE_TIMER1_CAPTURE_EVENT)
	{
		switch(Copy_u8AutoTriggerSource)
		{
			case ADC_u8_TRIGGER_RESOURCE_FREE_RUNNING:				//000
			CLR_BIT(ADC_u8_SFIOR_REG , 5);
			CLR_BIT(ADC_u8_SFIOR_REG , 6);
			CLR_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_ANALOG_COMPARATOR:			//001
			SET_BIT(ADC_u8_SFIOR_REG , 5);
			CLR_BIT(ADC_u8_SFIOR_REG , 6);
			CLR_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_EXTI0:						//010
			CLR_BIT(ADC_u8_SFIOR_REG , 5);
			SET_BIT(ADC_u8_SFIOR_REG , 6);
			CLR_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_TIMER0_COMPARE_MATCH:		//011
			SET_BIT(ADC_u8_SFIOR_REG , 5);
			SET_BIT(ADC_u8_SFIOR_REG , 6);
			CLR_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_TIMER0_OVERFLOW:			//100
			CLR_BIT(ADC_u8_SFIOR_REG , 5);
			CLR_BIT(ADC_u8_SFIOR_REG , 6);
			SET_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_TIMER_COMPARE_MATCH_B:		//101
			SET_BIT(ADC_u8_SFIOR_REG , 5);
			CLR_BIT(ADC_u8_SFIOR_REG , 6);
			SET_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_TIMER1_OVER_FLOW:			//110
			CLR_BIT(ADC_u8_SFIOR_REG , 5);
			SET_BIT(ADC_u8_SFIOR_REG , 6);
			SET_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			case ADC_u8_TRIGGER_RESOURCE_TIMER1_CAPTURE_EVENT:		//111
			SET_BIT(ADC_u8_SFIOR_REG , 5);
			SET_BIT(ADC_u8_SFIOR_REG , 6);
			SET_BIT(ADC_u8_SFIOR_REG , 7);
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	/*Enable ADC Auto Register*/
	SET_BIT(ADC_u8_ADCSRA_REG , ADC_u8_AUTO_TRIGGER_ENABLE_BIT);
	
	return Local_u8ErrorState;
}

/************************************************************************/
