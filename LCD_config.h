/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - LCD_config.h				 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#ifndef		_LCD_CONFIG_H
#define		_LCD_CONFIG_H

/** Control Port and Dara Port Directions */
/** Options: 
			(1) DIO_u8_PORTA
			(2) DIO_u8_PORTB
			(3) DIO_u8_PORTC
			(4) DIO_u8_PORTD
**/

#define 	LCD_u8_CONTROL_PORT		DIO_u8_PORTD
#define 	LCD_u8_DATA_PORT		DIO_u8_PORTC

/***************************************************/

/** Control Pins Directions */
/** Options: 
			(1) DIO_u8_PIN0
			(2) DIO_u8_PIN1
			(3) DIO_u8_PIN2
			(4) DIO_u8_PIN3
			(5) DIO_u8_PIN4
			(6) DIO_u8_PIN5
			(7) DIO_u8_PIN6
			(8) DIO_u8_PIN7

**/

#define		LCD_u8_RS_PIN			DIO_u8_PIN7
#define		LCD_u8_RW_PIN			DIO_u8_PIN6
#define		LCD_u8_E_PIN			DIO_u8_PIN5

#endif
