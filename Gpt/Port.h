/*
 * PORT.h
 *
 *  Created on: Mar 9, 2022
 *      Author: donia
 */

#ifndef PORT_H_
#define PORT_H_

/************************************************************************************
 * 									DEFINE
 ************************************************************************************/


#define PORT_u8OUTPUT 		1

#define INPUT_HIGHIMPEDANCE		0
#define INTERNAL_PULLUP    		1
#define OUTPUT_HIGH		    	2
#define OUTPUT_LOW				3

#define PORTA_               0
#define PORTB_               1
#define PORTC_               2
#define PORTD_               3


/************************************************************************************
 * 									ENUM
 ************************************************************************************/

typedef enum { // PORT ERROR Status
	Port_enuOK,
	Port_enuNOK,
}Port_enuErrorStatus;

typedef enum { // MODE ERROR Status
	Mode_enuOK,
	Mode_enuNOK,
}Mode_enuErrorStatus ;

/************************************************************************************
 * 								FUNCTION PROTOTYPE
 ************************************************************************************/
void Port_VidInit(void);
Port_enuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum,u8 Copy_u8PinDirection);
Mode_enuErrorStatus Port_enuSetPinMode(u8 Copy_u8PinNum,u8 Copy_u8PinMode);

#endif /* PORT_H_ */
