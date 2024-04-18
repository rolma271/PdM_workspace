/**
 ******************************************************************************
 * @file    npx_port.c
 *
 * @author 	Marco Rolon
 *
 * @brief   NeoPixels port
 ******************************************************************************
 */

#include "npx_port.h"
#include "stm32f4xx_hal_tim.h"

/**
 * @def NEOPIXELS_LED_BIT_QTY
 * @brief Defines the number of bits per LED for encoding color information omn NeoPixels.
 *
 * Each NeoPixel LED requires 24 bits of data (8 bits each for red, green, and blue).
 */
#define NEOPIXELS_LED_BIT_QTY			24

/**
 * @def NEOPIXELS_BIT_SET_TIM_COUNTER
 * @brief Timer counter value to set a bit in the NeoPixel data stream.
 *
 * This value determines how long the data line must remain high to encode a logical '1'.
 */
#define NEOPIXELS_BIT_SET_TIM_COUNTER 	61

/**
 * @def NEOPIXELS_BIT_RESET_TIM_COUNTER
 * @brief Timer counter value to reset a bit in the NeoPixel data stream.
 *
 * This value determines how long the data line must remain high to encode a logical '0'.
 */
#define NEOPIXELS_BIT_RESET_TIM_COUNTER 29

/**
 * @def NEOPIXELS_DMA_BUFFER_LENGTH
 * @brief Total length of the DMA buffer needed to transmit the complete data for all LEDs.
 *
 * The buffer length is calculated based on the number of bits required for each LED and the total number of LEDs.
 */
#define NEOPIXELS_DMA_BUFFER_LENGTH (NEOPIXELS_LED_BIT_QTY * NEOPIXEL_LED_QTY)

/**
 * @var htim1
 * @brief Timer handle for controlling the timing specific operations for NeoPixel data transmission.
 */
TIM_HandleTypeDef htim1;

/**
 * @var hdma_tim1_ch1
 * @brief DMA handle for Timer 1, Channel 1, used to automate the data transmission to NeoPixels.
 */
DMA_HandleTypeDef hdma_tim1_ch1;

/**
 * @var pixels
 * @brief Array to store the color configuration for each NeoPixel LED.
 */
pixel_t pixels[NEOPIXEL_LED_QTY];

/**
 * @var dmaData
 * @brief DMA transfer buffer, populated based on the pixels array and used to send data to the NeoPixels via DMA.
 */
uint16_t dmaData[NEOPIXELS_DMA_BUFFER_LENGTH];

/**
 * @brief DMA Initialization Function
 * @param None
 * @retval None
 */
static void DMA_Init(void);

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void TIM1_Init(void);

/**
 * @brief NeoPixel initial sequence. Only for testing purposes.
 */
static void npxPort_initialSequence();

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
static void Error_Handler(void);

/**
 * NeoPixels Port Functions
 */

void npxPort_Init()
{
	DMA_Init();
	TIM1_Init();

	npxPort_initialSequence();
}

void npxPort_ClearLEDs()
{
	for (int i = 0; i < NEOPIXEL_LED_QTY; i++)
	{
		pixels[i].value = 0;
	}
	npxPort_SetLEDs();
}

void npxPort_SetRed(uint8_t bright)
{
	for (int i = 0; i < NEOPIXEL_LED_QTY; i++)
	{
		pixels[i].value = 0;
		pixels[i].colour.red = bright;
	}
	npxPort_SetLEDs();
}

void npxPort_SetGreen(uint8_t bright)
{
	for (int i = 0; i < NEOPIXEL_LED_QTY; i++)
	{
		pixels[i].value = 0;
		pixels[i].colour.green = bright;
	}
	npxPort_SetLEDs();
}

void npxPort_SetBlue(uint8_t bright)
{
	for (int i = 0; i < NEOPIXEL_LED_QTY; i++)
	{
		pixels[i].value = 0;
		pixels[i].colour.blue = bright;
	}
	npxPort_SetLEDs();
}

void npxPort_SetLEDs(void)
{
	uint32_t iPWM = 0;

	// Pixel to bit conversion for serial transmission
	for (int iPix = 0; iPix < NEOPIXEL_LED_QTY; iPix++)
	{
		for (int iBit = NEOPIXELS_LED_BIT_QTY - 1; iBit >= 0; iBit--)
		{
			if (pixels[iPix].value & (1 << iBit))
			{
				// Logic 1: Set the equivalent to a 68% of PWMs duty cycle
				dmaData[iPWM] = NEOPIXELS_BIT_SET_TIM_COUNTER;
			}
			else
			{
				// Logic 0: Set the equivalent to a 32% of PWMs duty cycle
				dmaData[iPWM] = NEOPIXELS_BIT_RESET_TIM_COUNTER;
			}
			iPWM++;
		}
	}

	//@todo: assert iPWM==NEOPIXELS_DMA_BUFFER_LENGTH

	// Send PWM signal via DMA controller
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*) dmaData, iPWM);
}

static void TIM1_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig =
	{ 0 };
	TIM_MasterConfigTypeDef sMasterConfig =
	{ 0 };
	TIM_OC_InitTypeDef sConfigOC =
	{ 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig =
	{ 0 };

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 90 - 1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_MspPostInit(&htim1);
}

void npxPort_initialSequence()
{
	npxPort_ClearLEDs();
	HAL_Delay(100);

	npxPort_SetRed(0);
	HAL_Delay(100);
	npxPort_SetRed(50);
	HAL_Delay(100);
	npxPort_SetRed(100);
	HAL_Delay(100);
	npxPort_SetRed(150);
	HAL_Delay(100);
	npxPort_SetRed(200);
	HAL_Delay(100);
	npxPort_SetRed(250);
	HAL_Delay(100);

	npxPort_SetGreen(0);
	HAL_Delay(100);
	npxPort_SetGreen(50);
	HAL_Delay(100);
	npxPort_SetGreen(100);
	HAL_Delay(100);
	npxPort_SetGreen(150);
	HAL_Delay(100);
	npxPort_SetGreen(200);
	HAL_Delay(100);
	npxPort_SetGreen(250);
	HAL_Delay(100);

	npxPort_SetBlue(0);
	HAL_Delay(100);
	npxPort_SetBlue(50);
	HAL_Delay(100);
	npxPort_SetBlue(100);
	HAL_Delay(100);
	npxPort_SetBlue(150);
	HAL_Delay(100);
	npxPort_SetBlue(200);
	HAL_Delay(100);
	npxPort_SetBlue(250);
	HAL_Delay(100);

	npxPort_ClearLEDs();
	HAL_Delay(100);
}

static void DMA_Init(void)
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
}

static void Error_Handler(void)
{
	/* Turn LED_NPX on */
	BSP_LED_On(LED_NPX);
	while (1)
	{
	}
}

