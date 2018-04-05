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
DMA_HandleTypeDef hdma;
HAL_StatusTypeDef rc,rc1,rc2;


int VDDA;
int currMessung = 0;
int channel1;
int channel2;
int channel3;
uint32_t results[4] = {0};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc){

}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){

}
static void initDma(void){
	HAL_StatusTypeDef rcDmaInit, rcDmaStart;
	__DMA1_CLK_ENABLE();
	hdma.Instance = DMA1_Channel1;
	hdma.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma.Init.MemInc = DMA_MINC_ENABLE;
	// DMA_CIRCULAR or DMA_NORMAL???
	hdma.Init.Mode = DMA_NORMAL;
	hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma.Init.Priority = DMA_PRIORITY_LOW;
	hdma.ErrorCode = HAL_DMA_ERROR_NONE;
	hdma.Lock = HAL_UNLOCKED;
	hdma.State = HAL_DMA_STATE_RESET;
	hdma.Parent = &hadc; //?????
	hdma.XferCpltCallback = NULL;
	hdma.XferErrorCallback = NULL;
	hdma.XferHalfCpltCallback = NULL;
	rcDmaInit = HAL_DMA_Init(&hdma);
}
void initAdc(void){
	__ADC1_CLK_ENABLE();



	hadc.Instance = ADC1;
	hadc.Instance->IER |= ADC_ISR_EOC;
	hadc.Instance->IER |= ADC_ISR_EOS;
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
	hadc.DMA_Handle = &hdma;

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

void setVDDA(int m_refint){
	uint16_t m_refint_cal= *((uint16_t*)0x1FFFF7BA);
	VDDA = (3300*m_refint_cal)/m_refint;
}


uint32_t calculateVTest(uint32_t m_test){
	return (VDDA * m_test) / 0xFFF;
}

void DMA1_Channel1_IRQHandler(void) {
 HAL_DMA_IRQHandler(&hdma);
}

int main(void)
{
	HAL_Init();
	initItm();

	initPins();
	printVrefInt();

	initAdc();
	initDma();
	BSP_LED_Init(LED_ORANGE);

	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	for(;;){
		__GPIOC_CLK_ENABLE();
		HAL_Delay(1000);

		HAL_ADC_Start_DMA(&hadc,results, 4);
		HAL_Delay(1000);
		setVDDA(results[0]);

		results[1] = calculateVTest(results[1]);
		results[2] = calculateVTest(results[2]);
		results[3] = calculateVTest(results[3]);
		int delta_u1 = results[2] - results[1];
		int delta_u2 = results[3] - results[2];

		int R2 = (3300 * delta_u1) / delta_u2;

		printf("VDDA: %d\nChannel1: %d mv \nChannel2: %d mv \nChannel3: %d mv \nR2 entspricht %d\n", VDDA, results[1], results[2],results[3] , R2);

		BSP_LED_Toggle(LED_ORANGE);
	}
}


