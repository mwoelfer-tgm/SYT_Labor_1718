/**
  ******************************************************************************
  * @file    main.c
  * @author  Pierre Rieger
  * @version V1.0
  * @date    25-January-2017
  * @brief   prints to external programm
  ******************************************************************************
*/


#include "stm32f3xx.h"
#include "stm32f3_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
int n = 0;

unsigned long long factorial(unsigned long long f)
{
    if ( f == 0 )
        return 1;
    return(f * factorial(f - 1));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
	printf("%d! : %llu \n",n,factorial(n));
}


void BUTTON_Init(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

int main(void)
{
	BUTTON_Init();
	HAL_Init();

	// 0xE004 2004, Bit 5
	SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN);


	TPI->CSPSR = 0x1;
	TPI->FFCR = 0x102;

	ITM->LAR = 0xC5ACCE55;
	ITM->TCR = 0x00010005;
	ITM->TER = 0x1;
	ITM->TPR = 0x1;

	for(;;){
		n++;
		HAL_Delay(1000);
		printf("Variable = %d \n",n);
	}
}
int write(int file, char *ptr, int len);
int __io_putchar(int ch) {
	return(ITM_SendChar(ch));
}


