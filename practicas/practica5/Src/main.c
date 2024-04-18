/**
 ******************************************************************************
 * @file    main.c
 * @author 	Marco Rolon
 * @brief   Practica 5 - PdM CESE22
 ******************************************************************************
 */

//* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "API_delay.h"
#include "API_debounce.h"

#include "API_uart.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
	BUTTON_RELEASED,
	BUTTON_PRESSED
}
buttonState_t;

/* Private define ------------------------------------------------------------*/
#define LED_BUTTON_PRESSED_TIME_MS	  	100
#define LED_BUTTON_RELEASED_TIME_MS	  	500

#define	LED_TOGGLE_COUNTS				10

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static buttonState_t buttonState = BUTTON_RELEASED;

delay_t timer_LED1 		= {.startTime = 0, .duration = 0, .running = false};

/* Private functions ---------------------------------------------------------*/

static void buttonFSM_update();
static void buttonEvent_Print();

static void SystemClock_Config(void);
static void Error_Handler(void);

int main(void)
{
	/* STM32F4xx HAL library initialization
	*/
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);
	/* Initialize BSP Button */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Initialize Button Debounce */
	debounceFSM_init();
	delayInit(&timer_LED1, LED_BUTTON_RELEASED_TIME_MS);

	/* Initialize UART */
	uartInit();

	/* Infinite loop */
	while (1)
	{
		debounceFSM_update();
		buttonFSM_update();
	}
}

static void buttonFSM_update()
{
	static int toggleCounter;

	switch(buttonState)
	{
		case BUTTON_RELEASED:
			if (delayRead(&timer_LED1))
			{
				BSP_LED_Toggle(LED1);
			}

			if (readKey())
			{
				delayWrite(&timer_LED1, LED_BUTTON_PRESSED_TIME_MS);
				buttonState = BUTTON_PRESSED;

				toggleCounter = 0;

				buttonEvent_Print();
			}
			break;

		case BUTTON_PRESSED:
			if (delayRead(&timer_LED1))
			{
				BSP_LED_Toggle(LED1);
				toggleCounter++;
			}

			if (toggleCounter>LED_TOGGLE_COUNTS)
			{
				delayWrite(&timer_LED1, LED_BUTTON_RELEASED_TIME_MS);
				buttonState = BUTTON_RELEASED;
			}
			break;
	}

}

static void buttonEvent_Print()
{
	uartSendString((uint8_t*)"\n\rButton Pressed\n\r");
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
