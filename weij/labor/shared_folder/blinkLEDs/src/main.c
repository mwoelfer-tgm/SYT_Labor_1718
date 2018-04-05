/**
  ******************************************************************************
  * @file    main.c
  * @author  Wölfer Martin
  * @version V1.0
  * @date    08-Oktober-2016
  * @brief   Default main function.
  ******************************************************************************
*/

//Importiere GrundLibrary für das Board
#include "stm32f3xx.h"

//Definiere eine Variable welche alle Pins enthält
#define PINS GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15


//Main Funktion
int main(void) {
	//Initalisiere die HAL Library
	HAL_Init();
	//initialise die LEDs
	LED_Init();
	//Endlosschleife
	while(1){
		//Die Pins "aufdrehen", der erste Parameter GPIOE gibt an bei welchem Port die Pins
		//Der zweite Parameter PINS gibt an welche Pins genau angesteuert werden sollen
		HAL_GPIO_TogglePin(GPIOE, PINS);

		//Einen Delay Einbauen damit es blinkt => Statt Interrupt
		HAL_Delay(500);
	}
}


void LED_Init(void){
	//Eine Variable initalisieren welche man dann konfiguriern
	GPIO_InitTypeDef LED_Init;

	//Auf dem Port E (GPIOE) aktivieren
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Sagen welche Pins angesteurt werden sollen (Alle)
	LED_Init.Pin = PINS;
	//Modus auf Push Pull setzen
    LED_Init.Mode = GPIO_MODE_OUTPUT_PP;
    //Pull Modus setzen auf NoPull
	LED_Init.Pull = GPIO_NOPULL;
	LED_Init.Speed = GPIO_SPEED_FREQ_LOW;

	//GPIO Initalisieren mit GPIO (Port E) und der "Konfiguration"
	HAL_GPIO_Init(GPIOE, &LED_Init);
}

void BUTTON_Init(void){
	//Eine Variable initalisieren welche man dann konfiguriern
	GPIO_InitTypeDef LED_Init;

	//Auf dem Port E (GPIOE) aktivieren
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Sagen welche Pins angesteurt werden sollen (Alle)
	LED_Init.Pin = PINS;
	//Modus auf Push Pull setzen
	LED_Init.Mode = GPIO_MODE_OUTPUT_PP;
	//Pull Modus setzen auf NoPull
	LED_Init.Pull = GPIO_NOPULL;
	LED_Init.Speed = GPIO_SPEED_FREQ_LOW;
}
