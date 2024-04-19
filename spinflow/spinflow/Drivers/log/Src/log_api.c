/**
 ******************************************************************************
 * @file    log_api.c
 *
 * @author 	Marco Rolon
 *
 * @brief   Serial Log API
 ******************************************************************************
 */

#include "log_api.h"
#include "API_uart.h"
#include "device_config.h"

/**
 * @brief Indicates the start of a logging message session.
 *
 * This function is used to mark the beginning of a new logging session.
 */
static void log_StartMsg();

bool_t log_Init()
{
	if (DEVICE_LOG_ENABLE)
	{
		if (uartInit())
		{
			log_StartMsg();
			return true;
		}
		else
		{
			return false;
		}
	}
	else // log disabled, returns true to avoid error
	{
		return true;
	}
}

bool_t log_SendString(logType_t logType, char *pstring)
{
	if (DEVICE_LOG_ENABLE)
	{
		// check string validity
		if (pstring == NULL)
		{
			uartSendString((uint8_t*) "<System Error: NULL String >\n\r");
			return false;
		}

		// log preamble
		switch (logType)
		{
		case LOG_APP_INFO:
			uartSendString((uint8_t*) "<APP Info: ");
			break;

		case LOG_APP_ERROR:
			uartSendString((uint8_t*) "<APP Error: ");
			break;

		case LOG_SYSTEM_ERROR:
			uartSendString((uint8_t*) "<System Error: ");
			break;

		default:
			uartSendString((uint8_t*) "<System Error: Log Type Unknown");
			return false;
			//break;
		}

		// string
		uartSendString((uint8_t*) pstring);

		// log postamble
		uartSendString((uint8_t*) ">\n\r");

		return true;
	}
	else // log disabled, returns true to avoid error
	{
		return true;
	}
}

static void log_StartMsg()
{
	// log start
	uartSendString((uint8_t*) "<Log Start!>\n\r");

	//device name
	uartSendString((uint8_t*) "<Device Name: ");
	uartSendString((uint8_t*) DEVICE_NAME);
	uartSendString((uint8_t*) ">\n\r");

	// device version
	uartSendString((uint8_t*) "<Device Version: ");
	uartSendString((uint8_t*) DEVICE_FIRMWARE_VERSION);
	uartSendString((uint8_t*) ">\n\r");

}
