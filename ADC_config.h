/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - ADC_config.h 			     ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef 	_ADC_CONFIG_H
#define		_ADC_CONFIG_H

#define 	ADC_u32_TIME_OUT_MAX_VALUE		50000


//ADMUX REG
//---------
/** Initial Values for VREF */
/** Options: 
			(1) ADC_u8_INITIAL_VREF_AREF
			(2) ADC_u8_INITIAL_VREF_AVCC
			(3) ADC_u8_INITIAL_VREF_Internal
**/
#define 	ADC_u8_INITIAL_VREF						ADC_u8_INITIAL_VREF_AVCC


/** Initial Values for Adjustment direction */
/** Options: 
			(1) ADC_u8_INITIAL_RIGHT_ADJUST
			(2) ADC_u8_INITIAL_LEFT_ADJUST
**/
#define     ADC_u8_INITIAL_ADJUSTMENT_DIRECTION		ADC_u8_INITIAL_RIGHT_ADJUST 	   	

//-----------------------------------------------------------------------------------------------------
//ADCSRA REG
//----------
/** Prescaler Selections Choices*/
/** Options:
			(01) ADC_u8_PRESCALER_02
			(02) ADC_u8_PRESCALER_2
            (03) ADC_u8_PRESCALER_4
            (04) ADC_u8_PRESCALER_8
            (05) ADC_u8_PRESCALER_16
            (06) ADC_u8_PRESCALER_32
            (07) ADC_u8_PRESCALER_64
 		   	(08) ADC_u8_PRESCALER_128
**/
#define     ADC_u8_PRESCALER_SELECTION		ADC_u8_PRESCALER_64
			
                
#endif
