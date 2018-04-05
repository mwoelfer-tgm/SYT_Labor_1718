/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  * Zusatz bei den Bindeoptionen:
  *  -u HAL_RCCEx_GetPeriphCLKConfig
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef UartHandle;

/**
 * Configure GPIOs for USART.
 * wei�er Draht (brauner Verbinder mit PA9-au�en) verbinden
 * gelber Draht (roter Verbinder mit PA10-innen) verbinden
 */
void USART1_GPIO_Configuration(void) {
	GPIO_InitTypeDef  GPIO_InitStruct;
	__GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * Configurare USART.
 */
void USART1_Configuration(void) {
	HAL_StatusTypeDef rc;
	USART1_GPIO_Configuration();
	__USART1_CLK_ENABLE();
	 /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = None
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USART1;
	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  rc = HAL_UART_Init(&UartHandle);
	  if(rc != HAL_OK) {
	    //Error_Handler();
		  BSP_LED_Toggle(LED_RED_2);
	  }
}


/**
 * Funktioniert, ausgetestet.
 */
int main(void) {
	char str1[100];
	int counter = 0;
	HAL_StatusTypeDef rc1;
	HAL_Init();
	BSP_LED_Init(LED_RED);
	BSP_LED_Init(LED_RED_2);
	BSP_LED_Init(LED_BLUE);
	USART1_Configuration();

	for(;;) {
	    BSP_LED_Toggle(LED_RED);
	    BSP_LED_Toggle(LED_RED_2);
	    sprintf(str1, "Hello Welt - No. %d!\n", counter++);
	    rc1 = HAL_UART_Transmit(&UartHandle, (uint8_t *)str1, strlen(str1), 5000);
	    if (rc1 != HAL_OK) {
	    	BSP_LED_Toggle(LED_BLUE);
	    }
	    HAL_Delay(1000);
	}
}
