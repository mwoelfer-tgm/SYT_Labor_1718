/**
  ******************************************************************************
  * @file    main.c
  * @author  Woelfer martin
  * @version V1.4
  * @date    15-October-2016
  * @brief   Toggles the LEDs by pressing button.
  ******************************************************************************
*/

#include "stm32f3xx.h"
#include "stm32f3_discovery.h"

//Define variable so all LEDs get toggled
#define PINS GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
GPIO_InitTypeDef GPIO_InitStruct;


/**
 * Initializes oscillators and clocks
 */
void InitializeSystemClock(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, PINS, GPIO_PIN_RESET);
}

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

int main(void) {
	// resets periph. and inits the FLash and Systick
	HAL_Init();

	InitializeSystemClock();
	InitializeLEDs();
	InitializeButton();//

	for(;;){
		// checks if PushButon Pin is set
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {
			// switch on LEDs
			HAL_GPIO_WritePin(GPIOE, PINS, GPIO_PIN_SET);
		} else {
			// switch off LEDs
			HAL_GPIO_WritePin(GPIOE, PINS, GPIO_PIN_RESET);
		}
	}
}
