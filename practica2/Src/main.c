/**
 ******************************************************************************
 * @file    main.c
 * @author 	Marco Rolon
 * @author	Lucas Meoli
 * @brief   Practica 2 - PdM CESE22
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED_PATTERN_PERIOD_100_MS	  	100
#define LED_PATTERN_PERIOD_500_MS	  	500
#define LED_PATTERN_PERIOD_1000_MS	  	1000

#define LED_TOGGLE_LIMIT				10

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static tick_t 	ledPattern[] =
{
	LED_PATTERN_PERIOD_1000_MS,
	LED_PATTERN_PERIOD_500_MS,
	LED_PATTERN_PERIOD_100_MS
};

static const uint8_t ledPatternSize = sizeof(ledPattern)/sizeof(tick_t);

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/


int main(void)
{
	delay_t timer_LED1 		= {.startTime = 0, .duration = 0, .running = false};
	uint8_t ledToggleIndex	= 0;
	uint8_t ledPatternIndex	= 0;

	/* STM32F4xx HAL library initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);

	/* Initialize LED timer in 1 second */
	delayInit(&timer_LED1, LED_PATTERN_PERIOD_1000_MS);

	/* Infinite loop */
	while (1)
	{
		/* Part 2
		if(delayRead(&timer_LED1))
		{
		  BSP_LED_Toggle(LED1);
		  delayInit(&timer_LED1, LED_PATTERN_PERIOD_100_MS);
		}
		*/

		/* Part 3*/
	  	if (delayRead(&timer_LED1))
	  	{
			BSP_LED_Toggle(LED1); // toggle led

			ledToggleIndex = (ledToggleIndex+1)%LED_TOGGLE_LIMIT; // update and check toggle index value
			if(!ledToggleIndex)
			{
				ledPatternIndex = (ledPatternIndex+1)%ledPatternSize;
				delayWrite(&timer_LED1,ledPattern[ledPatternIndex]); // update pattern
			}
	  	}
	}
}

/**
 * Delay Functions
 */

void delayInit(delay_t * delay, tick_t duration)
{
	if (delay == NULL)
		return;

	delay->duration = duration;
	delay->running = false;
	delay->startTime = 0;
}

bool_t delayRead(delay_t * delay)
{
	uint32_t elapsedTime = 0;
	bool_t returnValue = false;

	if (delay == NULL)
		return returnValue;

	if (delay->running == false)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		elapsedTime = HAL_GetTick() - delay->startTime;
		if (elapsedTime >= delay->duration)
		{
			delay->running = false;
			returnValue = true;
		}
	}

	return returnValue;
}

void delayWrite(delay_t * delay, tick_t duration)
{
	if (delay == NULL)
	{
		return;
	}

	if (delay->running == false)
	{
		delay->duration = duration;
	}
}

/**
 * System
 */

static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
