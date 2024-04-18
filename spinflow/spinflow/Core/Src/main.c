/**
 ******************************************************************************
 * @file    main.c
 *
 * @author 	Marco Rolón Radcenco
 *
 * @brief   SpinFlow - PdM CESE22
 ******************************************************************************
 */

//* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "imu_api.h"
#include "npx_api.h"

#include "log_api.h"
#include "API_delay.h"

/* Private typedef -----------------------------------------------------------*/

/**
 * @enum appState_t
 * @brief Enumerates the states of the application's finite state machine (FSM).
 *
 * This enumeration defines the various states that the application can be in
 * at any given time. The FSM handles transitions between these states based on
 * internal and external events.
 */
typedef enum
{
	APP_START, /**< Initial state of the application upon power-up or reset. */
	APP_START_DELAY, /**< Delay state after start, before the application becomes fully active. */
	APP_IDLE, /**< Idle state where the application is waiting for motion detection. */
	APP_ACTIVE, /**< Active state indicating the application is currently processing tasks. */
	APP_POS_SPIN, /**< State indicating the application is experiencing a positive spin. */
	APP_NEG_SPIN, /**< State indicating the application is experiencing a negative spin. */
	APP_DELAY /**< Delay state for NeoPixels operation. */
} appState_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 * @var appTimer
 * @brief Timer structure for managing application-specific timings.
 *
 * This timer is used throughout the application to manage delays, timeouts, and intervals in various
 * processes and state transitions. It is a structure containing the start time, duration, and a flag
 * indicating whether the timer is currently running.
 */
static delay_t appTimer =
{ .startTime = 0, .duration = 0, .running = false };

/**
 * @var appState
 * @brief Holds the current state of the application's finite state machine (FSM).
 *
 * This static variable is used internally to keep track of the current state of the application's FSM.
 */
static appState_t appState;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Initializes the Application FSM and related variables.
 *
 * This function performs all necessary initializations for the application's finite state machine (FSM)
 * and associated variables. It sets up initial states, configures dependencies, and prepares the application
 * to enter its main operational loop. This function should be called once at startup.
 */
static void app_Init();

/**
 * @brief Updates the Application FSM based on system events and state changes.
 *
 * This function is called repeatedly within the main loop and is responsible for handling
 * transitions and actions within the application's FSM. It checks for system events, updates the state
 * of the FSM as required, and executes actions based on the current state of the application.
 */
static void app_Tasks();

/**
 * @brief Handles the application logic when no spin is detected.
 *
 * This function is executed when the FSM is in a state where no spinning action is detected.
 * It may perform tasks such as monitoring for changes or preparing the system for new inputs.
 */
static void app_noSpinDetected();

/**
 * @brief Handles the application logic for positive spin scenarios.
 *
 * This function is called when a positive spin is detected by the system. It executes the necessary
 * actions corresponding to a positive spin, such as updating display elements, logging, or other
 * system responses tailored to positive spin conditions.
 */
static void app_positiveSpinDetected();

/**
 * @brief Handles the application logic for negative spin scenarios.
 *
 * This function is executed when a negative spin is detected by the system. Similar to the positive spin handler,
 * it manages the responses and actions specific to negative spin conditions, including user interface updates,
 * logging events, or adjusting operational parameters.
 */
static void app_negativeSpinDetected();

/**
 * @brief System Clock Configuration
 * @retval None
 */
static void SystemClock_Config(void);

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void GPIO_Init(void);

/**
 * @brief BSP LEDs Initialization Function
 * @param None
 * @retval None
 */
static void led_init(void);

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void);

/**
 *
 * Application
 *
 */

int main(void)
{
	/* System initialization */
	HAL_Init();
	SystemClock_Config();
	GPIO_Init();

	/*BSP LEDs init*/
	led_init();

	/* Initialize App */
	app_Init();

	/* Infinite loop */
	while (1)
	{
		app_Tasks();
	}
}

static void app_Init()
{
	// init peripherals
	npx_Init();
	imu_Init();
	log_Init();

	// start app
	appState = APP_START;
	log_SendString(LOG_APP_INFO, "App start");
	delayInit(&appTimer, APP_START_DELAY_MS);
}

static void app_Tasks()
{
	switch (appState)
	{
	case APP_START:
		if (imu_Check())
		{
			log_SendString(LOG_APP_INFO, "IMU ok");
			BSP_LED_Off(LED_IMU); // reset LED to indicate success

			appState = APP_IDLE;
			delayWrite(&appTimer, APP_IDLE_DELAY_MS);
		}
		else
		{
			log_SendString(LOG_APP_INFO, "IMU error");
			BSP_LED_On(LED_IMU); // set LED to indicate error

			appState = APP_START_DELAY;
		}
		break;

	case APP_START_DELAY:
		if (delayRead(&appTimer))
		{
			appState = APP_START;
		}
		break;

	case APP_IDLE:
		if (delayRead(&appTimer))
		{
			imu_GetData();
			switch (imu_State())
			{
			case IMU_IDLE:
				log_SendString(LOG_APP_INFO, "Idle");
				//appState = APP_IDLE;
				app_noSpinDetected();
				break;

			case IMU_ACTIVE:
				log_SendString(LOG_APP_INFO, "Active");
				appState = APP_ACTIVE;
				break;

			default:
				log_SendString(LOG_APP_ERROR, "IMU state error");
				Error_Handler();
				break;
			}
		}
		break;

	case APP_ACTIVE:
		switch (imu_SpinDirection())
		{
		case IMU_NO_SPIN:
			log_SendString(LOG_APP_INFO, "No spin detected");
			appState = APP_IDLE;
			delayWrite(&appTimer, APP_IDLE_DELAY_MS);
			break;

		case IMU_POS_SPIN:
			log_SendString(LOG_APP_INFO, "Positive spin detected");
			appState = APP_POS_SPIN;
			break;

		case IMU_NEG_SPIN:
			log_SendString(LOG_APP_INFO, "Negative spin detected");
			appState = APP_NEG_SPIN;
			break;

		default:
			log_SendString(LOG_APP_ERROR, "IMU spin error");
			Error_Handler();
			break;
		}
		break;

	case APP_POS_SPIN:
		app_positiveSpinDetected();
		appState = APP_DELAY;
		delayWrite(&appTimer, APP_CONFIG_DELAY_MS);
		break;

	case APP_NEG_SPIN:
		app_negativeSpinDetected();
		appState = APP_DELAY;
		delayWrite(&appTimer, APP_CONFIG_DELAY_MS);
		break;

	case APP_DELAY:
		if (delayRead(&appTimer))
		{
			appState = APP_ACTIVE;
			imu_GetData();
		}
		break;

	default:
		log_SendString(LOG_APP_ERROR, "App unknown state!");
		Error_Handler();
		break;
	}
}

static void app_noSpinDetected()
{
	npx_SetIdle();
	BSP_LED_Off(LED_NPX);  // reset LED to indicate inactivity
}

static void app_positiveSpinDetected()
{
	npx_SetPositive();
	BSP_LED_Toggle(LED_NPX); // toggle LED to indicate activity
}

static void app_negativeSpinDetected()
{
	npx_SetNegative();
	BSP_LED_Toggle(LED_NPX); // toggle LED to indicate activity
}

/**
 * System
 */

static void Error_Handler(void)
{
	/* Turn LED_APP on */
	BSP_LED_On(LED_APP);
	while (1)
	{
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

static void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin | LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : USER_Btn_Pin */
	GPIO_InitStruct.Pin = USER_Btn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
	GPIO_InitStruct.Pin = RMII_MDC_Pin | RMII_RXD0_Pin | RMII_RXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
	GPIO_InitStruct.Pin = RMII_REF_CLK_Pin | RMII_MDIO_Pin | RMII_CRS_DV_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	GPIO_InitStruct.Pin = LD1_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : RMII_TXD1_Pin */
	GPIO_InitStruct.Pin = RMII_TXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_PowerSwitchOn_Pin */
	GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_OverCurrent_Pin */
	GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
	GPIO_InitStruct.Pin = RMII_TX_EN_Pin | RMII_TXD0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

static void led_init(void)
{
	BSP_LED_Init(LED_APP);
	BSP_LED_Init(LED_IMU);
	BSP_LED_Init(LED_NPX);

	BSP_LED_Off(LED_APP);
	BSP_LED_Off(LED_IMU);
	BSP_LED_Off(LED_NPX);
}
