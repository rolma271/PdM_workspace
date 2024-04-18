/**
 ******************************************************************************
 * @file    imu_port.h
 *
 * @author 	Marco Rolon
 *
 * @brief   IMU Port
 ******************************************************************************
 */

#ifndef IMU_PORT_H
#define IMU_PORT_H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

#include "device_config.h"
#include "device_types.h"

/**
 * @struct acc_t
 * @brief Structure to hold accelerometer data.
 *
 * This structure is used to hold the raw data from the accelerometer, including
 * measurements along the X, Y, and Z axes.
 */
typedef struct
{
    int16_t ax; /**< Acceleration along the X-axis. */
    int16_t ay; /**< Acceleration along the Y-axis. */
    int16_t az; /**< Acceleration along the Z-axis. */
}
acc_t;

/**
 * @typedef temp_t
 * @brief Type definition for temperature measurements.
 *
 * Represents the temperature data measured in degrees Celsius, using
 * a 16-bit signed integer to accommodate the range and precision.
 */
typedef int16_t temp_t;

/**
 * @struct gyro_t
 * @brief Structure to hold gyroscope data.
 *
 * This structure contains raw data from the gyroscope, with measurements for
 * angular velocity along the X, Y, and Z axes.
 */
typedef struct
{
    int16_t gx; /**< Angular velocity along the X-axis. */
    int16_t gy; /**< Angular velocity along the Y-axis. */
    int16_t gz; /**< Angular velocity along the Z-axis. */
}
gyro_t;

/**
 * @struct magn_t
 * @brief Structure to hold magnetometer data.
 *
 * Used to store raw magnetometer data which measures magnetic fields along
 * the X, Y, and Z axes.
 */
typedef struct
{
    int16_t mx; /**< Magnetic field strength along the X-axis. */
    int16_t my; /**< Magnetic field strength along the Y-axis. */
    int16_t mz; /**< Magnetic field strength along the Z-axis. */
}
magn_t;

/**
 * @brief Initializes the IMU port.
 * @return True if initialization is successful, False otherwise.
 *
 * This function sets up the IMU hardware, ensuring it is ready for data
 * collection and processing.
 */
bool imuPort_Init();

/**
 * @brief Checks the IMU device status.
 * @return True if the device is functioning correctly, False otherwise.
 *
 * Performs a basic status check of the IMU to ensure it is operational.
 */
bool imuPort_Check();

/**
 * @brief Reads data from the accelerometer.
 * @param acc Pointer to acc_t structure where accelerometer data will be stored.
 * @return True if data is successfully read, False otherwise.
 *
 * Fetches the latest readings from the accelerometer and stores them in the provided acc_t structure.
 */
bool imuPort_AccReadData(acc_t *acc);

/**
 * @brief Reads temperature data.
 * @param temp Pointer to temp_t where temperature data will be stored.
 * @return True if data is successfully read, False otherwise.
 *
 * Retrieves the current temperature data from the IMU and stores it in the provided temp_t variable.
 */
bool imuPort_TempReadData(temp_t *temp);

/**
 * @brief Reads data from the gyroscope.
 * @param gyro Pointer to gyro_t structure where gyroscope data will be stored.
 * @return True if data is successfully read, False otherwise.
 *
 * Captures the latest gyroscope measurements and stores them in the specified gyro_t structure.
 */
bool imuPort_GyroReadData(gyro_t *gyro);

/**
 * @brief Reads data from the magnetometer.
 * @param magn Pointer to magn_t structure where magnetometer data will be stored.
 * @return True if data is successfully read, False otherwise.
 *
 * Retrieves magnetometer readings and fills the provided magn_t structure with these values.
 */
bool imuPort_MagnReadData(magn_t *magn);

/**
 * @brief Calibrates the gyroscope.
 *
 * Executes a calibration routine for the gyroscope to ensure accuracy in its readings.
 * Typically involves offsetting drift and other systematic errors.
 */
void imuPort_calibrateGyro();

#endif
