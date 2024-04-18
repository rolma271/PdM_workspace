/**
 ******************************************************************************
 * @file    API_uart.c
 * @author  Marco Rolon
 * @brief   Source for API_UART.c module
 */

#include "API_uart.h"  
#include <string.h>

/* Private defines -----------------------------------------------------------*/
#define UART_TX_TIMEOUT		1000
#define UART_RX_TIMEOUT		1000

/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

static const char motd[] =
		"\n\r+-+-+-+-+-+-+-+-+-+-+ +-+ +-+-+-+-+-+ +-+-+-+-+-+\n\r|C|E|S|E|2|2|/|P|d|M| |>| |M|a|r|c|o| |R|o|l|o|n|\n\r+-+-+-+-+-+-+-+-+-+-+ +-+ +-+-+-+-+-+ +-+-+-+-+-+\n\r\n\r";
static const char config[] = "\n\rUART config: 9600bps 8N1\n\r";

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief Prints UART config
 */
static void uartPrintConfig();

/**
 * @brief UART error handler
 */
static void uartErrorHandler();

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

bool_t uartInit()
{
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = NONE parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance = USARTx;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		uartErrorHandler();
		return false;
	}
	else
	{
		uartPrintConfig();
		return true;
	}
}

void uartSendString(uint8_t *pstring)
{
	if (HAL_UART_Transmit(&UartHandle, pstring, strlen((const char*) pstring),
			UART_TX_TIMEOUT) != HAL_OK)
	{
		uartErrorHandler();
	}
}

void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
	if (HAL_UART_Transmit(&UartHandle, pstring, size, UART_TX_TIMEOUT)
			!= HAL_OK)
	{
		uartErrorHandler();
	}
}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size)
{
	if (HAL_UART_Receive(&UartHandle, pstring, size, UART_RX_TIMEOUT) != HAL_OK)
	{
		uartErrorHandler();
	}
}

static void uartPrintConfig()
{
	uartSendString((uint8_t*) motd);
	uartSendString((uint8_t*) config);
}

static void uartErrorHandler()
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART3 and Loop until the end of transmission */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}
