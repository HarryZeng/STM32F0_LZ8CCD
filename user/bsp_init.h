///**
//  ********************************  STM32F10x  *********************************
//  * @�ļ���     �� bsp_init.h
//  * @����       �� HarryZeng
//  * @��汾     �� V1.0.0
//  * @�ļ��汾   �� V1.0.0
//  * @����       �� 2017��10�31��
//  * @ժҪ       �� ���ݴ���
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  ������־:
//  2017-10-31 V1.0.0:��ʼ�汾
//  ----------------------------------------------------------------------------*/
///* ������ͷ�ļ� --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/


#ifndef __BSP_INIT_H
#define __BSP_INIT_H
#ifdef __cplusplus
 extern "C" {
#endif
#include  "stm32f0xx.h"
#include "project.h"
#include 	"stdbool.h"
#include 	"stdint.h"

	 
#define DMA_Value_NO   			1	 
#define DMA_BUFFER_SIZE     1*DMA_Value_NO 
	 
void RCC_Configuration(void);
void SMG_GPIO_INIT(void);
void IO_GPIO_INIT(void);
void TIM3_init(void);
void TIM14_init(void);
void TIM2_init(void);
void TIM1_Init(void);
void ADC1_Configuration(void);	 
void ADC1_Init(void);
void ADC2_Init(void);
void bsp_init(void);
	
#ifdef  DAC_OUT_Enable
void DAC_Configuration(void);	
#endif

extern int16_t adc_dma_tab[DMA_BUFFER_SIZE]; 
extern int32_t SA_MaxValue;
extern int32_t SB_MaxValue;
	 
#define _Gpio_Test_TRO  GPIO_WriteBit(Test_IO_GPIO_Port, Test_IO_Pin, (uint8_t)!GPIO_ReadOutputDataBit(Test_IO_GPIO_Port, Test_IO_Pin))


#ifdef __cplusplus
}
#endif
#endif /*__BSP_INIT_H */

