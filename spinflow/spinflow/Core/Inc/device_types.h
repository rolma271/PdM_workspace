/**
 ******************************************************************************
 * @file    device_types.h
 *
 * @author 	Marco Rolón Radcenco
 *
 * @brief   Serial Log API header
 ******************************************************************************
 */
#ifndef DEVICE_TYPES_H_
#define DEVICE_TYPES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_msp.h"
#include "stm32f4xx_nucleo_144.h"

/**
 * @brief bool_t Boolean type
 */
typedef bool bool_t;

/**
 * @enum BSP_Led_TypeDef
 * @brief Identifies different types of LEDs used in the Board Support Package (BSP).
 *
 * This enumeration is used to specify different LEDs on the board for control purposes.
 * Each member represents a specific LED that can be manipulated through BSP functions, allowing for
 * targeted operations such as turning an LED on or off, toggling, or setting a specific behavior or pattern.
 */
typedef enum
{
	LED_APP, /**< LED associated with application-specific functions or indications. */
	LED_IMU, /**< LED for the Inertial Measurement Unit (IMU). */
	LED_NPX /**< LED for NeoPixels. */
} BSP_Led_TypeDef;

#endif /* DEVICE_TYPES_H_ */
