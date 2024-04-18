/**
 ******************************************************************************
 * @file    imu_api.h
 *
 * @author 	Marco Rolon
 *
 * @brief   IMU API header
 ******************************************************************************
 */

#ifndef IMU_H
#define IMU_H

#include "device_config.h"
#include "device_types.h"

/**
 * @def IMU_SPIN_THRESHOLD
 * @brief Defines the threshold value for detecting spin in the IMU.
 *
 * This threshold is used to determine whether the IMU's rotational motion
 * is significant enough to be considered a spin. The value is measured in
 * degrees per second.
 */
#define IMU_SPIN_THRESHOLD			DEVICE_IMU_SPIN_THRESHOLD

/**
 * @enum imuState_t
 * @brief Defines the operational state of the IMU.
 */
typedef enum
{
	IMU_IDLE, /**< IMU is in idle state, but actively measuring. */
	IMU_ACTIVE /**< IMU is active and taking measurements. */
} imuState_t;

/**
 * @enum imuSpin_t
 * @brief Defines the spin state of the IMU.
 */
typedef enum
{
	IMU_NO_SPIN, /**< IMU is not spinning. */
	IMU_POS_SPIN, /**< IMU is spinning in a positive direction. */
	IMU_NEG_SPIN /**< IMU is spinning in a negative direction. */
} imuSpin_t;

/**
 * @brief Initializes the IMU sensor and related variables.
 *
 * Call this function before attempting to read data from the IMU to ensure
 * all components are configured and ready.
 *
 * @return bool Returns true if the initialization was successful, false otherwise.
 */
bool imu_Init();

/**
 * @brief Performs a quick self-check to verify IMU functionality.
 *
 * This function can be used to check the operational status of the IMU.
 *
 * @return bool Returns true if the IMU is functioning correctly, false if there is an error.
 */
bool imu_Check();

/**
 * @brief Retrieves the latest sensor data from the IMU.
 *
 * Updates the global IMU data structure with the latest readings from the
 * accelerometer, gyro, and magnetometer.
 *
 * @return bool Returns true if data was successfully retrieved, false otherwise.
 */
bool imu_GetData();

/**
 * @brief Retrieves the current state of the IMU.
 *
 * This function is used to check whether the IMU is currently active or idle.
 *
 * @return imuState_t The current state of the IMU (either IMU_IDLE or IMU_ACTIVE).
 */
imuState_t imu_State();

/**
 * @brief Determines the current spin direction of the IMU.
 *
 * This function checks the gyroscope data to determine the direction
 * of spin.
 *
 * @return imuSpin_t The current spin direction of the IMU, indicating no spin,
 * positive spin, or negative spin.
 */
imuSpin_t imu_SpinDirection();

#endif
