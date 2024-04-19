/**
 ******************************************************************************
 * @file    npx_api.c
 *
 * @author 	Marco Rolón Radcenco
 *
 * @brief   NeoPixels API
 ******************************************************************************
 */

#include "npx_api.h"
#include "npx_port.h"

/**
 * @brief LED brightness
 */
#define NPX_LED_BRIGHTNESS 50

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
	npxPort_SetGreen(NPX_LED_BRIGHTNESS);
}

void npx_SetPositive()
{
	npxPort_SetRed(NPX_LED_BRIGHTNESS);
}

void npx_SetNegative()
{
	npxPort_SetBlue(NPX_LED_BRIGHTNESS);
}
