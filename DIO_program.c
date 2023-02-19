/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: ATMEGA32 - DIO_program.c 			     ******/
/****** Version : 01		 							 ******/
/**************************************************************/
/*LIB Layer*/
#include	"STD_TYPES.h"
#include	"BIT_MATH.h"

/*MCAL*/
#include	"DIO_interface.h"
#include	"DIO_private.h"
#include	"DIO_config.h"


void DIO_voidInit(void)
/**Function to initiate the directions and the values of all the pins**/
{
	//Initiating the directions of pins
	DIO_u8_DDRA_REG = Conc(DIO_u8_PA7_INITIAL_DIRECTION , DIO_u8_PA6_INITIAL_DIRECTION , DIO_u8_PA5_INITIAL_DIRECTION , DIO_u8_PA4_INITIAL_DIRECTION , 
						   DIO_u8_PA3_INITIAL_DIRECTION , DIO_u8_PA2_INITIAL_DIRECTION , DIO_u8_PA1_INITIAL_DIRECTION , DIO_u8_PA0_INITIAL_DIRECTION); 
						   
	DIO_u8_DDRB_REG = Conc(DIO_u8_PB7_INITIAL_DIRECTION , DIO_u8_PB6_INITIAL_DIRECTION , DIO_u8_PB5_INITIAL_DIRECTION , DIO_u8_PB4_INITIAL_DIRECTION , 
						   DIO_u8_PB3_INITIAL_DIRECTION , DIO_u8_PB2_INITIAL_DIRECTION , DIO_u8_PB1_INITIAL_DIRECTION , DIO_u8_PB0_INITIAL_DIRECTION); 
						   
	DIO_u8_DDRC_REG = Conc(DIO_u8_PC7_INITIAL_DIRECTION , DIO_u8_PC6_INITIAL_DIRECTION , DIO_u8_PC5_INITIAL_DIRECTION , DIO_u8_PC4_INITIAL_DIRECTION , 
						   DIO_u8_PC3_INITIAL_DIRECTION , DIO_u8_PC2_INITIAL_DIRECTION , DIO_u8_PC1_INITIAL_DIRECTION , DIO_u8_PC0_INITIAL_DIRECTION); 
						   
	DIO_u8_DDRD_REG = Conc(DIO_u8_PD7_INITIAL_DIRECTION , DIO_u8_PD6_INITIAL_DIRECTION , DIO_u8_PD5_INITIAL_DIRECTION , DIO_u8_PD4_INITIAL_DIRECTION , 
						   DIO_u8_PD3_INITIAL_DIRECTION , DIO_u8_PD2_INITIAL_DIRECTION , DIO_u8_PD1_INITIAL_DIRECTION , DIO_u8_PD0_INITIAL_DIRECTION); 
						                              
										

						   
	//Initiating the values of pins
	DIO_u8_PORTA_REG = Conc(DIO_u8_PA7_INITIAL_VALUE , DIO_u8_PA6_INITIAL_VALUE , DIO_u8_PA5_INITIAL_VALUE , DIO_u8_PA4_INITIAL_VALUE , 
							DIO_u8_PA3_INITIAL_VALUE , DIO_u8_PA2_INITIAL_VALUE , DIO_u8_PA1_INITIAL_VALUE , DIO_u8_PA0_INITIAL_VALUE);
						    
						   
	DIO_u8_PORTB_REG = Conc(DIO_u8_PB7_INITIAL_VALUE , DIO_u8_PB6_INITIAL_VALUE , DIO_u8_PB5_INITIAL_VALUE , DIO_u8_PB4_INITIAL_VALUE , 
						    DIO_u8_PB3_INITIAL_VALUE , DIO_u8_PB2_INITIAL_VALUE , DIO_u8_PB1_INITIAL_VALUE , DIO_u8_PB0_INITIAL_VALUE);

	DIO_u8_PORTC_REG = Conc(DIO_u8_PC7_INITIAL_VALUE , DIO_u8_PC6_INITIAL_VALUE , DIO_u8_PC5_INITIAL_VALUE , DIO_u8_PC4_INITIAL_VALUE , 
						    DIO_u8_PC3_INITIAL_VALUE , DIO_u8_PC2_INITIAL_VALUE , DIO_u8_PC1_INITIAL_VALUE , DIO_u8_PC0_INITIAL_VALUE);
						   
	DIO_u8_PORTD_REG = Conc(DIO_u8_PD7_INITIAL_VALUE , DIO_u8_PD6_INITIAL_VALUE , DIO_u8_PD5_INITIAL_VALUE , DIO_u8_PD4_INITIAL_VALUE , 
						    DIO_u8_PD3_INITIAL_VALUE , DIO_u8_PD2_INITIAL_VALUE , DIO_u8_PD1_INITIAL_VALUE , DIO_u8_PD0_INITIAL_VALUE);
}

/*************************************************************************************/

u8 DIO_u8SetPinDirection  (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8PinDirection)
/**Function to specify the direction of a pin whether it's input or output**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	
	if((Copy_u8PortId <= DIO_u8_PORTD) && (Copy_u8PinId <= DIO_u8_PIN7) && ((Copy_u8PinDirection == DIO_u8_OUTPUT) || (Copy_u8PinDirection == DIO_u8_INPUT)))		//Checks the validity of the user inputs
	{
		if(Copy_u8PortId == DIO_u8_PORTA)				///PORTA is chosen
		{
				if(Copy_u8PinDirection == DIO_u8_OUTPUT)		//-->Pin is output
				{
					SET_BIT(DIO_u8_DDRA_REG , Copy_u8PinId);
				}
				
				else if(Copy_u8PinDirection == DIO_u8_INPUT)	//-->Pin is input
				{
					CLR_BIT(DIO_u8_DDRA_REG , Copy_u8PinId);
				}
		}
		
		
		else if(Copy_u8PortId == DIO_u8_PORTB)			///PORTB is chosen
		{
				if(Copy_u8PinDirection == DIO_u8_OUTPUT)		//-->Pin is output
				{
					SET_BIT(DIO_u8_DDRB_REG , Copy_u8PinId);
				}
				
				else if(Copy_u8PinDirection == DIO_u8_INPUT)	//-->Pin is input
				{
					CLR_BIT(DIO_u8_DDRB_REG , Copy_u8PinId);
				}
		}
		
		
		else if(Copy_u8PortId == DIO_u8_PORTC)			///PORTC is chosen
		{
				if(Copy_u8PinDirection == DIO_u8_OUTPUT)		//-->Pin is output
				{
					SET_BIT(DIO_u8_DDRC_REG , Copy_u8PinId);
				}
				
				else if(Copy_u8PinDirection == DIO_u8_INPUT)	//-->Pin is input
				{
					CLR_BIT(DIO_u8_DDRC_REG , Copy_u8PinId);
				}
		}
		
		
		else if(Copy_u8PortId == DIO_u8_PORTD)			///PORTD is chosen
		{
				if(Copy_u8PinDirection == DIO_u8_OUTPUT)		//-->Pin is output
				{
					SET_BIT(DIO_u8_DDRD_REG , Copy_u8PinId);
				}
				
				else if(Copy_u8PinDirection == DIO_u8_INPUT)	//-->Pin is input
				{
					CLR_BIT(DIO_u8_DDRD_REG , Copy_u8PinId);
				}
		}
	}
	
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;						//The validity of the user inputs isn't guaranteed
	}
	
	
		return Local_u8ErrorState;
}
	
/*************************************************************************************/	
		
u8 DIO_u8SetPinValue      (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 Copy_u8PinValue)
/**Function to specify the value of a pin whether it's high or low**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	
	if(Copy_u8PinId <= DIO_u8_PIN7)							//Checks the validity of the user inputs of the Pin value
	{
		switch(Copy_u8PinValue)		//Checks the user input for Pin value
		{
			case DIO_u8_HIGH:	///High is chosen
			switch(Copy_u8PortId)	//Checks the user input for Port value
			{
				case DIO_u8_PORTA: SET_BIT(DIO_u8_PORTA_REG , Copy_u8PinId); break;		///PORTA is chosen
				case DIO_u8_PORTB: SET_BIT(DIO_u8_PORTB_REG , Copy_u8PinId); break;     ///PORTB is chosen
				case DIO_u8_PORTC: SET_BIT(DIO_u8_PORTC_REG , Copy_u8PinId); break;     ///PORTC is chosen
				case DIO_u8_PORTD: SET_BIT(DIO_u8_PORTD_REG , Copy_u8PinId); break;     ///PORTD is chosen
				default: Local_u8ErrorState = STD_TYPES_NOK; break;						//Wrong input for the Port Id
			}
			break;
			
			case DIO_u8_LOW:	///Low is chosen
			switch(Copy_u8PortId)	//Checks the user input for port value
			{
				case DIO_u8_PORTA: CLR_BIT(DIO_u8_PORTA_REG , Copy_u8PinId); break;		///PORTA is chosen
				case DIO_u8_PORTB: CLR_BIT(DIO_u8_PORTB_REG , Copy_u8PinId); break;     ///PORTB is chosen
				case DIO_u8_PORTC: CLR_BIT(DIO_u8_PORTC_REG , Copy_u8PinId); break;     ///PORTC is chosen
				case DIO_u8_PORTD: CLR_BIT(DIO_u8_PORTD_REG , Copy_u8PinId); break;     ///PORTD is chosen
				default: Local_u8ErrorState = STD_TYPES_NOK; break;						//Wrong input for the Port Id
			}
			break;
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;											//Wrong input for the Pin value 
			break;
		}
	}
	
	else									//Wrong input for the Pin Id
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}		

/*************************************************************************************/

u8 DIO_u8GetPinValue      (u8 Copy_u8PortId , u8 Copy_u8PinId , u8 * Copy_pu8ReturnPinValue)
/**Function to return the value of a pin whether it's high or low**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	u8 Local_u8PinValue;
	if((Copy_u8PinId <= DIO_u8_PIN7) && (Copy_pu8ReturnPinValue != NULL))		//Checks the validity of the user inputs of the pin value and that the pointer had an address
	{
		switch(Copy_u8PortId)		//Checks the user input for Port Id
		{
			case DIO_u8_PORTA:		///PORTA is chosen
			Local_u8PinValue = GET_BIT(DIO_u8_PINA_REG , Copy_u8PinId);			//Because the High & low values may differ (Don't have always to be 0 & 1)
			if(Local_u8PinValue == 1)
			{
				*Copy_pu8ReturnPinValue = DIO_u8_HIGH;
			}
			else
			{
				*Copy_pu8ReturnPinValue = DIO_u8_LOW;
			}
			break;
			
			
			case DIO_u8_PORTB:		///PORTB is chosen
			Local_u8PinValue = GET_BIT(DIO_u8_PINB_REG , Copy_u8PinId);
			if(Local_u8PinValue == 1)
			{
				*Copy_pu8ReturnPinValue = DIO_u8_HIGH;
			}
			else
			{
				*Copy_pu8ReturnPinValue = DIO_u8_LOW;
			}
			break;
			
			
			case DIO_u8_PORTC:		///PORTC is chosen
			Local_u8PinValue = GET_BIT(DIO_u8_PINC_REG , Copy_u8PinId);
			if(Local_u8PinValue == 1)
			{
				*Copy_pu8ReturnPinValue = DIO_u8_HIGH;
			}
			else
			{
				*Copy_pu8ReturnPinValue = DIO_u8_LOW;
			}
			break;
			
			
			case DIO_u8_PORTD:		///PORTD is chosen
			Local_u8PinValue = GET_BIT(DIO_u8_PIND_REG , Copy_u8PinId);
			if(Local_u8PinValue == 1)
			{
				*Copy_pu8ReturnPinValue = DIO_u8_HIGH;
			}
			else
			{
				*Copy_pu8ReturnPinValue = DIO_u8_LOW;
			}
			break;
			
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK;			//Wrong input for the Port Id
			break;
		}
	}
	
	else									//Wrong input for the Pin Id 
	{
		Local_u8ErrorState = STD_TYPES_NOK;		
	}
	
	return Local_u8ErrorState;
}

/*************************************************************************************/

u8 DIO_u8SetPortDirection (u8 Copy_u8PortId , u8 Copy_u8PortDirection)
///Function to specify the direction of a whole port whether it's input or output
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	
	
	switch(Copy_u8PortDirection)		//Checks the user input for Port Direction
	{
		case DIO_u8_OUTPUT:
		switch(Copy_u8PortId)			//Checks the user input for Port Id
		{
			case DIO_u8_PORTA: DIO_u8_DDRA_REG = 0xFF; break;	///PORTA is chosen
			case DIO_u8_PORTB: DIO_u8_DDRB_REG = 0xFF; break;	///PORTB is chosen
			case DIO_u8_PORTC: DIO_u8_DDRC_REG = 0xFF; break;	///PORTC is chosen
			case DIO_u8_PORTD: DIO_u8_DDRD_REG = 0xFF; break;	///PORTD is chosen
			default:
			Local_u8ErrorState = STD_TYPES_NOK;				//Wrong input for the Port Id
			break;
		}
		break;
		
		
		
		case DIO_u8_INPUT:
		switch(Copy_u8PortId)			//Checks the user input for Port Id
		{
			case DIO_u8_PORTA: DIO_u8_DDRA_REG = 0x00; break;	///PORTA is chosed
			case DIO_u8_PORTB: DIO_u8_DDRB_REG = 0x00; break;   ///PORTB is chosed
			case DIO_u8_PORTC: DIO_u8_DDRC_REG = 0x00; break;   ///PORTC is chosed
			case DIO_u8_PORTD: DIO_u8_DDRD_REG = 0x00; break;   ///PORTD is chosed
			default:
			Local_u8ErrorState = STD_TYPES_NOK;				//Wrong input for the Port Id
			break;
		}
		break;
		
		
		
		default:
		Local_u8ErrorState = STD_TYPES_NOK;			//Wrong input for the Port Direction
		break;
		
	}
	
	return Local_u8ErrorState;
}					

/*************************************************************************************/

u8 DIO_u8SetPortValue	  (u8 Copy_u8PortId , u8 Copy_u8PortValue)
///Function to specify the value of a whole port whether it's high or low
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	
	
	switch(Copy_u8PortId)						//Because the value doesn't have to be only High or Low for the whole port
	{
		case DIO_u8_PORTA:		///PORTA is chosen
		DIO_u8_PORTA_REG = Copy_u8PortValue;
		break;
		
		case DIO_u8_PORTB:		///PORTB is chosen
		DIO_u8_PORTB_REG = Copy_u8PortValue;
		break;
		
		case DIO_u8_PORTC:		///PORTC is chosen
		DIO_u8_PORTC_REG = Copy_u8PortValue;
		break;
		
		case DIO_u8_PORTD:		///PORTD is chosen
		DIO_u8_PORTD_REG = Copy_u8PortValue;
		break;
		
		default:
		Local_u8ErrorState = STD_TYPES_NOK ;				//Wrong input for the Port Id 
		break;
	}

	return Local_u8ErrorState;
	
}						

/*************************************************************************************/

u8 DIO_u8GetPortValue	  (u8 Copy_u8PortId , u8 * Copy_pu8ReturnPortValue)
/**Function to return the value of a whole port whether it's high or low**/
{
	u8 Local_u8ErrorState = STD_TYPES_OK;					//u8 Variable - To return the state of the function at the end of it
	
	if(Copy_pu8ReturnPortValue != NULL)		//Checks that the pointer has an address
	{
		switch(Copy_u8PortId)	//Checks the user input for Port Id
		{

			case DIO_u8_PORTA:*Copy_pu8ReturnPortValue = DIO_u8_PINA_REG; break;		//Not true & false, its an 8 bit number
			case DIO_u8_PORTB:*Copy_pu8ReturnPortValue = DIO_u8_PINB_REG; break;
			case DIO_u8_PORTC:*Copy_pu8ReturnPortValue = DIO_u8_PINC_REG; break;
			case DIO_u8_PORTD:*Copy_pu8ReturnPortValue = DIO_u8_PIND_REG; break;
			
			
			default:
			Local_u8ErrorState = STD_TYPES_NOK; 		//Wrong input for the Port Id

		}
	}
	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	
	return Local_u8ErrorState;
}		

/**************************************************************************************/

u8 DIO_u8TogglePinValue(u8 Copy_u8PortId , u8 Copy_u8PinId)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;				    	//u8 Variable - To return the state of the function at the end of it
	if((Copy_u8PinId <= DIO_u8_PIN7) && (Copy_u8PinId <= DIO_u8_PIN7))		//Checks the validity of the user inputs of the pin value and that the pointer had an address
	{
		switch(Copy_u8PortId)
		{
		    case DIO_u8_PORTA: TOG_BIT(DIO_u8_PORTA_REG , Copy_u8PinId); break;
			case DIO_u8_PORTB: TOG_BIT(DIO_u8_PORTB_REG , Copy_u8PinId); break;
			case DIO_u8_PORTC: TOG_BIT(DIO_u8_PORTC_REG , Copy_u8PinId); break;
			case DIO_u8_PORTD: TOG_BIT(DIO_u8_PORTD_REG , Copy_u8PinId); break;
		}
	}
	return Local_u8ErrorState;
}
