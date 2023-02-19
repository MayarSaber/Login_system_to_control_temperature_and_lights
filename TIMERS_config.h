/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - TIMERS_config.h			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef		_TIMERS_CONFIG_H
#define		_TIMERS_CONFIG_H

//----------------------------------------------------------------------------------------------------
//---------------------------------------------| TIMER0 |---------------------------------------------
//----------------------------------------------------------------------------------------------------
//Wave Generation Mode Choices
//TCCR0_REG_BITS_3_6

/** Options: (1)TIMER0_u8_INITIAL_NORMAL_MODE							00
			 (2)TIMER0_u8_INITIAL_PWM_PHASE_CORRECT						01
			 (3)TIMER0_u8_INITIAL_CTC									10
			 (4)TIMER0_u8_INITIAL_FAST_PWM								11
**/
#define 	TIMER0_u8_INITIAL_WAVE_GENERATION_MODE				TIMER0_u8_INITIAL_FAST_PWM

///----------------------------------------------------------------------------------------------------
// Compare Match Output Mode Choices
//TCCR0_REG_BITS_5_4

/** Options: (1)TIMER0_u8_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC0											00							
			 (2)TIMER0_u8_INITIAL_NON_PWM_TOGG_OC0_ON_COMPARE_MATCH												01
			 (3)TIMER0_u8_INITIAL_NON_PWM_CLR_OC0_ON_COMPARE_MATCH												10
			 (4)TIMER0_u8_INITIAL_NON_PWM_SET_OC0_ON_COMPARE_MATCH												11
			 	
			 (1)TIMER0_u8_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC0										00
			 (2)TIMER0_u8_INITIAL_FAST_PWM_REVERSED																01
			 (3)TIMER0_u8_INITIAL_FAST_PWM_CLR_OC0_ON_COMPARE_MATCH_SET_OC0_AT_TOP								10
			 (4)TIMER0_u8_INITIAL_FAST_PWM_SET_OC0_ON_COMPARE_MATCH_CLR_OC0_AT_TOP								11
			    
			 (1)TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC0								00
			 (2)TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_REVERSED													01
			 (3)TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_CLR_OC0_ON_COMPARE_MATCH_UP_COUNTING_SET_OC0_DOWN_COUNTING	10
			 (4)TIMER0_u8_INITIAL_PHASE_CORRECT_PWM_SET_OC0_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC0_DOWN_COUNTING	11
**/
#define 	TIMER0_u8_INITIAL_COMPARE_MATCH_MODE				TIMER0_u8_INITIAL_FAST_PWM_CLR_OC0_ON_COMPARE_MATCH_SET_OC0_AT_TOP

///----------------------------------------------------------------------------------------------------
//Interrupt flag Choices
//TIMSK_REG_BITS_1_0

/** Options: (1)TIMER0_u8_INITIAL_OVERFLOW_FLAG						0
			 (2)TIMER0_u8_INITIAL_OUTPUT_COMPARE_FLAG				1
			 (3)TIMER0_u8_INITIAL_NO_ENABLED_INTERRUPTS				2
**/
#define 	TIMER0_u8_INITIAL_INTERRUPT_FLAG					TIMER0_u8_INITIAL_OVERFLOW_FLAG

///----------------------------------------------------------------------------------------------------
//Clock Selections Choices
//TCCR0_REG_BITS_2_1_0

/** Options: (1)TIMER0_u8_INITIAL_NO_CLOCK_SOURCE						000
			 (2)TIMER0_u8_INITIAL_NO_PRESCALLING						001
			 (3)TIMER0_u8_INITIAL_PRESCALER_8							010
			 (4)TIMER0_u8_INITIAL_PRESCALER_64							011
			 (5)TIMER0_u8_INITIAL_PRESCALER_256							100
			 (6)TIMER0_u8_INITIAL_PRESCALER_1024						101
			 (7)TIMER0_u8_INITIAL_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE	110
			 (8)TIMER0_u8_INITIAL_EXTERNAL_CLOCK_SOURCE_RISING_EDGE		111
**/
#define 	TIMER0_u8_INITIAL_CLOCK_SELECTION					TIMER0_u8_INITIAL_PRESCALER_8


//----------------------------------------------------------------------------------------------------
//---------------------------------------------| TIMER1 |---------------------------------------------
//----------------------------------------------------------------------------------------------------
//Wave Generation Mode Choices
//TCCR1A_REG_BITS_1_0
//TCCR1B_REG_BITS_4_3

/** Options: (01)TIMER1_u16_INITIAL_NORMAL_MODE										 0000
			 (02)TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_8BIT                           0001
			 (03)TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_9BIT                           0010
			 (04)TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_10BIT                          0011
			 (05)TIMER1_u16_INITIAL_CTC_TOP_OCR1A                                    0100
			 (06)TIMER1_u16_INITIAL_FAST_PWM_8BIT                                    0101
			 (07)TIMER1_u16_INITIAL_FAST_PWM_9BIT                                    0110
			 (08)TIMER1_u16_INITIAL_FAST_PWM_10BIT                                   0111
			 (09)TIMER1_u16_INITIAL_PWM_PHASE_FREQUENCY_CORRECT_TOP_ICR1             1000
			 (10)TIMER1_u16_INITIAL_PWM_PHASE_FREQUENCY_CORRECT_TOP_OCR1A            1001
			 (11)TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_TOP_ICR1                       1010
			 (12)TIMER1_u16_INITIAL_PWM_PHASE_CORRECT_TOP_OCR1A                      1011
			 (13)TIMER1_u16_INITIAL_CTC_TOP_ICR1                                     1100
			 (14)TIMER1_u16_INITIAL_RESERVED                                         1101
			 (15)TIMER1_u16_INITIAL_FAST_PWM_TOP_ICR1                                1110
			 (16)TIMER1_u16_INITIAL_FAST_PWM_TOP_OCR1A                               1111
**/		 
#define 	TIMER1_u16_INITIAL_WAVE_GENERATION_MODE				TIMER1_u16_INITIAL_FAST_PWM_TOP_ICR1
///----------------------------------------------------------------------------------------------------
// Compare Match Output Mode Choices
//TCCR1A_REG_BITS_5_4 (COM1A)

/** Options: (1)TIMER1_u16_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC1A												00							
			 (2)TIMER1_u16_INITIAL_NON_PWM_TOGG_OC1A_ON_COMPARE_MATCH													01
			 (3)TIMER1_u16_INITIAL_NON_PWM_CLR_OC1A_ON_COMPARE_MATCH													10
			 (4)TIMER1_u16_INITIAL_NON_PWM_SET_OC1A_ON_COMPARE_MATCH_SET_OUTPUT_TO_HIGH									11
								
			 (1)TIMER1_u16_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC1A												00
			 (2)TIMER1_u16_INITIAL_FAST_PWM_WGM13_0_15_TOGG_OC1A_ON_COMPARE_MATCH										01
			 (3)TIMER1_u16_INITIAL_FAST_PWM_CLR_OC1A_ON_COMPARE_MATCH_SET_OC1A_AT_TOP									10
			 (4)TIMER1_u16_INITIAL_FAST_PWM_SET_OC1A_ON_COMPARE_MATCH_CLR_OC1A_AT_TOP									11
								
			 (1)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC1A										00
			 (2)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_WGM13_0_9_14_TOGG_OC1A_ON_COMPARE_MATCH							01
			 (3)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_CLR_OC1A_ON_COMPARE_MATCH_UP_COUNTING_SET_OC1A_DOWN_COUNTING		10
			 (4)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_SET_OC1A_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC1A_DOWN_COUNTING		11
**/		
#define 	TIMER1_u16_INITIAL_COMPARE_MATCH_MODE_OC1A				TIMER1_u16_INITIAL_FAST_PWM_CLR_OC1A_ON_COMPARE_MATCH_SET_OC1A_AT_TOP
//TCCR1B_REG_BITS_7_6 (COM1B)

/** Options: (1)TIMER1_u16_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC1B												00							
			 (2)TIMER1_u16_INITIAL_NON_PWM_TOGG_OC1B_ON_COMPARE_MATCH													01
			 (3)TIMER1_u16_INITIAL_NON_PWM_CLR_OC1B_ON_COMPARE_MATCH													10
			 (4)TIMER1_u16_INITIAL_NON_PWM_SET_OC1B_ON_COMPARE_MATCH_SET_OUTPUT_TO_HIGH									11
								
			 (1)TIMER1_u16_INITIAL_FAST_PWM_NORMAL_PORT_OPERATION_DIS_OC1B												00
			 (2)TIMER1_u16_INITIAL_FAST_PWM_WGM13_0_15_DIS_OC1B_NORMAL_OPERATION										01
			 (3)TIMER1_u16_INITIAL_FAST_PWM_CLR_OC1A_ON_COMPARE_MATCH_SET_OC1B_AT_TOP									10
			 (4)TIMER1_u16_INITIAL_FAST_PWM_SET_OC1A_ON_COMPARE_MATCH_CLR_OC1B_AT_TOP									11
								
			 (1)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_NORMAL_PORT_OPERATION_DIS_OC1B										00
			 (2)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_WGM13_0_9_14_DIS_OC1B_NORMAL_OPERATION							    01
			 (3)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_CLR_OC1A_ON_COMPARE_MATCH_UP_COUNTING_SET_OC1B_DOWN_COUNTING		10
			 (4)TIMER1_u16_INITIAL_PHASE_CORRECT_PWM_SET_OC1A_ON_COMPARE_MATCH_UP_COUNTING_CLR_OC1B_DOWN_COUNTING		11
**/	
#define 	TIMER1_u16_INITIAL_COMPARE_MATCH_MODE_OC1B				TIMER1_u16_INITIAL_NON_PWM_NORMAL_PORT_OPERATION_DIS_OC1B
	
///----------------------------------------------------------------------------------------------------
//Interrupt flag Choices
//TIMSK_REG_BITS_1_0

/** Options: (1)TIMER1_u16_INITIAL_OVERFLOW_INTERRUPT_ENABLE								0
			 (2)TIMER1_u16_INITIAL_OUTPUT_COMPARE_A_MATCH_INTERRUPT_ENABLE					1
			 (3)TIMER1_u16_INITIAL_OUTPUT_COMPARE_A_MATCH_INTERRUPT_ENABLE					2
			 (4)TIMER1_u16_INITIAL_INPUT_CAPTURE_INTERRUPT_ENABLE							3			//Will choose that inside the ICU function
			 (5)TIMER1_u16_INITIAL_NO_ENABLED_INTERRUPTS									4
**/
#define 	TIMER1_u8_INITIAL_INTERRUPT_ENABLE					TIMER1_u16_INITIAL_NO_ENABLED_INTERRUPTS	

///----------------------------------------------------------------------------------------------------
//Clock Selections Choices
//TCCR1B_REG_BITS_2_1_0

/** Options: (1)TIMER1_u16_INITIAL_NO_CLOCK_SOURCE						000
			 (2)TIMER1_u16_INITIAL_NO_PRESCALLING						001
			 (3)TIMER1_u16_INITIAL_PRESCALER_8							010
			 (4)TIMER1_u16_INITIAL_PRESCALER_64							011
			 (5)TIMER1_u16_INITIAL_PRESCALER_256						100
			 (6)TIMER1_u16_INITIAL_PRESCALER_1024						101
			 (7)TIMER1_u16_INITIAL_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE	110
			 (8)TIMER1_u16_INITIAL_EXTERNAL_CLOCK_SOURCE_RISING_EDGE	111
**/
#define 	TIMER1_u16_INITIAL_CLOCK_SELECTION					TIMER1_u16_INITIAL_PRESCALER_8	

///----------------------------------------------------------------------------------------------------

#endif
