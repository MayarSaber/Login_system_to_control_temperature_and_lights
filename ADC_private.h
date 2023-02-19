/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - ADC_private.h 			     ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef 	_ADC_PRIVATE_H
#define		_ADC_PRIVATE_H


#define 	ADC_u8_ADMUX_REG			*((volatile u8 *)0x27)			///ADC Multiplexer Selection Register
#define 	ADC_u8_ADCSRA_REG			*((volatile u8 *)0x26)			///ADC Control and Status Register A
#define		ADC_u8_ADCL_REG				*((volatile u8 *)0x24)	    	///ADC Data Register HIGH
#define		ADC_u8_ADCH_REG				*((volatile u8 *)0x25)		    ///ADC Data Register LOW
#define		ADC_u16_ADCLH_REG			*((volatile u16*)0x24)			///To read both ADCL and ADCH in one step
#define 	ADC_u8_SFIOR_REG			*((volatile u8 *)0x50)			///Special Function IO Register

//-------------------------------------------------------------------------------
/*ADMUX bits*/
#define 	ADC_u8_VREF1_BIT				7
#define 	ADC_u8_VREF0_BIT				6
#define		ADC_u8_LEFT_ADJ_BIT				5


/*ADCSRA bits*/
#define     ADC_u8_ADC_ENABLE_BIT			7
#define 	ADC_u8_START_CONVERSION_BIT		6
#define 	ADC_u8_AUTO_TRIGGER_ENABLE_BIT	5
#define		ADC_u8_INTERRUPT_FLAG_BIT		4
#define		ADC_u8_INTERRUPT_ENABLE_BIT		3
#define		ADC_u8_PRESCALER2_BIT			2
#define		ADC_u8_PRESCALER1_BIT			1
#define		ADC_u8_PRESCALER0_BIT			0
//-------------------------------------------------------------------------------

/*ADMUX REG*/
/** Macros for VREF initial value **/
#define		ADC_u8_INITIAL_VREF_AREF										00 	   	
#define		ADC_u8_INITIAL_VREF_AVCC		   								01
#define		ADC_u8_INITIAL_VREF_Internal	 								11	
						
/** Macros for Adjustment initial Direction **/						
#define 	ADC_u8_INITIAL_RIGHT_ADJUST 	 								0
#define 	ADC_u8_INITIAL_LEFT_ADJUST 		 								1
						
/*ADCSRA REG*/
/**Macros for Channel and Gain Selections**/
#define		ADC_u8_PRESCALER_02 			0
#define		ADC_u8_PRESCALER_2				1
#define		ADC_u8_PRESCALER_4				2
#define		ADC_u8_PRESCALER_8				3
#define		ADC_u8_PRESCALER_16				4
#define		ADC_u8_PRESCALER_32				5
#define		ADC_u8_PRESCALER_64				6
#define		ADC_u8_PRESCALER_128			7




















/**REGISTERS DISCRIPTION**/
/**1-ADMUX**/
/*ADMUX		7:REFS1 6:REFS0 		0 0   	voltage reference = AREF -->pin 32  (Can be any value)
									0 1   	voltage reference = AVCC -->pin 30  (Same voltage on VCC but with a capacitor)
									1 0   	Reserved (NO ACTION)
									1 1   	voltage reference = Internal 2.56v  (With external capacitor at AREF pin)
										
			5: ADLAR				0	  	Disable Left Adjustment
									1	  	Enable Left Adjustment
			
			4:0 MUX					00000	Single-Ended-Input ADC0
									00001   Single-Ended-Input ADC1
									00010   Single-Ended-Input ADC2
									00011   Single-Ended-Input ADC3
									00100   Single-Ended-Input ADC4
									00101   Single-Ended-Input ADC7
									00110   Single-Ended-Input ADC6
									00111   Single-Ended-Input ADC7
									
									
									
									01000	Differential-Input-With-Gain	ADC0	ADC0 (x10)  --> on the same pin to calculte noise
									01001   Differential-Input-With-Gain	ADC1	ADC0 (x10)
											
									01010   Differential-Input-With-Gain	ADC0	ADC0 (x200) --> on the same pin to calculte noise
									01011   Differential-Input-With-Gain	ADC1	ADC0 (x200)
									
									01100	Differential-Input-With-Gain	ADC2	ADC2 (x10)  --> on the same pin to calculte noise	
									01101   Differential-Input-With-Gain	ADC3	ADC2 (x10)
									
									01110	Differential-Input-With-Gain	ADC2	ADC2 (x200) --> on the same pin to calculte noise
									01111   Differential-Input-With-Gain	ADC3	ADC2 (x200)
									
									
									
									10000	Differential-Input		ADC0	ADC0
									10001	Differential-Input		ADC1	ADC0
									10010	Differential-Input		ADC2	ADC0
									10011	Differential-Input		ADC3	ADC0
									10100	Differential-Input		ADC4	ADC0
									10101	Differential-Input		ADC5	ADC0
									10110	Differential-Input		ADC6	ADC0
									10111	Differential-Input		ADC7	ADC0
									
									11000	Differential-Input		ADC0	ADC2
									11001	Differential-Input      ADC1	ADC2
									11010	Differential-Input      ADC2	ADC2
									11011	Differential-Input      ADC3	ADC2
									11100	Differential-Input      ADC4	ADC2
									11101	Differential-Input		ADC5	ADC2
									
									
									
						            11110	FOR TESTING WITH 1.22v
									11111	FOR TESTING WITH 0v
*/
/**2-ADCSRA**/
/*
			7:ADEN  -> ADC Enable						
														0  Disable
														1  Enable
			6:ADSC  -> ADC Start Conversion
														0  
														1  Start Conversion
			5:ADATE -> ADC Auto Trigger Enable			
														0
														1  Enable Auto trigger (Trigger source from SFIOR Register)
			4:ADIF  -> ADC Interrupt Flag				
														0  Cleared by the hardware when using interrupt / We need to clear it ourselves when using polling (Set 1)
														1  Set by the hardware when ADC finishes its work
			3:ADIE  -> ADC Interrupt Enable				
														0  Disable interrupt in ADC
														1  Enable interrupt in ADC
			2:0 ADPS-> ADC Prescaler Select
														000		2
														001		2
														010		4
														011		8
														100		16
														101		32
														110		64
														111		128

*/
/**3-SFIO**/
/*
			5:7 ADTS-> ADC Auto Trigger Resource		000		Free Running Mode
														001		Analog Comparator
														010		External Interrupt/Request0
														011		Timer/Counter0 Compare Match
														100		Timer/Counter0 Overflow
														101		Timer/Counter Compare Match B
														110		Timer/Counter1 Overflow
														111		Timer/Counter1 Capture Event

*/

#endif
