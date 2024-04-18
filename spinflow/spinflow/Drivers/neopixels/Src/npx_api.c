/**
 ******************************************************************************
 * @file    npx_api.c
 * @author 	Marco Rolon
 * @brief   NeoPixels API
 ******************************************************************************
 */

#include "npx_api.h"
#include "npx_port.h"

#define NPX_LED_VALUE 50

void npx_Init()
{
	npxPort_Init();
}

void npx_Clear()
{
	npxPort_ClearLEDs();
}

void npx_SetIdle()
{
	npxPort_SetGreen(NPX_LED_VALUE);
}

void npx_SetPositive()
{
	npxPort_SetRed(NPX_LED_VALUE);
}

void npx_SetNegative()
{
	npxPort_SetBlue(NPX_LED_VALUE);
}
