/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - EXTI_private.h 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#ifndef		_EXTI_PRIVATE_H
#define		_EXTI_PRIVATE_H


#define		EXTI_u8_MCUCR_REG		*((volatile u8*)0x55)		///MCU Control Register          		 //Bit3:ISC11	 Bit2:ISC10	  BIT1:ISC01   BIT0:ISC10

#define 	EXTI_u8_MCUCSR_REG		*((volatile u8*)0x54)		///MCU Control and Status Register		 //BIT6:ISC2

#define 	EXTI_u8_GICR_REG		*((volatile u8*)0x5B)		///General Intrrupt Control Register	 //BIT7:INT1     BIT6:INT0    BIT5:INT2 (Refers to PIE)

#define 	EXTI_u8_GIFR_REG		*((volatile u8*)0x5A)		///General Interrupt Flag Register		 //BIT7:INTF1	 BIT6:INTF2   BIT5:INTF1


#endif
