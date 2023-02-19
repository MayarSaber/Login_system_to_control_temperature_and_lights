/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - EXTI_interface.h 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#ifndef 	_EXTI_INTERFACE_H
#define		_EXTI_INTERFACE_H


/*Macros for Interrupts*/
#define 	EXTI_u8_INTERRUPT0		0			//on PD2 pin
#define 	EXTI_u8_INTERRUPT1		1			//on PD3 pin
#define 	EXTI_u8_INTERRUPT2		2			//on PB2 pin

/*Macros for Interrupts levels*/
#define 	EXTI_u8_LOW_LEVEL		0
#define 	EXTI_u8_LOGICAL_CHANGE	1
#define 	EXTI_u8_FALLING_EDGE	2
#define 	EXTI_u8_RISING_EDGE		3


u8 EXTI_u8InterruptEnable  (u8 Copy_u8EXTIIndex , u8 Copy_EdgeIndex);			        //Function used to enable a specific interrupt in a specific edge
u8 EXTI_u8InterruptDisable (u8 Copy_u8EXTIIndex);									//Function used to disable a specific interrupt in a specific edge
u8 EXTI_u8SetCallBack      (u8 Copy_u8EXTIIndex , void(*Copy_pf)(void));                  //Function to send the address of the ISR application function to ISR 


#endif
