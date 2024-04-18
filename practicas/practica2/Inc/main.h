/**
  ******************************************************************************
  * @file    main.h
  * @author  Marco Rolon
  * @brief   Header for main.c module
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include <stdint.h>
#include <stdbool.h>


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/**
 * Delay types
 */

typedef uint32_t 	tick_t;
typedef bool 		bool_t;

typedef struct
{
   tick_t	startTime;
   tick_t 	duration;
   bool_t	running;
}
delay_t;

/**
 * Delay prototypes
 */

/**
 * @brief  Parameters initialization
 * @param  delay Delay structure
 * @param  duration Delay duration
 * @retval None
 */
void delayInit(delay_t * delay, tick_t duration);

/**
 * @brief  Check whether the time delay condition is met
 * @param  delay Pointer to the delay structure
 * @param  duration Delay duration
 * @retval True if delay condition is met
 *
 */
bool_t delayRead(delay_t * delay);

/**
 * @brief  Parameters initialisation
 * @param  delay Pointer to the delay structure
 * @param  duration Delay duration
 * @retval None
 */
void delayWrite(delay_t * delay, tick_t duration);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
