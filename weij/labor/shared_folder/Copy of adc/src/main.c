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
#include "file.h"

ADC_HandleTypeDef hadc1;
HAL_StatusTypeDef rc,rc1,rc2;

void initAdc(void){
	__ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.DMA_Handle = 0;
	hadc1.ErrorCode = 0;
	hadc1.Lock = HAL_UNLOCKED;
	hadc1.State = HAL_ADC_STATE_RESET;

	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
	hadc1.Init.Resolution = ADC_RESOLUTION12b;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;

	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.EOCSelection = EOC_SINGLE_CONV;
	hadc1.Init.LowPowerAutoWait = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;

	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.NbrOfDiscConversion = 1; //unnötig
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.ExternalTrigConvEdge =
	 ADC_EXTERNALTRIGCONVEDGE_FALLING; // unnötig
	hadc1.Init.DMAContinuousRequests = DISABLE;

	hadc1.Init.Overrun = OVR_DATA_OVERWRITTEN; // Default

	hadc1.Init.NbrOfConversion = 1;

	rc = HAL_ADC_Init(&hadc1);

	ADC_ChannelConfTypeDef sConfig1;
	sConfig1.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
	sConfig1.SingleDiff = ADC_SINGLE_ENDED;
	sConfig1.OffsetNumber = ADC_OFFSET_NONE;
	sConfig1.Offset = 0; // unnötig

	sConfig1.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig1.Rank = ADC_REGULAR_RANK_1;
	rc = HAL_ADC_ConfigChannel(&hadc1, &sConfig1);
}

void adcMeasure(void){
	rc1 = HAL_ADC_Start(&hadc1);
	rc2 = HAL_ADC_PollForConversion(&hadc1, 100);
	int value= HAL_ADC_GetValue(&hadc1);
	printf("Wert1 (rc1): %d \n", rc1);
	printf("Wert2 (rc2): %d \n", rc2);
	printf("Wert3 (value): %d \n", value);
}
int main(void)
{
	HAL_Init();
	initItm();
	initAdc();
	BSP_LED_Init(LED_ORANGE);
	for(;;){
		HAL_Delay(1000);
		adcMeasure();
		BSP_LED_Toggle(LED_ORANGE);
	}
}


