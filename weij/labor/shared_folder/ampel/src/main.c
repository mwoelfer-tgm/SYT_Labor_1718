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

//Define variable so all LEDs get toggled
#define PINS GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
GPIO_InitTypeDef GPIO_InitStruct;

int button = 0;

/**
 * Initialize the PushButton
 */
void InitializeButton(void){
	/* GPIO Port A Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO Pin of PushButton */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * Initialize the LEDs
 */
void InitializeLEDs(void) {
	/* GPIO Port E Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure all GPIO LED Pins*/
	GPIO_InitStruct.Pin = PINS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void LEDSOn(void){
	// switch on LEDs
	HAL_GPIO_WritePin(GPIOE, PINS, GPIO_PIN_SET);

}

void LEDSOff(void){
	// switch off LEDs
	HAL_GPIO_WritePin(GPIOE, PINS, GPIO_PIN_RESET);
}

void HAL_SYSTICK_Callback(void){
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	BSP_LED_Toggle(LED_RED);
}

int main(void)
{
	HAL_Init();
	BSP_LED_Init(LED_RED);
	BSP_LED_On(LED_RED);
	HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
	InitializeButton();
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	for(;;);
}
