/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - DIO_interface.h			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#ifndef 	_DIO_INTERFACE_H
#define		_DIO_INTERFACE_H

/*Macros for PORTS*/
#define 	DIO_u8_PORTA	0
#define		DIO_u8_PORTB	1
#define		DIO_u8_PORTC	2
#define		DIO_u8_PORTD	3

/*Macros for PINS*/
#define		DIO_u8_PIN0		0
#define		DIO_u8_PIN1		1
#define		DIO_u8_PIN2		2
#define		DIO_u8_PIN3		3
#define		DIO_u8_PIN4		4
#define		DIO_u8_PIN5		5
#define		DIO_u8_PIN6		6
#define		DIO_u8_PIN7		7

/*Macros for Direction*/
#define 	DIO_u8_OUTPUT	1
#define		DIO_u8_INPUT	0

/*Macros for Value*/
#define 	DIO_u8_HIGH		1
#define 	DIO_u8_LOW		0

void DIO_voidInit(void);																			///Function to initiate the directions and the values of all the pins

u8 DIO_u8SetPinDirection  (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8PinDirection);			///Function to specify the direction of a pin whether it's input or output
			
u8 DIO_u8SetPinValue      (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8PinValue);				///Function to specify the value of a pin whether it's high or low
	
u8 DIO_u8GetPinValue      (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 * Copy_pu8ReturnPinValue);		///Function to return the value of a pin whether it's high or low

u8 DIO_u8SetPortDirection (u8 Copy_u8PortId , u8 Copy_u8PortDirection);								///Function to specify the direction of a whole port whether it's input or output

u8 DIO_u8SetPortValue	  (u8 Copy_u8PortId , u8 Copy_u8PortValue);									///Function to specify the value of a whole port whether it's high or low

u8 DIO_u8GetPortValue	  (u8 Copy_u8PortId , u8 * Copy_pu8ReturnPortValue);						///Function to return the value of a whole port whether it's high or low
 
u8 DIO_u8TogglePinValue   (u8 Copy_u8PortId , u8 Copy_u8PinId);										///Function to toggle a certain bit in a port

#endif
