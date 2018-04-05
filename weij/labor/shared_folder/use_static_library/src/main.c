/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
#include <stdio.h>
#include "file.h"

int main(void)
{
	HAL_Init();
	BSP_LED_Init(LED_ORANGE);
	initItm();
	for(;;){
		HAL_Delay(1000);
		printf("Hallo Welt\n");
		BSP_LED_Toggle(LED_ORANGE);
	}
}
