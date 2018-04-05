/**
  ******************************************************************************
  * @file    main.c
  * @author  Wölfer Martin
  * @version V1.0
  * @date    08-Oktober-2016
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f3xx.h"

#define PINS GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15

int main(void) {
	HAL_Init();
	LED_Init();
	while(1){
		HAL_GPIO_TogglePin(GPIOE, PINS);

		HAL_Delay(1000);
	}
}


void LED_Init(void){

	GPIO_InitTypeDef LED_Init;
	__HAL_RCC_GPIOE_CLK_ENABLE();

	LED_Init.Pin = PINS;

	//Set mode To Push Pull
    LED_Init.Mode = GPIO_MODE_OUTPUT_PP;
	LED_Init.Pull = GPIO_NOPULL;
	LED_Init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &LED_Init);
}
