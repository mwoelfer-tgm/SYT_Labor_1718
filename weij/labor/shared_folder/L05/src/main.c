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

ADC_HandleTypeDef hadc;
HAL_StatusTypeDef rc,rc1,rc2;


int VDDA;

void initAdc(void){
	__ADC1_CLK_ENABLE();



	hadc.Instance = ADC1;
	hadc.DMA_Handle = 0;
	hadc.ErrorCode = 0;
	hadc.Lock = HAL_UNLOCKED;
	hadc.State = HAL_ADC_STATE_RESET;

	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION12b;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc.Init.EOCSelection = EOC_SINGLE_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.Overrun = OVR_DATA_OVERWRITTEN;
	hadc.Init.NbrOfConversion = 4;

	rc = HAL_ADC_Init(&hadc);

	ADC_ChannelConfTypeDef sConfig1;
	sConfig1.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
	sConfig1.SingleDiff = ADC_SINGLE_ENDED;  			// Ich messe nur ein PIN
	sConfig1.OffsetNumber = ADC_OFFSET_NONE; 			// Kein Offset
	// sConfig1.Offset = 0; // unnötig

	// Config VrefInt
	sConfig1.Channel = ADC_CHANNEL_VREFINT;
	sConfig1.Rank = ADC_REGULAR_RANK_1;
	HAL_ADC_ConfigChannel(&hadc, &sConfig1);

	// Config U1 (PA0)
	sConfig1.Channel = ADC_CHANNEL_1;
	sConfig1.Rank = ADC_REGULAR_RANK_2;
	HAL_ADC_ConfigChannel(&hadc, &sConfig1);

	// Config U2 (PA1)
	sConfig1.Channel = ADC_CHANNEL_2;
	sConfig1.Rank = ADC_REGULAR_RANK_3;
	HAL_ADC_ConfigChannel(&hadc, &sConfig1);

	// Config U3 (PA2)
	sConfig1.Channel = ADC_CHANNEL_3;
	sConfig1.Rank = ADC_REGULAR_RANK_4;
	HAL_ADC_ConfigChannel(&hadc, &sConfig1);
}

void initPins(void){
	// Init analog pins
	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Alternate = 0;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}



void printVrefInt(void){
	uint16_t m_refint_cal= *((uint16_t*)0x1FFFF7BA);
	int v_ref_int = 3300* m_refint_cal/0xFFF;
	printf("Die interne Referenzspannung beträgt %d \n", v_ref_int);
}

void setVDDA(void){
	uint16_t m_refint_cal= *((uint16_t*)0x1FFFF7BA);
	HAL_ADC_PollForConversion(&hadc, 100);
	uint32_t m_refint= HAL_ADC_GetValue(&hadc);
	VDDA = (3300*m_refint_cal)/m_refint;
}


uint32_t calculateVTest(uint32_t m_test){
	return (VDDA * m_test) / 0xFFF;
}

int main(void)
{
	HAL_Init();
	initItm();

	initPins();
	printVrefInt();

	initAdc();
	BSP_LED_Init(LED_ORANGE);

	for(;;){
		__GPIOC_CLK_ENABLE();
		HAL_Delay(1000);

		HAL_ADC_Start(&hadc);
		setVDDA();

		HAL_ADC_PollForConversion(&hadc, 100);
		uint32_t channel1 = calculateVTest(HAL_ADC_GetValue(&hadc));

		HAL_ADC_PollForConversion(&hadc, 100);
		uint32_t channel2 = calculateVTest(HAL_ADC_GetValue(&hadc));

		HAL_ADC_PollForConversion(&hadc, 100);
		uint32_t channel3 = calculateVTest(HAL_ADC_GetValue(&hadc));


		int delta_u1 = channel2 - channel1;
		int delta_u2 = channel3 - channel2;

		int R2 = (3300 * delta_u1) / delta_u2;

		printf("Channel1: %d mv \nChannel2: %d mv \nChannel3: %d mv \nR2 entspricht %d\n", channel1, channel2,channel3, R2);
		BSP_LED_Toggle(LED_ORANGE);
	}
}


