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

GPIO_InitTypeDef GPIO_InitStruct;
int count = 0;
int button = 0;

//Definiere eine Variable welche alle Pins enthält
#define PinsInt GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define PinsExt GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3

void toggleRed(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9 | GPIO_PIN_13);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
}

void toggleBlue(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8 | GPIO_PIN_12);
}

void toggleOrange(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10 | GPIO_PIN_14);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
}

void toggleGreen(void){
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11 | GPIO_PIN_15);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

void turnAllOff(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, PinsInt, GPIO_PIN_RESET);
}

void HAL_SYSTICK_Callback(void){
	count++;
	if(button == 0){
		if(count == 1){
			toggleRed();
		}

		if(count == 3000){
			toggleOrange();
		}

		if(count == 4500){
			toggleOrange();
			toggleRed();
			toggleGreen();
		}

		if(count >= 10000 && count <= 12000){
			if(count%200 == 0){
				toggleGreen();
			}
		}

		if(count == 12000){
			toggleOrange();
		}

		if(count == 14000){
			toggleOrange();
			count = 0;
		}
	}else{
		if(count%1000 == 0){
			toggleOrange();
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
	count = 0;
	turnAllOff();
	if(button == 0){
		button = 1;
	} else{
		button = 0;
	}
}
void LED_Init(void){
	//Auf dem Port E (GPIOE) aktivieren
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Sagen welche Pins angesteurt werden sollen (Alle)
	GPIO_InitStruct.Pin = PinsInt;
	//Modus auf Push Pull setzen
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //Pull Modus setzen auf NoPull
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	//GPIO Initalisieren mit GPIO (Port E) und der "Konfiguration"
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void PIN_Init(void){
	//Auf dem Port A (GPIOA) aktivieren
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Sagen welche Pins angesteurt werden sollen (1,2,3)
	GPIO_InitStruct.Pin = PinsExt;
	//Modus auf Push Pull setzen
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	//Pull Modus setzen auf NoPull
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	//GPIO Initalisieren mit GPIO (Port a) und der "Konfiguration"
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void BUTTON_Init(void){
	//Auf dem Port A (GPIOE) aktivieren
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Sagen welche Pins angesteurt werden sollen (1,2,3)
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	//Modus auf Push Pull setzen
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	//Pull Modus setzen auf NoPull
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

	//GPIO Initalisieren mit GPIO (Port a) und der "Konfiguration"
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

int main(void)
{
	HAL_Init();
	LED_Init();
	BUTTON_Init();
	PIN_Init();
}
