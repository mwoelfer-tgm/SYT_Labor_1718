/**
  ******************************************************************************
  * @file    main.c
  * @author  Filip Scopulovic
  * @version V1.0
  * @date    25-November-2016
  * @brief   printtf output
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
unsigned int faktor;

int main(void) {
faktor = 1;

HAL_Init();
set_conf();
InitButton();
}

void set_conf(void){
// 0xE004 2004, Bit 5
SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN);

TPI->CSPSR = 0x1;
TPI->FFCR = 0x102;

ITM->LAR = 0xC5ACCE55;
ITM->TCR = 0x00010005;
ITM->TER = 0x1;
ITM->TPR = 0x1;
}

int __io_putchar(int ch) {
   return(ITM_SendChar(ch));
}

/* Initialisiert den PushButton */
void InitButton(void){
/* Enable GPIOA clock */
__GPIOA_CLK_ENABLE();

/*Configure GPIO Pin of PushButton */
GPIO_InitStruct.Pin = GPIO_PIN_0;
GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/* Enable and set EXTI0 Interrupt to the lowest priority */
HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}



//Callback Funktion, die angibt was bei dem Interrupt passieren soll
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
for(int i = 1; i < 23; i++) {
unsigned long long f = faktor;
faktor *= i;
printf("%i\n", faktor);
//printf("Nummer %ll mal %i ist gleich unser Faktor %ll\n", f, i, faktor);
}
faktor = 1;
}
