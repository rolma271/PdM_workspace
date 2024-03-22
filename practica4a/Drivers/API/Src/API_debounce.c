/*
 * API_debounce.c
 *
 *  Created on: Mar 21, 2024
 *      Author: rolma
 */
#include "../../../Drivers/API/Inc/API_debounce.h"
#include "../../../Drivers/API/Inc/API_delay.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


#define DEBOUNCE_TICK_MS	  	40

/**
 *
 */
typedef enum
{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
}
debounceState_t;

/**
 *
 */
static debounceState_t debounceState;
static bool_t buttonIsPressed;

delay_t timerDebounce 		= {.startTime = 0, .duration = 0, .running = false};


void debounceFSM_init()
{
	debounceState = BUTTON_UP;
	buttonIsPressed = false;

	delayInit(&timerDebounce, DEBOUNCE_TICK_MS);
}

void debounceFSM_update()
{
	switch(debounceState)
	{
		case BUTTON_UP:
			if(BSP_PB_GetState(BUTTON_USER))
			{
				debounceState = BUTTON_FALLING;
				delayRead(&timerDebounce);
			}
			break;

		case BUTTON_FALLING:
			if (delayRead(&timerDebounce))
			{
				if(BSP_PB_GetState(BUTTON_USER))
				{
					buttonIsPressed = true;
					debounceState = BUTTON_DOWN;
				}
				else
				{
					debounceState = BUTTON_UP;
				}
			}
			break;

		case BUTTON_DOWN:
			if(!BSP_PB_GetState(BUTTON_USER))
			{
				debounceState = BUTTON_RAISING;
				delayRead(&timerDebounce);
			}
			break;

		case BUTTON_RAISING:
			if (delayRead(&timerDebounce))
			{
				if(!BSP_PB_GetState(BUTTON_USER))
				{
					buttonIsPressed = false;
					debounceState = BUTTON_UP;
				}
				else
				{
					debounceState = BUTTON_DOWN;
				}
			}
			break;

		default:
			// TODO error handler
			debounceState = BUTTON_UP;
			break;
	}
}

bool_t readKey()
{
	bool_t retVal = buttonIsPressed;

	buttonIsPressed = false;

	return retVal;
}



