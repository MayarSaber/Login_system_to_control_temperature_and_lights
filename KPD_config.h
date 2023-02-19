/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - KPD_config.h	 			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/

#ifndef		_KPD_CONFIG_H
#define		_KPD_CONFIG_H


/** ROWS PINS and COLS PORTS */
/** Options: 
			(1) DIO_u8_PORTA
			(2) DIO_u8_PORTB
			(3) DIO_u8_PORTC
			(4) DIO_u8_PORTD
**/

#define 	KPD_ROW0_PORT	DIO_u8_PORTD
#define 	KPD_ROW1_PORT	DIO_u8_PORTD
#define 	KPD_ROW2_PORT	DIO_u8_PORTD
#define 	KPD_ROW3_PORT	DIO_u8_PORTD
					
#define 	KPD_COL0_PORT	DIO_u8_PORTB
#define 	KPD_COL1_PORT	DIO_u8_PORTB
#define 	KPD_COL2_PORT	DIO_u8_PORTB
#define 	KPD_COL3_PORT	DIO_u8_PORTB



/** ROWS PINS and COLS PINS */
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

#define 	KPD_ROW0_PIN	 DIO_u8_PIN0			/**Configured as OUTPUT_HIGH**/
#define 	KPD_ROW1_PIN     DIO_u8_PIN1
#define 	KPD_ROW2_PIN     DIO_u8_PIN3
#define 	KPD_ROW3_PIN     DIO_u8_PIN4
			
#define 	KPD_COL0_PIN	 DIO_u8_PIN4			/**Configured as INPUT_PULLUP**/
#define 	KPD_COL1_PIN     DIO_u8_PIN5
#define 	KPD_COL2_PIN     DIO_u8_PIN6
#define 	KPD_COL3_PIN     DIO_u8_PIN7



/**Macro for the Keypad Keys structure**/
//NOTE: Multi line macros is made using '\'

#define 	KPD_KEYS		{{'1' , '2' , '3' , '+'},	\
							 {'4' , '5' , '6' , '-'},	\
							 {'7' , '8' , '9' , '*'},   \
							 {'0' , 'E' , 'B' , '%'}}
						 
						 
#endif
