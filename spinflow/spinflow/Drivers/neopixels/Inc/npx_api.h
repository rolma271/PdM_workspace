/**
 ******************************************************************************
 * @file    npx_api.h
 * @author 	Marco Rolon
 * @brief   NeoPixels API
 ******************************************************************************
 */

#ifndef NEOPIXELS_H
#define NEOPIXELS_H

#include "device_config.h"
#include "device_types.h"

/**
 * @brief Initializes NeoPixels variables.
 *
 * This function initializes variables related to NeoPixels, preparing them for operation.
 * It should be called before any other NeoPixels-related functions are used.
 */
void npx_Init();

/**
 * @brief Clears NeoPixels to default values.
 *
 * This function clears NeoPixels, setting them to their default state.
 * It typically turns off all NeoPixels or sets them to a default color.
 */
void npx_Clear();

/**
 * @brief Sets NeoPixels to the idle state pattern.
 *
 * This function sets NeoPixels to indicate an idle state, typically with a neutral color or no activity indication.
 */
void npx_SetIdle();

/**
 * @brief Sets NeoPixels to indicate positive activity.
 *
 * This function sets NeoPixels to indicate positive activity, such as a positive spin direction.
 * Its changes the color or pattern of NeoPixels to indicate this activity visually.
 */
void npx_SetPositive();

/**
 * @brief Sets NeoPixels to indicate negative activity.
 *
 * This function sets NeoPixels to indicate negative activity, such as a negative spin direction.
 * Its changes the color or pattern of NeoPixels to indicate this activity visually.
 */
void npx_SetNegative();


#endif
