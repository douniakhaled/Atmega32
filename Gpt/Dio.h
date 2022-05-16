/*
 * Dio.h
 *
 *  Created on: Mar 9, 2022
 *      Author: donia
 */

#ifndef DIO_H_
#define DIO_H_



/************************************************************************************
 * 									DEFINE
 ************************************************************************************/

#define DEFAULT           OUTPUT_LOW      LOW

#define PORT_u8OUTPUT 		      1

#define INPUT_HIGHIMPEDANCE       0
#define INTERNAL_PULLUP           1
#define OUTPUT_HIGH			      2
#define OUTPUT_LOW			      3

#define PORT_A                     0
#define PORT_B                     1
#define PORT_C                     2
#define PORT_D                     3

#define LOW          	           0
#define HIGH                       1

#define DIO_u8PIN_00		       0
#define DIO_u8PIN_01               1
#define DIO_u8PIN_02               2
#define DIO_u8PIN_03               3
#define DIO_u8PIN_04               4
#define DIO_u8PIN_05               5
#define DIO_u8PIN_06               6
#define DIO_u8PIN_07               7
#define DIO_u8PIN_08               8
#define DIO_u8PIN_09               9
#define DIO_u8PIN_10              10
#define DIO_u8PIN_11   		      11
#define DIO_u8PIN_12   		      12
#define DIO_u8PIN_13 		      13
#define DIO_u8PIN_14              14
#define DIO_u8PIN_15              15
#define DIO_u8PIN_16              16
#define DIO_u8PIN_17              17
#define DIO_u8PIN_18              18
#define DIO_u8PIN_19              19
#define DIO_u8PIN_20   		      20
#define DIO_u8PIN_21   		      21
#define DIO_u8PIN_22   		      22
#define DIO_u8PIN_23 		      23
#define DIO_u8PIN_24              24
#define DIO_u8PIN_25              25
#define DIO_u8PIN_26              26
#define DIO_u8PIN_27              27
#define DIO_u8PIN_28              28
#define DIO_u8PIN_29              29
#define DIO_u8PIN_30   		      30
#define DIO_u8PIN_31   		      31
#define DIO_u8PIN_32   		      32



/************************************************************************************
 * 									ENUM
 ************************************************************************************/


typedef enum { // Pin ERROR Status
	Dio_Pin_enuOK,
	Dio_Pin_enuNOK,
	Dio_Pointer_enuNULL,
}Pin_enuErrorStatus;



/************************************************************************************
 * 								FUNCTION PROTOTYPE
 ************************************************************************************/

Pin_enuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId ,u8 Copy_u8level );

Pin_enuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId ,pu8 Add_pu8channellevel );

Pin_enuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId ,u8 Copy_u8Value );

Pin_enuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId ,pu8 Add_pu8Portlevel );

Pin_enuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannelId);

#endif /* DIO_H_ */
