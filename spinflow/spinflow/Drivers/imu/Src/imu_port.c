/**
 ******************************************************************************
 * @file    imu_port.c
 * @author 	Marco Rolon
 * @brief   IMU port
 ******************************************************************************
 */

#include "imu_port.h"

/**
 * I2C defines
 */
#define MPU_9250_ADDRESS		0x68
#define IMU_I2C_TIMEOUT_MS		1000

/**
 * Accelerometer & Gyro defines
 */
#define WHO_AM_I_9250_ANS 		0x71
#define WHO_AM_I          		0x75
#define GYRO_CONFIG       		0x1B
#define ACCEL_CONFIG      		0x1C
#define PWR_MGMT_1        		0x6B
#define ACCEL_XOUT_H      		0x3B

/**
 * Magnetometer
 */
#define AK8963_ADDRESS 			0x0C
#define AK8963_WHO_AM_I  		0x00
#define AK8963_WHOAMI_VALUE 	0x48

/**
 * @def IMU_GYRO_CAL_POINTS
 * @brief Number of data points used in gyroscope calibration.
 *
 * This defines the total number of readings taken to calculate the average offsets for gyroscope calibration. Using multiple
 * data points helps in averaging out sensor noise and errors to establish a more accurate baseline for sensor readings.
 */
#define IMU_GYRO_CAL_POINTS		10

/**
 * @enum gyroscopeFullScaleRange
 * @brief Enumerations for gyroscope full scale ranges.
 */
enum gyroscopeFullScaleRange
{
    GFSR_250DPS,  /*!< Full scale range ±250 degrees per second */
    GFSR_500DPS,  /*!< Full scale range ±500 degrees per second */
    GFSR_1000DPS, /*!< Full scale range ±1000 degrees per second */
    GFSR_2000DPS  /*!< Full scale range ±2000 degrees per second */
};

/**
 * @enum accelerometerFullScaleRange
 * @brief Enumerations for accelerometer full scale ranges.
 */
enum accelerometerFullScaleRange
{
    AFSR_2G,  /*!< Full scale range ±2g */
    AFSR_4G,  /*!< Full scale range ±4g */
    AFSR_8G,  /*!< Full scale range ±8g */
    AFSR_16G  /*!< Full scale range ±16g */
};

/**
 * @struct rawData_t
 * @brief Structure to store raw data from the IMU sensors.
 */
typedef struct
{
    int16_t ax; /*!< Raw accelerometer x-axis data */
    int16_t ay; /*!< Raw accelerometer y-axis data */
    int16_t az; /*!< Raw accelerometer z-axis data */
    int16_t gx; /*!< Raw gyroscope x-axis data */
    int16_t gy; /*!< Raw gyroscope y-axis data */
    int16_t gz; /*!< Raw gyroscope z-axis data */
    int16_t mx; /*!< Raw magnetometer x-axis data */
    int16_t my; /*!< Raw magnetometer y-axis data */
    int16_t mz; /*!< Raw magnetometer z-axis data */
    int16_t temp; /*!< Raw temperature data */
}
rawData_t;

/**
 * @var rawData
 * @brief Instance of rawData_t to hold raw sensor readings.
 */
static rawData_t rawData;

/**
 * @struct sensorData_t
 * @brief Structure to store processed sensor data from the IMU.
 */
typedef struct
{
    int16_t ax; /*!< Processed accelerometer x-axis data */
    int16_t ay; /*!< Processed accelerometer y-axis data */
    int16_t az; /*!< Processed accelerometer z-axis data */
    int16_t gx; /*!< Processed gyroscope x-axis data */
    int16_t gy; /*!< Processed gyroscope y-axis data */
    int16_t gz; /*!< Processed gyroscope z-axis data */
    int16_t mx; /*!< Processed magnetometer x-axis data */
    int16_t my; /*!< Processed magnetometer y-axis data */
    int16_t mz; /*!< Processed magnetometer z-axis data */
    int16_t temp; /*!< Processed temperature data */
}
sensorData_t;

/**
 * @var sensorData
 * @brief Instance of sensorData_t to hold processed sensor readings.
 */
static sensorData_t sensorData;

/**
 * @struct gyroCal_t
 * @brief Structure to hold calibration values for the gyroscope.
 */
typedef struct
{
    int16_t gx; /*!< Gyroscope x-axis calibration offset */
    int16_t gy; /*!< Gyroscope y-axis calibration offset */
    int16_t gz; /*!< Gyroscope z-axis calibration offset */
}
gyroCal_t;

/**
 * @var gyroCal
 * @brief Instance of gyroCal_t to store gyroscope offset data.
 */
static gyroCal_t gyroCal;

/**
 * @var accScaleFactor
 * @brief Scale factor for converting raw accelerometer data to g units.
 */
static float accScaleFactor;

/**
 * @var gyroScaleFactor
 * @brief Scale factor for converting raw gyroscope data to degrees/s .
 */
static float gyroScaleFactor;


/**
 * @var hi2c1
 * @brief Handle for I2C1 used to communicate with the IMU.
 */
static I2C_HandleTypeDef hi2c1;

/**
 * @var imu_i2cAddress
 * @brief I2C address of the IMU device.
 */
static uint8_t imu_i2cAddress = MPU_9250_ADDRESS;;

/**
 * @brief Initializes I2C1 interface for IMU communication.
 * @note This function configures the I2C1 hardware settings and must be called before any IMU communication.
 * @param None
 * @retval None
 */
static void I2C1_Init(void);

/**
 * @brief Initializes the IMU, checks connectivity, resets it, and configures full scale ranges for accelerometer and gyroscope.
 * @param accScale Accelerometer full scale range selection: 0 for ±2g, 1 for ±4g, 2 for ±8g, 3 for ±16g.
 * @param gyroScale Gyroscope full scale range selection: 0 for ±250°/s, 1 for ±500°/s, 2 for ±1000°/s, 3 for ±2000°/s.
 * @return true if initialization was successful, false otherwise.
 */
static bool imuPort_begin(uint8_t accScale, uint8_t gyroScale);

/**
 * @brief Reads raw sensor data from the IMU.
 * @note This function fetches raw data directly from the IMU registers.
 */
static void imuPort_readRawData();

/**
 * @brief Processes the raw data from the IMU to convert it into usable sensor values.
 * @note This function calculates sensor values in real-world units, applying necessary scale factors.
 */
static void imuPort_readProcessedData();

/**
 * @brief Writes the accelerometer full scale range to the IMU.
 * @param accScale Accelerometer full scale range: 0 for ±2g, 1 for ±4g, 2 for ±8g, 3 for ±16g.
 */
static void imuPort_writeAccFullScaleRange(uint8_t accScale);

/**
 * @brief Writes the gyroscope full scale range to the IMU.
 * @param gyroScale Gyroscope full scale range: 0 for ±250°/s, 1 for ±500°/s, 2 for ±1000°/s, 3 for ±2000°/s.
 */
static void imuPort_writeGyroFullScaleRange(uint8_t gyroScale);

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void);

 /**
 * IMU Port Functions
 */

bool imuPort_Init()
{
	I2C1_Init();
	if (imuPort_begin(AFSR_4G, GFSR_500DPS))
	{
		BSP_LED_Off(LED_IMU);
	    return true;
	}
	else
	{
		BSP_LED_On(LED_IMU);
		return false;
	}
}

bool imuPort_Check()
{
    uint8_t buffer[1];

    // Confirm device
    HAL_I2C_Mem_Read(&hi2c1, imu_i2cAddress<< 1, WHO_AM_I, 1, buffer, 1, IMU_I2C_TIMEOUT_MS);

    return (buffer[0] == WHO_AM_I_9250_ANS)? true : false;
}

bool imuPort_AccReadData(acc_t *acc)
{
	imuPort_readProcessedData();

	acc->ax = sensorData.ax;
	acc->ay = sensorData.ay;
	acc->az = sensorData.az;

	return true;
}

bool imuPort_TempReadData(temp_t *temp)
{
	// todo: not implemented yet
	return false;
}

bool imuPort_GyroReadData(gyro_t *gyro)
{
	imuPort_readProcessedData();

	gyro->gx = sensorData.gx;
	gyro->gy = sensorData.gy;
	gyro->gz = sensorData.gz;

	return true;
}

bool imuPort_MagnReadData(magn_t *magn)
{
	// todo: not implemented yet
	return false;
}

/// @brief Find offsets for each axis of gyroscope.
void imuPort_calibrateGyro()
{
    int32_t gx = 0;
    int32_t gy = 0;
    int32_t gz = 0;

    // Save specified number of points
    for (uint16_t i = 0; i < IMU_GYRO_CAL_POINTS; i++)
    {
        imuPort_readRawData();

        gx += rawData.gx;
        gy += rawData.gy;
        gz += rawData.gz;

        HAL_Delay(10); // @todo: improve this method
    }

    // Average the saved data points to find the gyroscope offset
    gyroCal.gx = (int16_t)(gx/IMU_GYRO_CAL_POINTS);
    gyroCal.gy = (int16_t)(gy/IMU_GYRO_CAL_POINTS);
    gyroCal.gz = (int16_t)(gz/IMU_GYRO_CAL_POINTS);
}

static bool imuPort_begin(uint8_t accScale, uint8_t gyroScale)
{
    // Initialize variables
    uint8_t buffer[1];

    // Confirm device
    HAL_I2C_Mem_Read(&hi2c1, imu_i2cAddress<< 1, WHO_AM_I, 1, buffer, 1, IMU_I2C_TIMEOUT_MS);


    if (buffer[0] == WHO_AM_I_9250_ANS)
    {
        // Startup / reset the sensor
    	buffer[0] = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, PWR_MGMT_1, 1, buffer, 1, IMU_I2C_TIMEOUT_MS);

        // Set the full scale ranges
        imuPort_writeAccFullScaleRange(accScale);

        imuPort_writeGyroFullScaleRange(gyroScale);
        imuPort_calibrateGyro();

        return true;
    }
    else
    {
        return false;
    }
}

static void imuPort_readRawData()
{
    // Init buffer
    uint8_t buffer[14];

    // Subroutine for reading the raw data
    HAL_I2C_Mem_Read(&hi2c1, imu_i2cAddress<< 1, ACCEL_XOUT_H, 1, buffer, 14, IMU_I2C_TIMEOUT_MS);

    // Bit shift the data
    rawData.ax = buffer[0] << 8 | buffer[1];
    rawData.ay = buffer[2] << 8 | buffer[3];
    rawData.az = buffer[4] << 8 | buffer[5];
    // temperature = buffer[6] << 8 | buffer[7];
    rawData.gx = buffer[8] << 8 | buffer[9];
    rawData.gy = buffer[10] << 8 | buffer[11];
    rawData.gz = buffer[12] << 8 | buffer[13];
}


static void imuPort_readProcessedData()
{
    // Get raw values from the IMU
    imuPort_readRawData();

    // Convert accelerometer values to g's
    sensorData.ax = rawData.ax/accScaleFactor;
    sensorData.ay = rawData.ay/accScaleFactor;
    sensorData.az = rawData.az/accScaleFactor;

    // Compensate offset and convert to deg/s
    sensorData.gx = (rawData.gx-gyroCal.gx)/gyroScaleFactor;
    sensorData.gy = (rawData.gy-gyroCal.gy)/gyroScaleFactor;
    sensorData.gz = (rawData.gz-gyroCal.gz)/gyroScaleFactor;
}

static void imuPort_writeAccFullScaleRange(uint8_t accScale)
{
    // Variable init
    uint8_t select;

    // Set the value
    switch (accScale)
    {
    case AFSR_2G:
        accScaleFactor = 16384.0;
        select = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, ACCEL_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;

    case AFSR_4G:
        accScaleFactor = 8192.0;
        select = 0x08;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, ACCEL_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;

    case AFSR_8G:
        accScaleFactor = 4096.0;
        select = 0x10;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, ACCEL_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;

    case AFSR_16G:
        accScaleFactor = 2048.0;
        select = 0x18;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, ACCEL_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;

    default:
        accScaleFactor = 8192.0;
        select = 0x08;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, ACCEL_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    }
}

static void imuPort_writeGyroFullScaleRange(uint8_t gyroScale)
{
    // Variable init
    uint8_t select;

    // Set the value
    switch (gyroScale)
    {
    case GFSR_250DPS:
        gyroScaleFactor = 131.0;
        select = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, GYRO_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    case GFSR_500DPS:
        gyroScaleFactor = 65.5;
        select = 0x08;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, GYRO_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    case GFSR_1000DPS:
        gyroScaleFactor = 32.8;
        select = 0x10;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, GYRO_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    case GFSR_2000DPS:
        gyroScaleFactor = 16.4;
        select = 0x18;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, GYRO_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    default:
        gyroScaleFactor = 65.5;
        select = 0x08;
        HAL_I2C_Mem_Write(&hi2c1, imu_i2cAddress<< 1, GYRO_CONFIG, 1, &select, 1, IMU_I2C_TIMEOUT_MS);
        break;
    }
}

static void I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void Error_Handler(void)
{
	/* Turn LED_IMU on */
	BSP_LED_On(LED_IMU);
	while (1)
	{
	}
}

