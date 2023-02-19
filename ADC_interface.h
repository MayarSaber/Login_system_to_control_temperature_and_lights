/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - ADC_interface.h 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef 	_ADC_INTERFACE_H
#define		_ADC_INTERFACE_H

/** Macros for Channel and Gain Selections */
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC0								0
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC1								1
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC2								2
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC3								3
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC4								4
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC5								5
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC6								6
#define		ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC7								7

#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC0_ADC0_x10			8
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC1_ADC0_x10			9
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC0_ADC0_x200			10
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC1_ADC0_x200			11
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC2_ADC2_x10			12
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC3_ADC2_x10			13
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC2_ADC2_x200			14
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_WITH_GAIN_ADC3_ADC2_x200			15
	
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC0_ADC0							16
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC1_ADC0							17
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC2_ADC0							18
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC3_ADC0							19
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC4_ADC0							20
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC5_ADC0							21
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC6_ADC0							22
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC7_ADC0							23
	
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC0_ADC2							24
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC1_ADC2							25
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC2_ADC2							26
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC3_ADC2							27
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC4_ADC2							28
#define		ADC_u8_DIFFERENTIAL_INPUT_CHANNEL_ADC5_ADC2							29
	
#define		ADC_u8_TESTING_CHANNEL_WITH_1.22v									30
#define		ADC_u8_TESTING_CHANNEL_WITH_0v										31

/**Macros for Auto Trigger Resources**/
#define		ADC_u8_TRIGGER_RESOURCE_FREE_RUNNING				0
#define     ADC_u8_TRIGGER_RESOURCE_ANALOG_COMPARATOR			1
#define     ADC_u8_TRIGGER_RESOURCE_EXTI0						2
#define     ADC_u8_TRIGGER_RESOURCE_TIMER0_COMPARE_MATCH		3
#define     ADC_u8_TRIGGER_RESOURCE_TIMER0_OVERFLOW				4
#define     ADC_u8_TRIGGER_RESOURCE_TIMER_COMPARE_MATCH_B		5
#define     ADC_u8_TRIGGER_RESOURCE_TIMER1_OVER_FLOW			6
#define     ADC_u8_TRIGGER_RESOURCE_TIMER1_CAPTURE_EVENT		7


void ADC_voidInit							(void);
u8   ADC_u8GetDigitalValueSynchNonBlocking  (u8 Copy_u8ChannelGainSelection , u16 * Copy_pu16DigitalValue);
u8   ADC_u8GetDigitalValueAsynch			(u8 Copy_u8ChannelGainSelection , void(* Copy_pfNotificationFunc)(u16));
u8 	 ADC_u8_AutoTriggerEnable				(u8 Copy_u8AutoTriggerSource);



#endif
