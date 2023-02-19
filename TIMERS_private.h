/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - TIMERS_private.h			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef 	_TIMERS_PRIVATE_H
#define		_TIMERS_PRIVATE_H

/**********************************************| General |*********************************************/
//-------------------------------------------- REG Macros ----------------------------------------------
#define 	TIMER0_u8_TIMSK_REG		 *((volatile u8 *)0x59)			//Timer/Counter Interrupt Mask Register
#define     TIMER0_u8_TIFR_REG		 *((volatile u8 *)0x58)			//Timer/Counter Interrupt Flag Register

//-------------------------------------------- Pin Macros ----------------------------------------------
//TIMSK_REG_BITS
#define     TIMER0_TIMSK_TOIE0_BIT		0							//Timer0 Overflow Interrupt Enable bit
#define     TIMER0_TIMSK_OCIE0_BIT		1							//Timer0 Output Compare Match Interrupt Enable bit
#define		TIMER1_TIMSK_TOIE1_BIT		2							//Timer1 Overflow Interrupt Enable bit
#define		TIMER1_TIMSK_OCIE1B_BIT		3							//Timer1 Output Compare Match Interrupt Enable B bit
#define		TIMER1_TIMSK_OCIE1A_BIT		4							//Timer1 Output Compare Match Interrupt Enable A bit
#define		TIMER1_TIMSK_TICIE1_BIT		5							//Timer1 Input Capture Interrupt Enable bit
	
//TIFR_REG_BITS	
#define     TIMER0_TIFR_TOV0_BIT		0							//Timer0 overflow flag bit
#define     TIMER0_TIFR_OCF0_BIT		1							//Timer0 Output compare flag bit
#define		TIMER1_TIFR_TOV1_BIT		2							//Timer1 overflow flag bit
#define		TIMER1_TIFR_OCF1B_BIT		3							//Timer1 Output compare flag B bit
#define		TIMER1_TIFR_OCF1A_BIT		4							//Timer0 Output compare flag A bit
#define		TIMER1_TIFR_ICF1_BIT		5							//Timer1 Input Capture Flag bit

/**********************************************| TIMER0 |***********************************************/
//-------------------------------------------- REG Macros ----------------------------------------------
#define 	TIMER0_u8_TCCR0_REG		 *((volatile u8 *)0x53)			//Timer/Counter0 Control Register
#define 	TIMER0_u8_TCNT0_REG		 *((volatile u8 *)0x52)			//Timer/Counter0 Register
#define		TIMER0_u8_OCR0_REG		 *((volatile u8 *)0x5C)			//Timer/Counter0 Output Countrol Register

//-------------------------------------------- Pin Macros ----------------------------------------------
//TCCR0_REG_BITS
#define 	TIMER0_TCCR0_FOC0_BIT	7								//Force Output compare bit
#define 	TIMER0_TCCR0_WGM00_BIT	6								//Wave Generation Mode bit 0
#define 	TIMER0_TCCR0_COM01_BIT	5								//Compare Match Output Mode bit 1
#define 	TIMER0_TCCR0_COM00_BIT	4								//Compare Match Output Mode bit 0
#define 	TIMER0_TCCR0_WGM01_BIT	3								//Wave Generation Mode bit 1
#define 	TIMER0_TCCR0_CS02_BIT	2								//Clock Select bit 2
#define 	TIMER0_TCCR0_CS01_BIT	1								//Clock Select bit 1
#define 	TIMER0_TCCR0_CS00_BIT	0								//Clock Select bit 0

//------------------------------------------ CONFIG Macros ---------------------------------------------
//Macros for Wave Generation Mode
#define		TIMER0_u8_INITIAL_NORMAL_MODE																	00
#define		TIMER0_u8_INITIAL_PWM_PHASE_CORRECT																01
#define		TIMER0_u8_INITIAL_CTC																			10
#define		TIMER0_u8_INITIAL_FAST_PWM																		11
 
//Macros for Clock Selection Initial Value									
#define		TIMER0_u8_INITIAL_NO_CLOCK_SOURCE																000
#define		TIMER0_u8_INITIAL_NO_PRESCALLING					           									001
#define		TIMER0_u8_INITIAL_PRESCALER_8						           									010
#define		TIMER0_u8_INITIAL_PRESCALER_64						           									011
#define		TIMER0_u8_INITIAL_PRESCALER_256						           									100
#define		TIMER0_u8_INITIAL_PRESCALER_1024					           									101
#define		TIMER0_u8_INITIAL_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE           									110
#define		TIMER0_u8_INITIAL_EXTERNAL_CLOCK_SOURCE_RISING_EDGE	           									111

//Macros for Compare Match Output Mode
#define		TIMER0_u8_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC0											 0
#define		TIMER0_u8_INITIAL_NON_PWM_TOGG_OC0_ON_COMPARE_MATCH												 1
#define		TIMER0_u8_INITIAL_NON_PWM_CLR_OC0_ON_COMPARE_MATCH												 2
#define		TIMER0_u8_INITIAL_NON_PWM_SET_OC0_ON_COMPARE_MATCH												 3

#define		TIMER0_u8_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC0										 4
#define		TIMER0_u8_INITIAL_FAST_PWM_REVERSED																 5
#define		TIMER0_u8_INITIAL_FAST_PWM_CLR_OC0_ON_COMPARE_MATCH_SET_OC0_AT_TOP								 6
#define		TIMER0_u8_INITIAL_FAST_PWM_SET_OC0_ON_COMPARE_MATCH_CLR_OC0_AT_TOP								 7

#define		TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC0								 8
#define		TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_REVERSED													 9
#define		TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_CLR_OC0_ON_COMPARE_MATCH_UP_COUNTING_SET_OC0_DOWN_COUNTING   10
#define		TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_SET_OC0_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC0_DOWN_COUNTING   11

//Macros for Interrupt Flag Selection
#define 	TIMER0_u8_INITIAL_OVERFLOW_FLAG			                                                          0
#define 	TIMER0_u8_INITIAL_OUTPUT_COMPARE_FLAG														      1
#define     TIMER0_u8_INITIAL_NO_ENABLED_INTERRUPTS															  2

/**********************************************| TIMER1 |**********************************************/
//-------------------------------------------- REG Macros ----------------------------------------------
#define 	TIMER1_u8_TCCR1A_REG		*((volatile u8 *)0x4F)		//Timer/Counter1 Control Register A
#define 	TIMER1_u8_TCCR1B_REG		*((volatile u8 *)0x4E)		//Timer/Counter1 Control Register B

#define 	TIMER1_u8_TCNT1H_REG		*((volatile u8 *)0x4D)		//Timer/Counter1 Register High
#define 	TIMER1_u16_TCNT1LH_REG		*((volatile u16*)0x4C)		//Timer/Counter1 Register

#define		TIMER1_u8_OCR1AH_REG		*((volatile u8 *)0x4B)		//Timer/Counter1 Output Countrol Register A High
#define		TIMER1_u16_OCR1ALH_REG		*((volatile u16*)0x4A)		//Timer/Counter1 Output Countrol Register A

#define		TIMER1_u8_OCR1BH_REG	    *((volatile u8 *)0x49)		//Timer/Counter1 Output Countrol Register B High
#define		TIMER1_u16_OCR1BLH_REG		*((volatile u16*)0x48)		//Timer/Counter1 Output Countrol Register B

#define	    TIMER1_u8_ICR1H_REG			*((volatile u8 *)0x47)		//Timer/Counter1 Input Capture Register High
#define		TIMER1_u16_ICR1LH_REG		*((volatile u16*)0x46)		//Timer/Counter1 Input Capture Register

//-------------------------------------------- Pin Macros ----------------------------------------------
//TCCR1A_REG_BITS
#define 	TIMER1_TCCR1A_COM1A1_BIT		7						//Compare Match Output Mode bit A1
#define 	TIMER1_TCCR1A_COM1A0_BIT		6						//Compare Match Output Mode bit A0
#define 	TIMER1_TCCR1A_COM1B1_BIT		5						//Compare Match Output Mode bit B1
#define 	TIMER1_TCCR1A_COM1B0_BIT		4						//Compare Match Output Mode bit B0
#define 	TIMER1_TCCR1A_FOC1A_BIT			3						//Force Output compare bit A
#define 	TIMER1_TCCR1A_FOC1B_BIT			2						//Force Output compare bit B
#define 	TIMER1_TCCR1A_WGM11_BIT			1						//Wave Generation Mode bit 1
#define 	TIMER1_TCCR1A_WGM10_BIT			0						//Wave Generation Mode bit 0

//TCCR1B_REG_BITS
#define 	TIMER1_TCCR1B_ICNC1_BIT			7						//Input Capture Noise Canceler Bit
#define 	TIMER1_TCCR1B_ICES1_BIT			6						//Input Capture Edge Select
#define 	TIMER1_TCCR1B_WGM13_BIT			4						//Wave Generation Mode bit 3
#define 	TIMER1_TCCR1B_WGM12_BIT			3                       //Wave Generation Mode bit 2
#define 	TIMER1_TCCR1B_CS12_BIT			2						//Clock Select Bit 2
#define 	TIMER1_TCCR1B_CS11_BIT			1						//Clock Select Bit 1
#define 	TIMER1_TCCR1B_CS10_BIT			0						//Clock Select Bit 0

//------------------------------------------ CONFIG Macros ---------------------------------------------
//Macros for Wave Generation Mode
#define		TIMER1_u16_INITIAL_NORMAL_MODE										0000
#define		TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_8BIT                           0001
#define		TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_9BIT                           0010
#define		TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_10BIT                          0011
#define		TIMER1_u16_INITIAL_CTC_TOP_OCR1A                                    0100
#define		TIMER1_u16_INITIAL_FAST_PWM_8BIT                                    0101
#define		TIMER1_u16_INITIAL_FAST_PWM_9BIT                                    0110
#define		TIMER1_u16_INITIAL_FAST_PWM_10BIT                                   0111
#define		TIMER1_u16_INITIAL_PWM_PHASE_FREQUENCY_CORRECT_TOP_ICR1             1000
#define		TIMER1_u16_INITIAL_PWM_PHASE_FREQUENCY_CORRECT_TOP_OCR1A            1001
#define		TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_TOP_ICR1                       1010
#define		TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_TOP_OCR1A                      1011
#define		TIMER1_u16_INITIAL_CTC_TOP_ICR1                                     1100
#define		TIMER1_u16_INITIAL_RESERVED                                         1101
#define		TIMER1_u16_INITIAL_FAST_PWM_TOP_ICR1                                1110
#define		TIMER1_u16_INITIAL_FAST_PWM_TOP_OCR1A                               1111


//Macros for Clock Selection Initial Value
#define		TIMER1_u16_INITIAL_NO_CLOCK_SOURCE									000
#define		TIMER1_u16_INITIAL_NO_PRESCALLING									001
#define		TIMER1_u16_INITIAL_PRESCALER_8										010
#define		TIMER1_u16_INITIAL_PRESCALER_64										011
#define		TIMER1_u16_INITIAL_PRESCALER_256									100
#define		TIMER1_u16_INITIAL_PRESCALER_1024									101
#define		TIMER1_u16_INITIAL_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE				110
#define		TIMER1_u16_INITIAL_EXTERNAL_CLOCK_SOURCE_RISING_EDGE				111


//Macros for Compare Match Output Mode
//COM1A
#define		TIMER1_u16_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC1A												1
#define		TIMER1_u16_INITIAL_NON_PWM_TOGG_OC1A_ON_COMPARE_MATCH													2
#define		TIMER1_u16_INITIAL_NON_PWM_CLR_OC1A_ON_COMPARE_MATCH													3
#define		TIMER1_u16_INITIAL_NON_PWM_SET_OC1A_ON_COMPARE_MATCH_SET_OUTPUT_TO_HIGH									4
				
#define		TIMER1_u16_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC1A												5
#define		TIMER1_u16_INITIAL_FAST_PWM_WGM13_0_15_TOGG_OC1A_ON_COMPARE_MATCH										6
#define		TIMER1_u16_INITIAL_FAST_PWM_CLR_OC1A_ON_COMPARE_MATCH_SET_OC1A_AT_TOP									7
#define		TIMER1_u16_INITIAL_FAST_PWM_SET_OC1A_ON_COMPARE_MATCH_CLR_OC1A_AT_TOP									8
					
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC1A										13
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_WGM13_0_9_14_TOGG_OC1A_ON_COMPARE_MATCH							14
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_CLR_OC1A_ON_COMPARE_MATCH_UP_COUNTING_SET_OC1A_DOWN_COUNTING		15
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_SET_OC1A_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC1A_DOWN_COUNTING		16

//CIM1B
#define		TIMER1_u16_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC1B												18
#define		TIMER1_u16_INITIAL_NON_PWM_TOGG_OC1B_ON_COMPARE_MATCH													19
#define		TIMER1_u16_INITIAL_NON_PWM_CLR_OC1B_ON_COMPARE_MATCH													21
#define		TIMER1_u16_INITIAL_NON_PWM_SET_OC1B_ON_COMPARE_MATCH_SET_OUTPUT_TO_HIGH									22
				
#define		TIMER1_u16_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC1B												23
#define		TIMER1_u16_INITIAL_FAST_PWM_WGM13_0_15_DIS_OC1B_NORMAL_OPERATION										24
#define		TIMER1_u16_INITIAL_FAST_PWM_CLR_OC1A_ON_COMPARE_MATCH_SET_OC1B_AT_TOP									25
#define		TIMER1_u16_INITIAL_FAST_PWM_SET_OC1A_ON_COMPARE_MATCH_CLR_OC1B_AT_TOP									26
				
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC1B										27
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_WGM13_0_9_14_DIS_OC1B_NORMAL_OPERATION							    28
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_CLR_OC1A_ON_COMPARE_MATCH_UP_COUNTING_SET_OC1B_DOWN_COUNTING		29
#define		TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_SET_OC1A_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC1B_DOWN_COUNTING		30


//Macros for Enabled INTERRUPTS
#define		TIMER1_u16_INITIAL_OVERFLOW_INTERRUPT_ENABLE															0
#define		TIMER1_u16_INITIAL_OUTPUT_COMPARE_A_MATCH_INTERRUPT_ENABLE		                                        1
#define		TIMER1_u16_INITIAL_INPUT_CAPTURE_INTERRUPT_ENABLE				                                        2
#define     TIMER1_u16_INITIAL_NO_ENABLED_INTERRUPTS																3

#endif
