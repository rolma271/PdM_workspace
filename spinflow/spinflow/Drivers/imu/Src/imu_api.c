/**
 ******************************************************************************
 * @file    imu_api.c
 *
 * @author 	Marco Rolon
 *
 * @brief   IMU API
 ******************************************************************************
 */

#include "imu_api.h"
#include "imu_port.h"
#include <stdlib.h>

/**
 * @struct imu_t
 * @brief Represents the sensor readings from the IMU.
 *
 * This structure holds the latest readings from the accelerometer, gyro, and magnetometer.
 */
typedef struct
{
    int16_t ax; /**< Accelerometer X-axis reading */
    int16_t ay; /**< Accelerometer Y-axis reading */
    int16_t az; /**< Accelerometer Z-axis reading */

    int16_t gx; /**< Gyroscope X-axis reading */
    int16_t gy; /**< Gyroscope Y-axis reading */
    int16_t gz; /**< Gyroscope Z-axis reading */

    int16_t mx; /**< Magnetometer X-axis reading */
    int16_t my; /**< Magnetometer Y-axis reading */
    int16_t mz; /**< Magnetometer Z-axis reading */

    int16_t temp; /**< Temperature reading */
}
imu_t;

static imu_t imu;

/**
 * @brief Clears the stored data from the IMU sensor.
 *
 * This function is used to reset the data in the IMU sensor
 * Typically called before starting new measurements.
 */
static void imu_ClearData();

/**
 * @brief Reads data from the IMU sensor.
 *
 * Retrieves the latest data from the IMU sensor and stores it in a globally accessible
 * structure or buffer. This function is called periodically to update the sensor readings.
 *
 * @return bool Returns true if the data was successfully read, false if there was an error
 * in reading the data.
 */
static bool imu_ReadData();

/**
 * @brief Processes the data retrieved from the IMU sensor.
 *
 * Analyzes the raw sensor data to compute useful information such as orientation,
 * acceleration, and angular velocity. This function include filtering and
 * noise reduction processes.
 *
 * @return bool Returns true if the data was successfully processed, false if the processing
 * failed due to corrupt or incomplete data.
 */
static bool imu_ProcessData();

/**
 * @brief Checks if the IMU detected motion.
 *
 * This function is typically used to determine whether the IMU detected motion or not.
 *
 * @return bool Returns true if there is activity, false if it is idle.
 */
static bool imu_IsActive();


bool imu_Init()
{

	if (imuPort_Init())
	{
		imu_ClearData();
		return true;
	}
	else
	{
		return false;
	}
}

bool imu_Check()
{
	return imuPort_Check();
}

bool imu_GetData()
{
	bool retVal = true;

	retVal &= imu_ReadData();
	retVal &= imu_ProcessData();

	return retVal;
}

imuState_t imu_State()
{
	if (imu_IsActive())
	{
		return IMU_ACTIVE;
	}
	else
	{
		return IMU_IDLE;
	}
}

imuSpin_t imu_SpinDirection()
{
	if ((abs(imu.gz) < IMU_SPIN_THRESHOLD))
	{
		return IMU_NO_SPIN;
	}
	else
	{
		if (imu.gz>0)
		{
			return IMU_POS_SPIN;
		}
		else
		{
			return IMU_NEG_SPIN;
		}
	}
}

static void imu_ClearData()
{
	// accelerometer
	imu.ax = 0;
	imu.ay = 0;
	imu.az = 0;

	// gyro
	imu.gx = 0;
	imu.gy = 0;
	imu.gz = 0;

	// magnetomer
	imu.mx = 0;
	imu.my = 0;
	imu.mz = 0;

	// temperature
	imu.temp = 0;
}

static bool imu_ReadData()
{
	gyro_t gyroData;

	if (imuPort_GyroReadData(&gyroData))
	{
		imu.gx = gyroData.gx;
		imu.gy = gyroData.gy;
		imu.gz = gyroData.gz;

		return true;
	}
	else
	{
		return false;
	}
}

static bool imu_ProcessData()
{
	// todo: implement function
	return true;
}

static bool imu_IsActive()
{
	return ((imu.gx > IMU_SPIN_THRESHOLD) || (imu.gy > IMU_SPIN_THRESHOLD) || (imu.gz > IMU_SPIN_THRESHOLD));
}
