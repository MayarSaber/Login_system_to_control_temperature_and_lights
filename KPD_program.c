/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - KPD_program.c				 ******/
/****** Version : 01		 							 ******/
/**************************************************************/

/*LIB*/
#include 	"STD_TYPES.h"
#include 	"BIT_MATH.h"

#define F_CPU 8000000UL
#include <util/delay.h>

/*MCAL*/
#include 	"DIO_interface.h"

/*HAL*/
#include 	"KPD_interface.h"
#include	"KPD_config.h"
#include	"KPD_private.h"

const u8 KPD_Au8Keys[4][4] = KPD_KEYS;	//The Keypad keys structure  ==> This structure needs to be more configurable by the application ==> We'll create it using Macros im config file

const u8 KPD_Au8RowsPorts[4] = {KPD_ROW0_PORT , KPD_ROW1_PORT , KPD_ROW2_PORT , KPD_ROW3_PORT};	    //Array of Rows ports		///The arrays are global, so that we don't recreate them each time we call the function
const u8 KPD_Au8RowPins  [4] = {KPD_ROW0_PIN , KPD_ROW1_PIN , KPD_ROW2_PIN , KPD_ROW3_PIN};		    //Array of Rows Pins

const u8 KPD_Au8ColsPorts[4] = {KPD_COL0_PORT , KPD_COL1_PORT , KPD_COL2_PORT , KPD_COL3_PORT};	    //Array of Cols ports
const u8 KPD_Au8ColsPins [4] = {KPD_COL0_PIN , KPD_COL1_PIN , KPD_COL2_PIN , KPD_COL3_PIN};		    //Array of Cols pins



u8 KPD_u8GetPressedKey(u8 * Copy_pu8ReturnedKey)
/**Function used to return the pressed key from the keypad**/			
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//Variable to return the state of the function
	u8 Local_u8ReturnedPinValue;							//Variable to hold the returned pin value
	u8 Local_u8RowsCounter;									//Variable to be used as Counter for rows
	u8 Local_u8ColsCounter;									//Variable to be used as Counter for cols
	u8 Local_u8Flag = 0;									//Variable to be used as a flag to indicate that the key was found
	
	
	if(Copy_pu8ReturnedKey != NULL)															//Check that the pointer argument holds an address of a variable in main
	{
		for(Local_u8RowsCounter=0 ; Local_u8RowsCounter<4 ; Local_u8RowsCounter++)		    //Loop on the rows
		{
			DIO_u8SetPinValue(KPD_Au8RowsPorts[Local_u8RowsCounter] , KPD_Au8RowPins[Local_u8RowsCounter] , DIO_u8_LOW);	//Set the row in the round to low (Activate the row)
			
			for(Local_u8ColsCounter=0 ; Local_u8ColsCounter<4 ; Local_u8ColsCounter++)		//Loop on the cols
			{
				DIO_u8GetPinValue(KPD_Au8ColsPorts[Local_u8ColsCounter] , KPD_Au8ColsPins[Local_u8ColsCounter] , &Local_u8ReturnedPinValue);   //Get the value of the current pin and save that to the local variable
				if(Local_u8ReturnedPinValue == DIO_u8_LOW)									//If local variable is set to 0  --> The key is pressed
				{
					/*Debouncing using delay*/
					_delay_ms(20);
					
					/*Check if the pin is still LOW*/
					DIO_u8GetPinValue(KPD_Au8ColsPorts[Local_u8ColsCounter] , KPD_Au8ColsPins[Local_u8ColsCounter] , &Local_u8ReturnedPinValue);
					
					if(Local_u8ReturnedPinValue == DIO_u8_LOW)		//Pin is still low
					{
						/*Wait till the pin is back to HIGH*/
						while(Local_u8ReturnedPinValue == DIO_u8_LOW)
						{
							DIO_u8GetPinValue(KPD_Au8ColsPorts[Local_u8ColsCounter] , KPD_Au8ColsPins[Local_u8ColsCounter] , &Local_u8ReturnedPinValue);
						}
						
						*Copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];	//Return the pressed key to the return key argument
						Local_u8Flag = 1;
						break;
					}
					
					else		//Pin isn't low anymore
					{
						*Copy_pu8ReturnedKey = KPD_u8_KEY_NOT_PRESSED;		//This character will be sent in case no key was pressed, so that the LCD won't display anything
					}
				}
				
				
				
				else
				{
					*Copy_pu8ReturnedKey = KPD_u8_KEY_NOT_PRESSED;			    //This character will be sent in case no key was pressed, so that the LCD won't display anything
				}
			}
			

			/*Deactivate ROw*/
			DIO_u8SetPinValue(KPD_Au8RowsPorts[Local_u8RowsCounter] , KPD_Au8RowPins[Local_u8RowsCounter] , DIO_u8_HIGH);	//We need to return the row pin to it's original state at the end of each loop
			
			if(Local_u8Flag == 1)	//If we found the key, we'll break the rows loop too
			{
				break;
			}
		}
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}
