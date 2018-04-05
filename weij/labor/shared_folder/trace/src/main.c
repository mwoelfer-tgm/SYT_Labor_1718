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

int main(void){

	HAL_Init();

	// 0xE004 2004, Bit 5
	SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN);

	TPI->CSPSR = 0x1;
	TPI->FFCR = 0x102;

	ITM->LAR = 0xC5ACCE55;
	ITM->TCR = 0x00010005;
	ITM->TER = 0x1;
	ITM->TPR = 0x1;
	int i;
	for(i=0;;i++){
		HAL_Delay(1000);
		printf("Wird zum %d. mal aufgerufen\n",i);
		}
	}
	int write(int file, char *ptr, int len);
	int __io_putchar(int ch) {
	 return(ITM_SendChar(ch));
}
