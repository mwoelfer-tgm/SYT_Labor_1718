/**
  ******************************************************************************
  * @file    main.c
  * @author  Martin Wölfer
  * @version V1.0
  * @date    05-Oktober-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
			

int main(void) {
 HAL_Init();
 BSP_LED_Init(LED_RED);
 BSP_LED_On(LED_RED);
}
