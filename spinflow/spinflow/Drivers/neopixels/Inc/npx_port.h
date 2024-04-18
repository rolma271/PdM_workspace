/**
 ******************************************************************************
 * @file    npx_port.h
 *
 * @author 	Marco Rolon
 *
 * @brief   NeoPixels port
 ******************************************************************************
 */

#ifndef NEOPIXELS_PORT_H
#define NEOPIXELS_PORT_H

#include <stdio.h>

#include "device_types.h"
#include "device_config.h"

/**
 * @def NEOPIXEL_LED_QTY
 * @brief Defines the length of the NeoPixel LEDs strip.
 */
#define NEOPIXEL_LED_QTY	DEVICE_NEOPIXEL_QUANTITY

/**
 * @struct pixel_t
 * @brief Structure to represent a single pixel's color in terms of red, green, and blue components or as a single uint32_t value.
 *
 * This structure uses a union to allow for easy manipulation of pixel colors either as individual
 * RGB components or as a single 32-bit unsigned integer, which is useful to send it serially as individual bits
 */
typedef struct
{
	union
	{
		struct
		{
			uint8_t blue; /**< Blue component of the color. */
			uint8_t red; /**< Red component of the color. */
			uint8_t green; /**< Green component of the color. */
		} colour; /**< Structure for individual color components. */

		uint32_t value; /**< Composite color value as a single uint32_t for DMA transfers. */
	};
} pixel_t;

/**
 * @brief Initializes NeoPixel LEDs.
 *
 * Sets up the hardware configuration required to control the NeoPixel LEDs
 */
void npxPort_Init();

/**
 * @brief Clears all the NeoPixel LEDs to their default state.
 *
 * Turns off all LEDs by setting their color to black (0,0,0).
 */
void npxPort_ClearLEDs();

/**
 * @brief Sets all NeoPixel LEDs to a specified red brightness.
 * @param bright Brightness value for the red component (0-255).
 *
 * Configures all LEDs to the specified red intensity, with other color components set to zero.
 */
void npxPort_SetRed(uint8_t bright);

/**
 * @brief Sets all NeoPixel LEDs to a specified green brightness.
 * @param bright Brightness value for the green component (0-255).
 *
 * Configures all LEDs to the specified green intensity, with other color components set to zero.
 */
void npxPort_SetGreen(uint8_t bright);

/**
 * @brief Sets all NeoPixel LEDs to a specified blue brightness.
 * @param bright Brightness value for the blue component (0-255).
 *
 * Configures all LEDs to the specified blue intensity, with other color components set to zero.
 */
void npxPort_SetBlue(uint8_t bright);

/**
 * @brief Updates the LED strip to reflect any changes made to their color or state.
 *
 * This function should be called after setting LED colors to send the updated color data
 * to the NeoPixel strip.
 */
void npxPort_SetLEDs();

#endif
