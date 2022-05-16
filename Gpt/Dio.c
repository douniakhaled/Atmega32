/*
 * Dio.c
 *
 *  Created on: Mar 9, 2022
 *      Author: donia
 */

#ifndef DIO_C_
#define DIO_C_

#include <avr/io.h>
#include "Std_types.h"
#include "Bit_utils.h"
#include "Dio.h"
#include <stddef.h>

/************************************Dio Write Channel************************************************
 *  function to write on channel (SET OR CLEAR)
 * 1- check if the input pin is out of range
 * 2- check the input level (SET 1 OR CLEAR 0 )
 * 3- if pin and level in range calculate which port and which pin in this port
 * 4- switch which port is selected
 * 5- check if the level is SET OR CLEAR and write it
 ********************************************************************************************/

Pin_enuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId ,u8 Copy_u8level )
{
		Pin_enuErrorStatus loc_enuReturnStatus = Dio_Pin_enuOK;// flag to detect if there is an error in the pin number or the direction

		u8 loc_u8Port; // variable that will carry which port is selected
		u8 loc_u8pin; // variable that will carry which pin is selected from this port

		if(Copy_u8ChannelId>31)//MC is 32 PIN so check that the pin in range
		{
			loc_enuReturnStatus = Dio_Pin_enuNOK;
		}
		else if(Copy_u8level>1)//to check if the input level is valid (set OR clear)
		{
			loc_enuReturnStatus = Dio_Pin_enuNOK;
		}
		else
		{
			 loc_u8Port = Copy_u8ChannelId/8 ; // to calculate PORT number
			 loc_u8pin = Copy_u8ChannelId%8 ; // to calculate the pin number in the port

			switch(loc_u8Port)
			{
				case PORT_A :
							if(Copy_u8level == HIGH) // check if the input level is SET OR CLEAR
							{

								SET_BIT(PORTA,loc_u8pin); //write 1 on the pin in PORTA
							}
							else
							{
								CLR_BIT(PORTA, loc_u8pin);//write 0 on the pin in PORTA
							}
							break;

				case PORT_B :
							if(Copy_u8level == HIGH)
							{
								SET_BIT(PORTB, loc_u8pin);
							}
							else
							{
								CLR_BIT(PORTB,loc_u8pin);
							}
							break;

				case PORT_C :
							if(Copy_u8level == HIGH)
							{
								SET_BIT(PORTC, loc_u8pin);
							}
							else
							{
								CLR_BIT(PORTC, loc_u8pin);
							}
							break;

				case PORT_D :
							if(Copy_u8level == HIGH)
							{
								SET_BIT(PORTD, loc_u8pin);
							}
							else
							{
								CLR_BIT(PORTD, loc_u8pin);
							}
							break;
			}
		}
		return loc_enuReturnStatus; // return error status
}


/************************************Dio Read Channel************************************************
 * this function to read channel
 * 1- check if the input pin is out of range
 * 2- check if the pointer = NULL
 * 3- if pin in range and pointer not = NULL calculate which port and which pin in this port
 * 4- switch on the port and get the value from the pin
 ********************************************************************************************/


Pin_enuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId ,pu8 Add_pu8channellevel )
{
	Pin_enuErrorStatus loc_enuReturnStatus = Dio_Pin_enuOK;// flag to detect if there is an error in the pin number or the direction

	u8 loc_u8Port; // variable that will carry which port is selected
	u8 loc_u8pin; // variable that will carry which pin is selected from this port


	if(Copy_u8ChannelId>31)//MC is 32 PIN so check that the pin in range
	{
		loc_enuReturnStatus = Dio_Pin_enuNOK;
	}
	else if(Add_pu8channellevel == NULL)
	{
		loc_enuReturnStatus = Dio_Pointer_enuNULL;
	}
	else
	{
		 loc_u8Port = Copy_u8ChannelId/8 ; // to calculate PORT number
		 loc_u8pin = Copy_u8ChannelId%8 ; // to calculate the pin number in the port

		switch(loc_u8Port)
		{
			case PORT_A :
						 *Add_pu8channellevel = (GET_BIT(PINA,loc_u8pin));//pointer to u8 which will carry the value of the pin
						 break;

			case PORT_B :
						*Add_pu8channellevel = (GET_BIT(PINB,loc_u8pin));
						break;

			case PORT_C :
						*Add_pu8channellevel = (GET_BIT(PINC,loc_u8pin));
						break;

			case PORT_D :
						*Add_pu8channellevel = (GET_BIT(PIND,loc_u8pin));
						break;
		}
	}

	return loc_enuReturnStatus;
}

/************************************Dio Write Port************************************************
 *  function to write on PORT
 * 1- check if the input port is out of range
 * 2- check the input value
 * 3- if port and value in range calculate which port and which pin in this port
 * 4- switch which port is selected and write the value
 ********************************************************************************************/

Pin_enuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId ,u8 Copy_u8Value )
{
		Pin_enuErrorStatus loc_enuReturnStatus = Dio_Pin_enuOK;// flag to detect if there is an error in the pin number or the direction


		if(Copy_u8PortId >3)//check the input port
		{
			loc_enuReturnStatus = Dio_Pin_enuNOK;
		}
		else if(Copy_u8Value>255)
		{
			loc_enuReturnStatus = Dio_Pin_enuNOK;
		}
		else
		{

			switch(Copy_u8PortId)
			{
				case PORT_A :
							ASSIGN_REG(PORTA,Copy_u8Value);
							break;

				case PORT_B :
							ASSIGN_REG(PORTB,Copy_u8Value);
							break;

				case PORT_C :
							ASSIGN_REG(PORTC,Copy_u8Value);
							break;

				case PORT_D :
							ASSIGN_REG(PORTD,Copy_u8Value);
							break;
			}
		}

		return loc_enuReturnStatus;
}

/************************************Dio Read Port************************************************
 * this function to read PORT
 * 1- check if the input pin is out of range
 * 2- check if the pointer = NULL
 * 3- if pin in range and pointer not = NULL calculate which port and which pin in this port
 * 4- switch on the port and get the value
 ********************************************************************************************/

Pin_enuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId ,pu8 Add_pu8Portlevel )
{
	Pin_enuErrorStatus loc_enuReturnStatus = Dio_Pin_enuOK;// flag to detect if there is an error in the pin number


	if(Copy_u8PortId >3)//MC is 32 PIN so check that the pin in range
	{
		loc_enuReturnStatus = Dio_Pin_enuNOK;
	}
	else if(Add_pu8Portlevel == NULL)
	{
		loc_enuReturnStatus =Dio_Pointer_enuNULL;
	}
	else
	{

		switch(Copy_u8PortId)
		{
			case PORT_A :
						*Add_pu8Portlevel = GET_REG(PINA);
						break;

			case PORT_B :
						*Add_pu8Portlevel = GET_REG(PINB);
						break;

			case PORT_C :
						*Add_pu8Portlevel = GET_REG(PINC);
						break;

			case PORT_D :
						*Add_pu8Portlevel = GET_REG(PIND);
						break;
		}
	}

	return loc_enuReturnStatus;
}

/************************************Dio Flip ChannelT************************************************
 *  function to flip the channel (SET OR CLEAR)
 * 1- check if the input pin is out of range
 * 2- if pin  in range calculate which port and which pin in this port
 * 3- switch which port is selected
 * 4- Flip the channel
 ********************************************************************************************/

Pin_enuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannelId)
{
	Pin_enuErrorStatus loc_enuReturnStatus = Dio_Pin_enuOK;// flag to detect if there is an error in the pin number or the direction

	u8 loc_u8Port; // variable that will carry which port is selected
	u8 loc_u8pin; // variable that will carry which pin is selected from this port

	if(Copy_u8ChannelId>31)//MC is 32 PIN so check that the pin in range
	{
		loc_enuReturnStatus = Dio_Pin_enuNOK;
	}
	else
	{
		 loc_u8Port = Copy_u8ChannelId/8 ; // to calculate PORT number
		 loc_u8pin = Copy_u8ChannelId%8 ; // to calculate the pin number in the port

		switch(loc_u8Port)
		{

			case PORT_A :
						TGL_BIT(PORTA,loc_u8pin);
						break;

			case PORT_B :
						TGL_BIT(PORTB,loc_u8pin);
						break;

			case PORT_C :
						TGL_BIT(PORTC,loc_u8pin);
						break;

			case PORT_D :
						TGL_BIT(PORTD,loc_u8pin);
						break;
		}
	}

	return loc_enuReturnStatus;
}


#endif /* DIO_C_ */
