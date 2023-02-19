/**************************************************************/
/****** Author 	: Mayar Saber 							 ******/
/****** SW		: Login System to control Fan and Lights ******/
/****** SWC		: main.c 			   				     ******/
/****** Version : 01		 							 ******/
/**************************************************************/
/*----------------Includes----------------*/
/*LIB*/
#include	"STD_TYPES.h"
#include	"BIT_MATH.h"

/*MCAL*/
#include	"DIO_interface.h"
#include	"ADC_interface.h"
#include	"TIMERS_interface.h"
#include	"GI_interface.h"
#include	"EXTI_interface.h"

/*HAL*/
#include	"LCD_interface.h"
#include	"KPD_interface.h"

#define		F_CPU	  8000000UL
#include	<util/delay.h>

/*Configure system password*/
u8 App_Au8SystemPassword[4] = {'1','2','3','4'};

/*Global Variables*/
u8 Local_u8ChoosedService;			//A u8-Variable to indicate the chosen service

/*Prototypes for functions*/
void  App_voidTempControlSystem  (u16 Copy_u16DigitalReturnedValue);		//Application using LM35(Temperature sensor)
void  App_voidLightControlSystem (u16 Copy_u16DigitalReturnedValueLDR);		//Application using LDR(Light Dependent Resistor)
void  App_voidGetBackToMenuEXTI  (void);									//Function to get back to the main menu by changing the value of the ChooseService variable

int main(void)
{
/*----------------Local Variables----------------*/
	//Arrays of u8 to send strings to LCD
	u8 Local_Au8LCDStr1[] = "....Welcome....";
	u8 Local_Au8LCDStr2[] = "login->Press(E)";
	u8 Local_Au8LCDStr3[] = "Enter Password";
	u8 Local_Au8LCDStr4[] = "Correct Password";
	u8 Local_Au8LCDStr5[] = "Wrong Password";
	u8 Local_Au8LCDStr6[] = "Trail1.Try again";
	u8 Local_Au8LCDStr7[] = "Trail2.Try again";
	u8 Local_Au8LCDStr8[] = "Try again later";
	u8 Local_Au8LCDStr9[] = "Welcome to system";
	u8 Local_Au8LCDStr10[] = "Choose Service..";
	u8 Local_Au8LCDStr11[] = "(1)Temp";
	u8 Local_Au8LCDStr12[] = "(2)Light";


	u8 Local_u8PressedKey = KPD_u8_KEY_NOT_PRESSED;	//A u8-Variable to get the pressed key from the keypad/ Initiated by a macro to indicate that it's not pressed
	u8 Local_u8EnteredPassword[4];					//An Array of u8, to store the entered password
	u8 Local_u8Counter = 0;							//A u8-Variable, used to store the password digit we're going to enter
	u8 Local_u8Flag = 0;							//A u8-Variable to determine whether the entered flag is correct or wrong
	u8 Local_u8NumberOfTrails = 0;					//A u8-Variable to indicate the given trails for entering a password


/*----------------Initializing peripherals----------------*/

	//initialize DIO
	DIO_voidInit();
	//initialize LCD
	LCD_voidInit();
	//initiate General Interrupt
	GI_voidEnable();
	//initiate ADC
	ADC_voidInit();
	//initiate TIMER0
	TIMER0_voidInit();
	//Set callback for EXTI0
	EXTI_u8SetCallBack(EXTI_u8_INTERRUPT0 , &App_voidGetBackToMenuEXTI);
	//Enable EXTI0 at falling edge
	EXTI_u8InterruptEnable(EXTI_u8_INTERRUPT0 , EXTI_u8_FALLING_EDGE);

/*----------------Part1 - Welcome Screen----------------*/
	LCD_voidSendString(Local_Au8LCDStr1);
	LCD_u8GoToXY(LCD_u8_LINE_TWO,0);
	LCD_voidSendString(Local_Au8LCDStr2);

	//Wait till 'E' key is pressed
	while(Local_u8PressedKey != 'E')
	{
		//Pull on KPD value
		KPD_u8GetPressedKey(&Local_u8PressedKey);
	}

	//If Key 'E' is pressed, ask for the password (3 trails)
	if(Local_u8PressedKey == 'E')
	{
		//Check entered password
		//3 Trails for wrong password
		while(Local_u8NumberOfTrails < 3)
		{
			//Ask for password
			LCD_voidClearScreen();						  //Clear LCD to enter the password
			Local_u8Counter = 0;						  //Initiate counter
			LCD_u8GoToXY(LCD_u8_LINE_ONE,0);			  //Go to the first address on the LCD
			LCD_voidSendString(Local_Au8LCDStr3);		  //Ask for the password
			Local_u8PressedKey = KPD_u8_KEY_NOT_PRESSED;  //Reinitiate the variable for the pressed key

			//Get the entered key and write it as a '*', 4 times for the 4 digits
			LCD_u8GoToXY(LCD_u8_LINE_TWO , 5);			          //Go to the 2nd line on the LCD
			while(Local_u8Counter < 4)					          //Loop to get the 4 digits
			{
				KPD_u8GetPressedKey(&Local_u8PressedKey);
				if(Local_u8PressedKey != KPD_u8_KEY_NOT_PRESSED)  //When the key is pressed
				{
					Local_u8EnteredPassword[Local_u8Counter] = Local_u8PressedKey;	//Store the pressed key
					LCD_voidSendChar('*');											//Enter it as *
					Local_u8Counter++;												//Increase counter
					Local_u8PressedKey = KPD_u8_KEY_NOT_PRESSED;					//Reinitiate the pressed key to wait for the next digit
				}
			}

			/*Check the entered password*/
			for(Local_u8Counter = 0 ; Local_u8Counter<4 ; Local_u8Counter++)							//Loop on the 4 digits
			{
				if(App_Au8SystemPassword[Local_u8Counter] == Local_u8EnteredPassword[Local_u8Counter])	//Compare between the entered value and the stored value for the password for each digit
				{
					Local_u8Flag = 1;			//If it's correct -> Flag = 1
				}
				else
				{
					Local_u8Flag = 0;			//If it's wrong -> Flag = 0 , Stop comparing (break)
					break;
				}
			}

			/*Print on the comparison result*/
			if(Local_u8Flag == 1)		//if Flag = 1 -> Password is correct
			{
				LCD_voidClearScreen();
				LCD_voidSendString(Local_Au8LCDStr4);
				break;
			}
			else						//if Flag = 0 -> Password is not correct, try again
			{
				Local_u8NumberOfTrails++;	    	    //increase the number of used trails
				LCD_voidClearScreen();		        	//Clear screen
				LCD_u8GoToXY(LCD_u8_LINE_ONE,0);        //Go to the first address on the LCD
				LCD_voidSendString(Local_Au8LCDStr5);	//Print that the password is wrong
				LCD_u8GoToXY(LCD_u8_LINE_TWO,0);
				switch(Local_u8NumberOfTrails)			//Decide depending on the value of the remaining trails the next messages
				{
				case 1:
					LCD_voidSendString(Local_Au8LCDStr6);
					break;
				case 2:
					LCD_voidSendString(Local_Au8LCDStr7);
					break;
				case 3:
					LCD_voidSendString(Local_Au8LCDStr8);
					break;
				}
				_delay_ms(2000);
			}
		}
	}


/*----------------System Serices----------------*/
	if(Local_u8Flag == 1)		//Password was correct
	{
		Local_u8PressedKey = KPD_u8_KEY_NOT_PRESSED;  //Reinitiate the pressed key variable
		LCD_voidClearScreen();						  //Clear Screen
		LCD_voidSendString(Local_Au8LCDStr9);	      //Welcome message
		_delay_ms(500);
		LCD_u8_MoveScreen(LCD_u8MoveLeft);			  //Moving the screen left to display the whole text
		_delay_ms(500);

		//Choosing the required service from the system
		LCD_voidClearScreen();
		LCD_voidSendString(Local_Au8LCDStr10);		//A message to ask for choosing one of the services
		LCD_u8GoToXY(LCD_u8_LINE_TWO,0);
		LCD_voidSendString(Local_Au8LCDStr11);		//1 for temperature control service
		LCD_u8GoToXY(LCD_u8_LINE_TWO,8);
		LCD_voidSendString(Local_Au8LCDStr12);		//2 for light control

		//Pull for the value of the pressed key choice
		while(Local_u8PressedKey == KPD_u8_KEY_NOT_PRESSED)
		{
			KPD_u8GetPressedKey(&Local_u8PressedKey);
		}

		//Decide depending on the input
		if(Local_u8PressedKey == '1')	//1 for Temperature control service
		{
			Local_u8ChoosedService = '1';
		}

		else if(Local_u8PressedKey == '2') //2 for lighting control service
		{
			Local_u8ChoosedService = '2';
		}
	}

	else if(Local_u8Flag == 0)		//Messages if the password wasn't correct and no trails left
	{
		LCD_voidClearScreen();
		u8 Local_u8Arr[] = "...Thank You...";
		u8 Local_u8Arr2[] = "Restart.TryAgain";
		LCD_voidSendString(Local_u8Arr);
		LCD_u8GoToXY(LCD_u8_LINE_TWO,0);
		LCD_voidSendString(Local_u8Arr2);
	}

	while(1)
	{
		if(Local_u8ChoosedService == '1')
		{
			/*Read thae value of LM35 which is on channel1 in the ADC periphera0*/
			ADC_u8GetDigitalValueAsynch(ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC0 , &App_voidTempControlSystem);
		}

		if(Local_u8ChoosedService == '2')
		{
			/*Read thae value of LDR which is on channel0 in the ADC peripheral*/
			ADC_u8GetDigitalValueAsynch(ADC_u8_SINGLE_ENDED_INPUT_CHANNEL_ADC1 , &App_voidLightControlSystem);
		}

		if(Local_u8ChoosedService == '0')	//If we get back to the main menu using EXTI
		{
			Local_u8PressedKey = KPD_u8_KEY_NOT_PRESSED;  //Reinitiate the pressed key variable

			//Choosing the required service from the system
			LCD_voidClearScreen();
			LCD_voidSendString(Local_Au8LCDStr10);		//A message to ask for choosing one of the services
			LCD_u8GoToXY(LCD_u8_LINE_TWO,0);
			LCD_voidSendString(Local_Au8LCDStr11);		//1 for temperature control service
			LCD_u8GoToXY(LCD_u8_LINE_TWO,8);
			LCD_voidSendString(Local_Au8LCDStr12);		//2 for light control

			//Pull for the value of the pressed key choice
			while(Local_u8PressedKey == KPD_u8_KEY_NOT_PRESSED)
			{
				KPD_u8GetPressedKey(&Local_u8PressedKey);
			}

			//Decide depending on the input
			if(Local_u8PressedKey == '1')	//1 for Temperature control service
			{
				Local_u8ChoosedService = '1';
			}

			else if(Local_u8PressedKey == '2') //2 for lighting control service
			{
				Local_u8ChoosedService = '2';
			}
		}
	}
	return 0;
}

void  App_voidTempControlSystem(u16 Copy_u16DigitalReturnedValue)
/*Application using LM35(Temperature sensor)*/
{

	u8 Local_Au8LCDStr18[] = "Degree=";
	u8 Local_Au8LCDStr19[] = "HOT!";
	u8 Local_Au8LCDStr20[] = "Cold!";
	u8 Local_Au8LCDStr21[] = "Duty Cycle=";

	/*Calculate Analog Value = Digital Value * Step Size
	 *Step Size = Max Voltage / 2**Resolution*/
	u16 Local_u16AnalogValue = (Copy_u16DigitalReturnedValue * 5000UL)/1024;
	u16 Local_DegreeInCelsius = Local_u16AnalogValue/10;

	//Write the results of the analog value on the screen
	LCD_voidClearScreen();

	LCD_u8GoToXY(LCD_u8_LINE_ONE,0);
	LCD_voidSendString(Local_Au8LCDStr18);
	LCD_voidSendNum(Local_DegreeInCelsius);

	if(Local_DegreeInCelsius > 25)		//If temp > 25 --> Hot Temp
	{
		LCD_u8GoToXY(LCD_u8_LINE_ONE , 12);
		LCD_voidSendString(Local_Au8LCDStr19);

		/*Turn on RED LED / Turn OFF GREEN LED*/
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN4 , DIO_u8_LOW);

		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr21);
		/*Turn on Fan (DC motor) with a duty cycle depending on the temperature*/
		//TIMER0 , PWM Fast Mode , Non-Inverting
		if((Local_DegreeInCelsius > 25) && (Local_DegreeInCelsius <30))
		{
			//Fan - Duty Cycle 40%
			/* Timer freq = 8MHZ/8 = 1MHZ
			   Tick time = 1usec
			   OverFlow time = 256usec
			   Duty cycle = 40%
			   OCR0 = 256*0.4 -1 = 101*/
			TIMER0_voidSetCompareMatchValue(101);
			LCD_voidSendNum(40);
			LCD_voidSendChar('%');
		}
		else if((Local_DegreeInCelsius >= 30) && (Local_DegreeInCelsius <40))
		{
			//Fan - Duty Cycle 50%
			/* Duty cycle = 50%
			   OCR0 = 256*0.5 -1 = 127*/
			TIMER0_voidSetCompareMatchValue(127);
			LCD_voidSendNum(50);
			LCD_voidSendChar('%');
		}
		else
		{
			//Fan - Duty Cycle 60%
			/* Duty cycle = 60%
			   OCR0 = 256*0.6 -1 = 152*/
			TIMER0_voidSetCompareMatchValue(152);
			LCD_voidSendNum(60);
			LCD_voidSendChar('%');
		}
	}

	else     //if temp <25
	{
		LCD_u8GoToXY(LCD_u8_LINE_ONE , 12);
		LCD_voidSendString(Local_Au8LCDStr20);

		///*Turn on Green LED / Turn OFF RED LED*/
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN4 , DIO_u8_HIGH);


		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr21);
		/*Turn on Fan (DC motor) with a duty cycle depending on the temperature*/
		//TIMER0 , PWM Fast Mode , Non-Inverting
		if((Local_DegreeInCelsius >= 0) && (Local_DegreeInCelsius <10))
		{
			//Fan - Duty Cycle 10%
			/* Duty cycle = 10%
			   OCR0 = 256*0.1 -1 = 24*/
			TIMER0_voidSetCompareMatchValue(24);
			LCD_voidSendNum(10);
			LCD_voidSendChar('%');
		}
		else if((Local_DegreeInCelsius >= 10) && (Local_DegreeInCelsius <20))
		{
			//Fan - Duty Cycle 20%
			/* Duty cycle = 20%
			   OCR0 = 256*0.2 -1 = 50*/
			TIMER0_voidSetCompareMatchValue(50);
			LCD_voidSendNum(20);
			LCD_voidSendChar('%');
		}
		else
		{
			//Fan - Duty Cycle 30%
			/* Duty cycle = 30%
			   OCR0 = 256*0.3 -1 = 75*/
			TIMER0_voidSetCompareMatchValue(75);
			LCD_voidSendNum(30);
			LCD_voidSendChar('%');
		}
	}
	_delay_ms(1000);
	LCD_voidClearScreen();
}


void  App_voidLightControlSystem(u16 Copy_u16DigitalReturnedValueLDR)
/*Application using LDR(Light Dependent Resistor)*/
{
	u8 Local_Au8LCDStr13[] = "Analog=";
	u8 Local_Au8LCDStr14[] = "No lights needed";
	u8 Local_Au8LCDStr15[] = "Medium-LED1 ON";
	u8 Local_Au8LCDStr16[] = "Darker-LED2 ON";
	u8 Local_Au8LCDStr17[] = "It'sDark-LEDs ON";

	/*Calculate Analog Value = Digital Value * Step Size
	 *Step Size = Max Voltage / 2**Resolution*/
	u16 Local_u16AnalogValue = (Copy_u16DigitalReturnedValueLDR * 5000UL)/1024;

	//Write the results of the analog value on the screen
	LCD_voidClearScreen();
	//LCD_u8GoToXY(LCD_u8_LINE_ONE,0);
	LCD_voidSendString(Local_Au8LCDStr13);
	LCD_voidSendNum(Local_u16AnalogValue);

	/*Taking actions depending on the result of LDR Sensor*/
	if((Local_u16AnalogValue > 0) && (Local_u16AnalogValue <=1500))
	{
		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr14);							//Print "No Lights Needed"
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_LOW);		//Turn off All LEDs
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN6 , DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN5 , DIO_u8_LOW);
	}
	//If the lights is medium -> Turn on LED1
	else if((Local_u16AnalogValue > 1500) && (Local_u16AnalogValue <=3000))
	{
		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr15);							//Print "Mediun -LED1 ON"
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_HIGH);	//Turn ON one LED
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN6 , DIO_u8_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN5 , DIO_u8_LOW);
	}
	else if((Local_u16AnalogValue > 3000) && (Local_u16AnalogValue <=4000))
	{
		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr16);							//Print "Darker" - 2LEDs ON
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN6 , DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN5 , DIO_u8_LOW);
	}
	else if((Local_u16AnalogValue > 4000))
	{
		LCD_u8GoToXY(LCD_u8_LINE_TWO , 0);
		LCD_voidSendString(Local_Au8LCDStr17);							//Print "It's dark" - Turn ON all LEDs
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN7 , DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN6 , DIO_u8_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTA , DIO_u8_PIN5 , DIO_u8_HIGH);
	}

	_delay_ms(1000);
	LCD_voidClearScreen();
}


void  App_voidGetBackToMenuEXTI(void)
/*Function to get back to the main menu by changing the value of the ChooseService variable*/
{
	Local_u8ChoosedService = '0';
}
