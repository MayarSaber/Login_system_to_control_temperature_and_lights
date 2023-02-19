/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - LCD_interface.h			 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#ifndef		_LCD_INTERFACE_H
#define		_LCD_INTERFACE_H


/*Macros for line number*/
#define 	LCD_u8_LINE_ONE		1
#define 	LCD_u8_LINE_TWO		2


/*Macros for special character number*/
#define 	LCD_u8_SPECIAL_CHAR0		0
#define		LCD_u8_SPECIAL_CHAR1		1
#define		LCD_u8_SPECIAL_CHAR2		2
#define		LCD_u8_SPECIAL_CHAR3		3
#define		LCD_u8_SPECIAL_CHAR4		4
#define		LCD_u8_SPECIAL_CHAR5		5
#define		LCD_u8_SPECIAL_CHAR6		6
#define		LCD_u8_SPECIAL_CHAR7		7


/*Moving Direction*/
#define		LCD_u8MoveLeft		0
#define		LCD_u8MoveRight		1


void 	LCD_voidInit(void);																		///Function used to iniate the LCD
												
void 	LCD_voidSendCmnd(u8 Copy_u8Cmnd);		    												///Function used to send command to the LCD
												
void 	LCD_voidSendChar(u8 Copy_u8Char);															///Function used to send char to the LCD			
				
void 	LCD_voidSendString(u8 * Copy_pu8String);													///Function used to send string to the LCD
				
void 	LCD_voidSendNum(u32 Copy_u32Num);															///Function used to send number to the LCD
				
u8 		LCD_u8GoToXY(u8 Copy_u8LineNum , u8 Copy_u8Location);										///Function used to select the vale of the AC at the beginning of the program
				
void 	LCD_voidClearScreen(void);																	///Function used to create the display screen
			
u8 		LCD_u8CreateSpecialChar(u8 Copy_u8SpecialCharNum , u8 * Copy_pu8Pattern);  					///Function used to create a new special character

u8 		LCD_u8SendSpecialChar(u8 Copy_u8SpecialCharNum , u8 Copy_u8LineNum , u8 Copy_u8Location);	///Function used to send a special character to the LCD

void	LCD_u8_MoveCursor(u8 Copy_MovingDirection);													///Function used to move the cursor right or left

void	LCD_u8_MoveScreen(u8 Copy_MovingDirection);													///Function used to move the screen right or left

u8 		LCD_u8GoToXY_CGRAM(u8 Copy_u8LineNum , u8 Copy_u8Location);									///Function used to select the vale of the AC at the beginning of the program
#endif
