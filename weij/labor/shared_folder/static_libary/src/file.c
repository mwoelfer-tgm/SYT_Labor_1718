/*
 * file.c
 *
 *  Created on: 23. Feb. 2017
 *      Author: Bernd
 */



#include "stm32f3xx.h"
#include "stm32f3_discovery.h"

#include <stdio.h>
#include "file.h"

void initItm(void){
	// 0xE004 2004, Bit 5
	SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN);
	// 0xE004 2004, Bit 6-7
	CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_MODE);
	// 0xE000 EDFC, Bit 24
	SET_BIT(CoreDebug->DEMCR,CoreDebug_DEMCR_TRCENA_Msk);



	TPI->ACPR = 0;
	TPI->CSPSR = 0x1;
	TPI->FFCR = 0x102;
	TPI->SPPR = 0x02;



	ITM->LAR = 0xC5ACCE55;
	ITM->TCR = 0x00010005;
	ITM->TER = 0x1;
	ITM->TPR = 0x1;

	setvbuf(stdout, NULL, _IONBF, 0);
}
int __io_putchar(int ch) {
 return(ITM_SendChar(ch));
}

