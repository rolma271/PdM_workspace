/**
 ******************************************************************************
 * @file    API_uart.h
 * @author  Marco Rolon
 * @brief   Header for API_UART.c module
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_UART_H
#define __API_UART_H

#include <stdint.h>
#include <stdbool.h>

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/**
 * Types
 */

typedef bool bool_t;

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
 * Prototypes
 */

/**
 * @brief  Parameters initialization
 * @retval TRUE if OK, FALSE otherwise
 */
bool_t uartInit();

/**
 * @brief  Sends a string (until NULL detection)
 * @param  uint8_t * pstring String
 * @retval None
 */
void uartSendString(uint8_t *pstring);

/**
 * @brief  Sends a string via UART
 * @param  uint8_t * pstring String
 * @param  uint16_t size String size
 * @retval None
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size);

/**
 * @brief  Receives a string via UART
 * @param  uint8_t * pstring String
 * @param  uint16_t size String size
 * @retval None
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);

#endif
