/*
 * Gpt.h
 *
 *  Created on: May 6, 2022
 *      Author: donia
 */

#ifndef GPT_H_
#define GPT_H_

typedef void (*Gpt_Cbf) (void);




typedef enum{
	NO_Clock_Select,
	Clock_Prescaler_0,
	Clock_Prescaler_8,
	Clock_Prescaler_64,
	Clock_Prescaler_256,
	Clock_Prescaler_1024,
	External_Clk_Falling,
	External_Clk_rising,
}Timer_tenuPrescaller;


typedef enum{
	Gpt_enuTimer0,
	Gpt_enuTimer1,
	Gpt_enuTimer2,
}Gpt_ChannelType;



typedef struct {
	Gpt_ChannelType Timer_Channel;
	Timer_tenuPrescaller Prescaler;
	Gpt_Cbf CallBack;
}Gpt_ConfigType;


void Gpt_Init(const Gpt_ConfigType* ConfigPtr);

void Gpt_DeInit(void);
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Copy_u8Channel);
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);
void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value);
void Gpt_StopTimer(Gpt_ChannelType Channel);
void Gpt_EnableNotification(Gpt_ChannelType Channel);
void Gpt_DisableNotification(Gpt_ChannelType Channel);

#endif /* GPT_H_ */
