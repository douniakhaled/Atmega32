/*
 * Gpt.c
 *
 *  Created on: May 6, 2022
 *      Author: donia
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Std_types.h"
#include "Bit_utils.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt_prv.h"
#include "Gpt.h"

Gpt_Cbf Gpt_CallBackFunc[3];

void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
	if(ConfigPtr->Timer_Channel==Gpt_enuTimer0)
	{
		TCCR0 &= TCCR0_u8WVG_CLR;
		TCCR0 |= GPT_u8TIMER0_CTC_MODE;
		TIMSK &= TIMSK0_u8INTRPT_CLR;
		if(ConfigPtr->CallBack)
		{
			Gpt_CallBackFunc[TIMER0]=ConfigPtr->CallBack;

		}
	}
	else if(ConfigPtr->Timer_Channel==Gpt_enuTimer1)
		{
			TCCR1A &= TCCR1A_WGM_CLR_MSK;
			TCCR1B &= TCCR1B_WGM_CLR_MSK;

			TCCR1B |= GPT_u8TIMER1_CTC_MODE;
			TIMSK &= TIMSK1_u8INTRPT_CLR;
			if(ConfigPtr->CallBack)
			{
				Gpt_CallBackFunc[TIMER1]=ConfigPtr->CallBack;

			}
		}
	if(ConfigPtr->Timer_Channel==Gpt_enuTimer2)
		{
			TCCR2 &= TCCR0_u8WVG_CLR;
			TCCR2 |= GPT_u8TIMER2_CTC_MODE;
			TIMSK &= TIMSK2_u8INTRPT_CLR;
			if(ConfigPtr->CallBack)
			{
				Gpt_CallBackFunc[TIMER2]=ConfigPtr->CallBack;

			}
		}
}

Gpt_ValueType Gpt_GetTimeElapsed(u8 Copy_u8Channel)
{
	u8 Loc_u8TimeElapsed;
	switch(Copy_u8Channel)
	{
		case Gpt_enuTimer0:
							Loc_u8TimeElapsed=TCNT0;
							break;
		case Gpt_enuTimer1:
							Loc_u8TimeElapsed=TCNT1;
							break;
		case Gpt_enuTimer2:
							Loc_u8TimeElapsed=TCNT2;
							break;
	}
	return 	Loc_u8TimeElapsed;

}
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
	u8 Loc_u8TimeRemaining=0;
	switch(Channel)
	{
		case Gpt_enuTimer0:
							Loc_u8TimeRemaining=OCR0-TCNT0;
							break;
		case Gpt_enuTimer1:
							Loc_u8TimeRemaining=OCR1A-TCNT1;
							break;
		case Gpt_enuTimer2:
							Loc_u8TimeRemaining=OCR2-TCNT2;
							break;
	}
	return 	Loc_u8TimeRemaining;
}
void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value)
{
	switch(Channel)
		{
			case Gpt_enuTimer0:
								if (Value <= 0xFF)
								{
									OCR0=Value;
								}
								break;
			case Gpt_enuTimer1:
								OCR1A=Value;
								break;
			case Gpt_enuTimer2:
								if (Value <= 0xFF)
								{
									OCR2=Value;
								}
								break;
		}
}
void Gpt_StopTimer(Gpt_ChannelType Channel)
{

	switch(Channel)
		{
			case Gpt_enuTimer0:
								TCCR0=TCCR0_PRESCALER_CLR;
								break;
			case Gpt_enuTimer1:
								TCCR1B=TCCR1B_PRESCALER_CLR;
								break;
			case Gpt_enuTimer2:
								TCCR2=TCCR2_PRESCALER_CLR;
								break;
		}
}
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
	switch(Channel)
			{
				case Gpt_enuTimer0:
									TIMSK &= TIMSK0_u8INTRPT_CLR;
									TIMSK |= GPT_u8TIMER0_CTC_INTERRUPT;
									break;
				case Gpt_enuTimer1:
									TIMSK &= TIMSK1_u8INTRPT_CLR;
									TIMSK |= GPT_u8TIMER1_CTC_INTERRUPT;
									break;
				case Gpt_enuTimer2:
									TIMSK &= TIMSK2_u8INTRPT_CLR;
									TIMSK |= GPT_u8TIMER2_CTC_INTERRUPT;
									break;
			}
}
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
	switch(Channel)
			{
				case Gpt_enuTimer0:
									TIMSK &= TIMSK0_u8INTRPT_CLR;
									break;
				case Gpt_enuTimer1:
									TIMSK &= TIMSK1_u8INTRPT_CLR;
									break;
				case Gpt_enuTimer2:
									TIMSK &= TIMSK2_u8INTRPT_CLR;
									break;
			}
}

ISR(TIMER0_COMP_vect)
{
	if (Gpt_CallBackFunc[TIMER0])
	{
		Gpt_CallBackFunc[TIMER0]();
	}
}

ISR(TIMER1A_COMP_vect)
{
	if (Gpt_CallBackFunc[TIMER1])
	{
		Gpt_CallBackFunc[TIMER1]();
	}
}
ISR(TIMER2_COMP_vect)
{
	if (Gpt_CallBackFunc[TIMER2])
	{
		Gpt_CallBackFunc[TIMER2]();
	}
}
