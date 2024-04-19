/**
 ******************************************************************************
 * @file    device_config.h
 *
 * @author 	Marco Rolón Radcenco
 *
 * @brief   Device config file
 ******************************************************************************
 */

#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_msp.h"
#include "stm32f4xx_nucleo_144.h"

/**
 * @def DEVICE_NAME
 * @brief Name of the device.
 *
 * This macro holds the string that identifies the name of the device across the system.
 * It is used in the serial log.
 */
#define DEVICE_NAME "SpinFlow"

/**
 * @def DEVICE_FIRMWARE_VERSION
 * @brief Firmware version of the device.
 *
 * This macro stores the version number of the device's firmware. It is crucial for compatibility checks,
 * update validations, and troubleshooting.
 */
#define DEVICE_FIRMWARE_VERSION "1.0"

/**
 * @def DEVICE_IMU_SPIN_THRESHOLD
 * @brief Threshold value for IMU spin detection.
 *
 * Defines the threshold for detecting rotational motion (spin) in the IMU sensor readings.
 * Spin detection is used in the application to trigger specific behaviors on NeoPixels color patterns.
 * The value is specified in degrees per second.
 */
#define DEVICE_IMU_SPIN_THRESHOLD 90

/**
 * @def DEVICE_NEOPIXEL_QUANTITY
 * @brief Number of NeoPixels in the device.
 *
 * Specifies the total number of NeoPixels used in the device. This is used to control and
 * manage the behavior of LED arrays in the system.
 */
#define DEVICE_NEOPIXEL_QUANTITY 20

/**
 * @def APP_START_DELAY_MS
 * @brief Delay duration in case there an error on IMU initialization and it need to be restarted, in milliseconds.
 */
#define APP_START_DELAY_MS 500

/**
 * @def APP_IDLE_DELAY_MS
 * @brief Delay duration between consecutive readings in idle state, in milliseconds.
 */
#define APP_IDLE_DELAY_MS 50

/**
 * @def APP_CONFIG_DELAY_MS
 * @brief Delay duration between consecutive readings in active state, used for NeoPixel configuration operations, in milliseconds.
 */
#define APP_CONFIG_DELAY_MS 100

/**
 * @def DEVICE_LOG_ENABLE
 * @brief Enable or disable logging feature.
 *
 * Controls whether logging is enabled (1) or disabled (0) within the device.
 */
#define DEVICE_LOG_ENABLE 1

/**
 * @def DEVICE_NEOPIXEL_INITIAL_SEQUENCE
 * @brief Enable or disable the NeoPixels initial colour sequence.
 *
 * Controls whether the sequence is enabled (1) or disabled (0).
 */
#define DEVICE_NEOPIXEL_INITIAL_SEQUENCE 1

#endif /* DEVICE_CONFIG_H_ */
