/**
 ******************************************************************************
 * @file    API_delay.c
 * @author 	Marco Rolon
 * @brief   Practica 4 - PdM CESE22
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <../../../Drivers/API/Inc/API_delay.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/**
 * Delay Functions
 */

void delayInit(delay_t * delay, tick_t duration)
{
	if (delay == NULL)
		return;

	delay->duration = duration;
	delay->running = false;
	delay->startTime = 0;
}

bool_t delayRead(delay_t * delay)
{
	uint32_t elapsedTime = 0;
	bool_t returnValue = false;

	if (delay == NULL)
		return returnValue;

	if (delay->running == false)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		elapsedTime = HAL_GetTick() - delay->startTime;
		if (elapsedTime >= delay->duration)
		{
			delay->running = false;
			returnValue = true;
		}
	}

	return returnValue;
}

void delayWrite(delay_t * delay, tick_t duration)
{
	if (delay == NULL)
	{
		return;
	}

	delay->duration = duration;

//	if (delay->running == false)
//	{
//		delay->duration = duration;
//	}
}
