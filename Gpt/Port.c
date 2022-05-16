/*
 * PORT.c
 *
 *  Created on: Mar 9, 2022
 *      Author: donia
 */
#include <avr/io.h>
#include <util/delay.h>
#include "Bit_utils.h"
#include "Std_types.h"
#include "Port.h"
#include "Port_cfg.h"
#include "Port_prv.h"



void Port_VidInit(void)
{
	#undef INPUT_HIGHIMPEDANCE
	#undef INTERNAL_PULLUP
	#undef OUTPUT_HIGH
	#undef OUTPUT_LOW

	#define INPUT_HIGHIMPEDANCE		0
	#define INTERNAL_PULLUP    		0
	#define OUTPUT_HIGH		    	1
	#define OUTPUT_LOW				1

	DDRA = CONC(PORT_PIN_7_INIT_CFG,PORT_PIN_6_INIT_CFG,PORT_PIN_5_INIT_CFG,PORT_PIN_4_INIT_CFG
				,PORT_PIN_3_INIT_CFG,PORT_PIN_2_INIT_CFG,PORT_PIN_1_INIT_CFG,PORT_PIN_0_INIT_CFG);

	DDRB = CONC(PORT_PIN_15_INIT_CFG,PORT_PIN_14_INIT_CFG,PORT_PIN_13_INIT_CFG,PORT_PIN_12_INIT_CFG
				,PORT_PIN_11_INIT_CFG,PORT_PIN_10_INIT_CFG,PORT_PIN_9_INIT_CFG,PORT_PIN_8_INIT_CFG);

	DDRC = CONC(PORT_PIN_23_INIT_CFG,PORT_PIN_22_INIT_CFG,PORT_PIN_21_INIT_CFG,PORT_PIN_20_INIT_CFG
				,PORT_PIN_19_INIT_CFG,PORT_PIN_18_INIT_CFG,PORT_PIN_17_INIT_CFG,PORT_PIN_16_INIT_CFG);

	DDRD = CONC(PORT_PIN_31_INIT_CFG,PORT_PIN_30_INIT_CFG,PORT_PIN_29_INIT_CFG,PORT_PIN_28_INIT_CFG
					,PORT_PIN_27_INIT_CFG,PORT_PIN_26_INIT_CFG,PORT_PIN_25_INIT_CFG,PORT_PIN_24_INIT_CFG);

	#undef INPUT_HIGHIMPEDANCE
	#undef INTERNAL_PULLUP
	#undef OUTPUT_HIGH
	#undef OUTPUT_LOW

	#define INPUT_HIGHIMPEDANCE		0
	#define INTERNAL_PULLUP    		1
	#define OUTPUT_HIGH		    	1
	#define OUTPUT_LOW				0


	PORTA = CONC(PORT_PIN_7_INIT_CFG,PORT_PIN_6_INIT_CFG,PORT_PIN_5_INIT_CFG,PORT_PIN_4_INIT_CFG
				,PORT_PIN_3_INIT_CFG,PORT_PIN_2_INIT_CFG,PORT_PIN_1_INIT_CFG,PORT_PIN_0_INIT_CFG);

	PORTB = CONC(PORT_PIN_15_INIT_CFG,PORT_PIN_14_INIT_CFG,PORT_PIN_13_INIT_CFG,PORT_PIN_12_INIT_CFG
				,PORT_PIN_11_INIT_CFG,PORT_PIN_10_INIT_CFG,PORT_PIN_9_INIT_CFG,PORT_PIN_8_INIT_CFG);

	PORTC = CONC(PORT_PIN_23_INIT_CFG,PORT_PIN_22_INIT_CFG,PORT_PIN_21_INIT_CFG,PORT_PIN_20_INIT_CFG
				,PORT_PIN_19_INIT_CFG,PORT_PIN_18_INIT_CFG,PORT_PIN_17_INIT_CFG,PORT_PIN_16_INIT_CFG);

	PORTD = CONC(PORT_PIN_31_INIT_CFG,PORT_PIN_30_INIT_CFG,PORT_PIN_29_INIT_CFG,PORT_PIN_28_INIT_CFG
				,PORT_PIN_27_INIT_CFG,PORT_PIN_26_INIT_CFG,PORT_PIN_25_INIT_CFG,PORT_PIN_24_INIT_CFG);

	#undef INPUT_HIGHIMPEDANCE
	#undef INTERNAL_PULLUP
	#undef OUTPUT_HIGH
	#undef OUTPUT_LOW

	#define INPUT_HIGHIMPEDANCE		0
	#define INTERNAL_PULLUP    		1
	#define OUTPUT_HIGH		    	2
	#define OUTPUT_LOW				3

}

/************************************PORT_SET************************************************
 *  * this function control the direction .
 * 1- check if the input pin is out of range
 * 2- check if the input direction is wrong
 * 3- if pin and direction in range calculate which port and which pin in this port
 * 4- switch the pin direction
 ********************************************************************************************/

Port_enuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum,u8 Copy_u8PinDirection)
{
	Port_enuErrorStatus loc_enuReturnStatus = Port_enuOK;// flag to detect if there is an error in the pin number or the direction

	u8 loc_u8Port; // variable that will carry which port is selected
	u8 loc_u8pin; // variable that will carry which pin is selected from this port

	if(Copy_u8PinNum>31)//MC is 32 PIN so check that the pin in range
	{
		loc_enuReturnStatus = Port_enuNOK;
	}
	else if(Copy_u8PinDirection>1)//to check if the input direction  is valid (output OR input)
	{
		loc_enuReturnStatus = Port_enuNOK;
	}
	else
	{
		 loc_u8Port = Copy_u8PinNum/8 ; // to calculate PORT number
		 loc_u8pin = Copy_u8PinNum%8 ; // to calculate the pin number in the port

		switch(loc_u8Port)
		{
			case PORTA_ :
						if(Copy_u8PinDirection == PORT_u8OUTPUT) // if the direction is output
						{
							SET_BIT(DDRA, loc_u8pin);//set DDRA which means that this pin is output
						}
						else
						{
							CLR_BIT(DDRA, loc_u8pin);//clear DDRA which means that this pin is input
						}
						break;

			case PORTB_ :
						if(Copy_u8PinDirection == PORT_u8OUTPUT)
						{
							SET_BIT(DDRB, loc_u8pin);
						}
						else
						{
							CLR_BIT(DDRB, loc_u8pin);
						}
						break;

			case PORTC_ :
						if(Copy_u8PinDirection == PORT_u8OUTPUT)
						{
							SET_BIT(DDRC, loc_u8pin);
						}
						else
						{
							CLR_BIT(DDRC, loc_u8pin);
						}
						break;

			case PORTD_ :
						if(Copy_u8PinDirection == PORT_u8OUTPUT)
						{
							SET_BIT(DDRD, loc_u8pin);
						}
						else
						{
							CLR_BIT(DDRD, loc_u8pin);
						}
						break;

		}
	}

	return loc_enuReturnStatus;
}

/************************************MODE_SET************************************************
 * this function control the pin mode and direction .
 * 1- check if the input pin is out of range
 * 2- check if the input mode is out of range
 * 3- if pin and mode in range calculate which port and which pin in this port
 * 4- switch which port is selected
 * 5- switch on the pin modes
 ********************************************************************************************/

Mode_enuErrorStatus  Port_enuSetPinMode(u8 Copy_u8PinNum,u8 Copy_u8PinMode)
{
	Mode_enuErrorStatus loc_enuReturnStatus = Mode_enuOK;// flag to detect if there is an error in the pin number or the mode

	u8 loc_u8Port;// variable that will carry which port is selected
	u8 loc_u8pin; // variable that will carry which pin is selected from this port

	if(Copy_u8PinNum>31)//MC is 32 PIN so check that the pin in range
	{
		loc_enuReturnStatus = Mode_enuNOK;
	}
	else if(Copy_u8PinMode>3)//to check the input mode is valid or not
	{
		loc_enuReturnStatus = Mode_enuNOK;
	}
	else
	{
		 loc_u8Port = Copy_u8PinNum/8 ;// to calculate PORT number
		 loc_u8pin = Copy_u8PinNum%8 ; // to calculate the pin number in the port

		switch(loc_u8Port)// check which port is selected
		{
			case PORTA_ :
						switch(Copy_u8PinMode)//check which mode is selected
						{
							    case INPUT_HIGHIMPEDANCE:
															CLR_BIT(DDRA, loc_u8pin);//clear DDRA which means that this pin is input
															CLR_BIT(PORTA, loc_u8pin);

															break;

								case INTERNAL_PULLUP	:
															CLR_BIT(DDRA, loc_u8pin);//clear DDRA which means that this pin is input
															SET_BIT(PORTA, loc_u8pin);

															break;

								case OUTPUT_HIGH 		:
															SET_BIT(DDRA, loc_u8pin);//set DDRA which means that this pin is output
															SET_BIT(PORTA, loc_u8pin);

															break;

								case OUTPUT_LOW 		:
															SET_BIT(DDRA, loc_u8pin);//set DDRA which means that this pin is output
															CLR_BIT(PORTA, loc_u8pin);

															break;

						}
						break;

			case PORTB_ :
						switch(Copy_u8PinMode)
						{
								case INPUT_HIGHIMPEDANCE:
															CLR_BIT(DDRB, loc_u8pin);
															CLR_BIT(PORTB, loc_u8pin);

															break;

								case INTERNAL_PULLUP	:
															CLR_BIT(DDRB, loc_u8pin);
															SET_BIT(PORTB, loc_u8pin);

															break;

								case OUTPUT_HIGH 		:
															SET_BIT(DDRB, loc_u8pin);
															SET_BIT(PORTB, loc_u8pin);

															break;

								case OUTPUT_LOW 		:
															SET_BIT(DDRB,loc_u8pin);
															CLR_BIT(PORTB,loc_u8pin);

															break;

						}
						break;

			case PORTC_ :
						switch(Copy_u8PinMode)
						{
								case INPUT_HIGHIMPEDANCE:
															CLR_BIT(DDRC, loc_u8pin);
															CLR_BIT(PORTC, loc_u8pin);

															break;

								case INTERNAL_PULLUP	:
															CLR_BIT(DDRC, loc_u8pin);
															SET_BIT(PORTC, loc_u8pin);

															break;

								case OUTPUT_HIGH 		:
															SET_BIT(DDRC, loc_u8pin);
															SET_BIT(PORTC, loc_u8pin);

															break;

								case OUTPUT_LOW 		:
															SET_BIT(DDRC, loc_u8pin);
															CLR_BIT(PORTC, loc_u8pin);

															break;

						}
						break;

			case PORTD_ :
						switch(Copy_u8PinMode)
						{
								case INPUT_HIGHIMPEDANCE:
															CLR_BIT(DDRD, loc_u8pin);
															CLR_BIT(PORTD, loc_u8pin);

															break;

								case INTERNAL_PULLUP	:
															CLR_BIT(DDRD, loc_u8pin);
															SET_BIT(PORTD, loc_u8pin);

															break;

								case OUTPUT_HIGH 		:
															SET_BIT(DDRD, loc_u8pin);
															SET_BIT(PORTD, loc_u8pin);

															break;

								case OUTPUT_LOW 		:
															SET_BIT(DDRD, loc_u8pin);
															CLR_BIT(PORTD, loc_u8pin);

															break;

						}
						break;
		}
	}

	return loc_enuReturnStatus;
}
