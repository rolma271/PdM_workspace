/**
  ******************************************************************************
  * @file    API_delay.h
  * @author  Marco Rolon
  * @brief   Header for API_delay.c module
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DELAY_H
#define __API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


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
 * @brief  Write a new delay's duration
 * @param  delay Pointer to the delay structure
 * @param  duration Delay duration
 * @retval None
 */
void delayWrite(delay_t * delay, tick_t duration);

#endif /* __API_DELAY_H */
