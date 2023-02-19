/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - LCD_program.c				 ******/
/****** Version : 01		 							 ******/
/**************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>

/*LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void LCD_voidInit(void)
/**Function used to iniate the LCD**/
{
	//Wait more than 30ms
	_delay_ms(35);
	
	/*Function Set Command 0b001DLNF00 --> where:
												 DL:Sets interface data length
												   DL=0 --> 4 bit length (D4 - D7)
												   DL=1 --> 8 bit length (D0 - D7)
												
												 N:Sets the number of lines
												   N=0  --> 1 line display (1/8 duty)
												   N=1  --> 2 line display (1/16 duty)
												   
												 F:Sets character font
												   F=0  --> 5x7 dots
												   F=1  --> 5x10 dots
												   */
												   
	LCD_voidSendCmnd(0b00111000);			    ///DL=1 -- N=1 -- F=0
	
	//Wait more than 39us
	_delay_us(40);
	
	/*Display ON/OFF control 0b00001DCB -->where:
												 D: Controls the entire data display
													D=1 --> Display is ON
													D=0 --> Display is OFF (The display data remains in DDRAM)
													
												 C: Controls cursor display
													C=0 --> The cursor doesn't displays
													C=1 --> The cursor displays(Displays in 8th line when 5X7dot display is used )
													
												 B: Controls cursor blinking
													B=0 --> The blink is off
													B=1 --> The blink is on 
												 */
												 
	LCD_voidSendCmnd(0b00001111);			    ///D=1 -- C=0 -- B=0
	
	//Wait more than 39us
	_delay_us(40);
	
	
	/*Display clear 0b00000001		    -->Used to clear any thing on the display*/
	LCD_voidSendCmnd(0b00000001);
	
	//Wait more than 1.53ms
	_delay_us(1535);
	
	/*Entry Mode Set 0b000001I/DSH		-->where:
												 I/D: Sets the move direction of the cursor
													  I/D=0 --> Decreases the DDRAM address by 1
													  I/D=1 --> Increases (default)
													  
												 S  : Shifts the entire display
													  S=1 	--> Shifts the desplay (To left --> if I/D = 1 (moves to right) // To right --> if I/D = 0 (moves to left))
													  S=0   --> Display does not shift
													  */
													  
	LCD_voidSendCmnd(0b00000110);			    ///I/D=1 -- S=0
}

/*************************************************************************************/

void LCD_voidSendCmnd(u8 Copy_u8Cmnd)
/**Function used to send command to the LCD**/
{
	/*RS = 0*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_RS_PIN , DIO_u8_LOW);			//Depending on which port and which pin we used for RS pin, we set the values of PORT & PIN in config file
	
	/*R/W = 0*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_RW_PIN , DIO_u8_LOW);			//Depending on which port and which pin we used for R/W pin, we set the values of PORT & PIN in config file
	
	/*Write cmnd*/
	DIO_u8SetPortValue(LCD_u8_DATA_PORT , Copy_u8Cmnd);								//Depending on which port we used for pins D0 - D7, we set the values of PORT in config file
	
	/*E = 1*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_E_PIN , DIO_u8_HIGH);			//Depending on which port and which pin we used for E pin, we set the values of PORT & PIN in config file
	
	_delay_us(1);		///From LCD data sheet, E pulse width tw --> min = 230ns -->we can't use 0.23us(no fractions)
	
	/*E = 0*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_E_PIN , DIO_u8_LOW);				//Depending on which port and which pin we used for E pin, we set the values of PORT & PIN in config file
}

/*************************************************************************************/

void LCD_voidSendChar(u8 Copy_u8Char)
/**Function used to send char to the LCD**/
{
	/*RS = 1*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_RS_PIN , DIO_u8_HIGH);		    //Depending on which port and which pin we used for RS pin, we set the values of PORT & PIN in config file
    
    /*R/W = 0*/
    DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_RW_PIN , DIO_u8_LOW);		    //Depending on which port and which pin we used for R/W pin, we set the values of PORT & PIN in config file
    
    /*Write char*/
    DIO_u8SetPortValue(LCD_u8_DATA_PORT , Copy_u8Char);							    //Takes the ASCII code of the char (by placing the char between '') and it looks up the equivalent address to that in the CGROM
    
    /*E = 1*/
    DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_E_PIN , DIO_u8_HIGH);		    //Depending on which port and which pin we used for E pin, we set the values of PORT & PIN in config file
    
    _delay_us(1);		///From LCD data sheet, E pulse width tw --> min = 230ns -->we can't use 0.23us(no fractions)		
    
    /*E = 0*/
    DIO_u8SetPinValue(LCD_u8_CONTROL_PORT , LCD_u8_E_PIN , DIO_u8_LOW);	            //Depending on which port and which pin we used for E pin, we set the values of PORT & PIN in config file
} 	

/*************************************************************************************/

void LCD_voidSendString(u8 * Copy_pu8String)
/**Function used to send string to the LCD**/
{
	for(u8 i=0 ; (*(Copy_pu8String+i))!='\0' ; i++)
	{
		LCD_voidSendChar(*(Copy_pu8String+i));
	}
} 

/*************************************************************************************/

void LCD_voidSendNum(u32 Copy_u32Num)
/**Function used to send number to the LCD**/
{
	u32 Local_u32Divider = 10;		//u32 Local Variable - Used to get the digits of the number by finding the remainder on it
	u32 Local_u32Remainder ;		//u32 Local Variable - Used to get the remainder 
	u32 Local_u32Digit;				//u32 Local Variable - Used to hold the digits of the number
	
	u32 Local_u32DigitArr[10];		//u32 Local Array - Used to store the digits of the number
	u8 Local_u8_Counteri =1;		//u8 Local Variable - Used as a counter
	if(Copy_u32Num == 0)
	{
		LCD_voidSendChar(48);
	}
	
	while(Copy_u32Num != 0)
	{
		Local_u32Remainder = Copy_u32Num % Local_u32Divider;			//The remainder is calculated for the multiples of ten tell the biggest digit
		Local_u32Digit = Local_u32Remainder/(Local_u32Divider/10);		//Finding each digit by dividing the resultant remainder by the divider/10
		
		Local_u32DigitArr[Local_u8_Counteri]= Local_u32Digit;			//Storing the digits in the array		
		Local_u8_Counteri++;
		
		Copy_u32Num -= Local_u32Remainder;								//Calculating the number after finding the pervious digit
		Local_u32Divider *= 10;											//Increasing the divider each loop to get a higher multiple of ten
	}
	
	Local_u8_Counteri--;
	while(Local_u8_Counteri>0)											//Looping on the array to send the stored digits to the LCD
	{
		LCD_voidSendChar(Local_u32DigitArr[Local_u8_Counteri]+48);		//Sending the digits to LCD_voidSendChar() function. To calculate the ASCII for each digit we add the ASCII of zero = 48
		Local_u8_Counteri--;
	}

}	

/*************************************************************************************/

u8 LCD_u8GoToXY(u8 Copy_u8LineNum , u8 Copy_u8Location)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8Location <= 39)							//Because each line has 40 characters available (0 - 40)
	{
		switch(Copy_u8LineNum)
		{
			case LCD_u8_LINE_ONE: LCD_voidSendCmnd(0x80 + Copy_u8Location);break;		//As the first line starts from address 0x80H --> 0b1 0000000
			case LCD_u8_LINE_TWO: LCD_voidSendCmnd(0xC0 + Copy_u8Location);break;		//As the second line starts from address 0xC0H --> 0b1 0000000 + 64(decimal) = 0b1 1000000
			default:
			Local_u8ErrorState = STD_TYPES_NOK;			//In case of wrong line number
			break;
		}
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;				//In case of wrong line location
	}
	
	return Local_u8ErrorState;
}									

/*************************************************************************************/

void LCD_voidClearScreen(void)
/**Function used to crear the display screen**/
{
	LCD_voidSendCmnd(0b00000001);
	//Wait more than 1.53ms
	_delay_ms(2);
}

/*************************************************************************************/

u8 LCD_u8CreateSpecialChar(u8 Copy_u8SpecialCharNum , u8 * Copy_pu8Pattern)
/**Function used to create a new special character**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8SpecialCharNum <= 7)
	{	
		switch(Copy_u8SpecialCharNum)
		{
			case LCD_u8_SPECIAL_CHAR0:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR0_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR1:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR1_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR2:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR2_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR3:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR3_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR4:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR4_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR5:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR5_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR6:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR6_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
			
			case LCD_u8_SPECIAL_CHAR7:
			LCD_voidSendCmnd(LCD_u8_SPECIAL_CHAR7_Address);		//Set CGRAM Address to write the character
			for(u8 i=0 ; i<8 ; i++)
			{
				LCD_voidSendChar(*(Copy_pu8Pattern+i));			//Saving the pattern to the CGRAM
			}
			break;
			
		}

	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*************************************************************************************/

u8 LCD_u8SendSpecialChar(u8 Copy_u8SpecialCharNum , u8 Copy_u8LineNum , u8 Copy_u8Location)
/**Function used to send a special character to the LCD**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8SpecialCharNum <= 7 && ((Copy_u8LineNum == 1) || (Copy_u8LineNum == 2)) && Copy_u8Location <= 39)
	{
		LCD_u8GoToXY(Copy_u8LineNum , Copy_u8Location);
		LCD_voidSendChar(Copy_u8SpecialCharNum);
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*************************************************************************************/

void	LCD_u8_MoveCursor(u8 Copy_MovingDirection)
{
	if(Copy_MovingDirection == LCD_u8MoveLeft)
	{
		/*Move cursor left cmnd*/
		LCD_voidSendCmnd(0b00010000);
	}
	else if(Copy_MovingDirection == LCD_u8MoveRight)
	{
		/*Move cursor right cmnd*/
		LCD_voidSendCmnd(0b00010100);
	}
}

/*************************************************************************************/

void	LCD_u8_MoveScreen(u8 Copy_MovingDirection)
{
	if(Copy_MovingDirection == LCD_u8MoveLeft)
	{
		/*Move cursor left cmnd*/
		LCD_voidSendCmnd(0b00011000);
	}
	else if(Copy_MovingDirection == LCD_u8MoveRight)
	{
		/*Move cursor right cmnd*/
		LCD_voidSendCmnd(0b00011100);
	}
}
