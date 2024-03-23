/**
 ******************************************************************************
 * @file    API_debounce.c
 * @author 	Marco Rolon
 * @brief   Practica 4 - PdM CESE22
 ******************************************************************************
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>

typedef bool 		bool_t;

/**
 * Debounce prototypes
 */

/**
 * @brief  Debounce FSM initialization
 */
void debounceFSM_init();

/**
 * @brief  Debounce FSM update
 */
void debounceFSM_update();

/**
 * @brief 	Check the key status
 * @retval 	It returns true (once) if the button was pressed
 * */
bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
