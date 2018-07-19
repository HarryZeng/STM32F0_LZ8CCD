/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __differentialDC_H
#define __differentialDC_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f0xx.h"

#define _Gpio_12_set  GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12))
#define _Gpio_7_set  GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7))

	 
	 
#define DAC_OUT_Enable	 	 
	 
/* Private define ------------------------------------------------------------*/
/*SMG*/
#define D1_Pin 										GPIO_Pin_2
#define D1_GPIO_Port 							GPIOB
#define D2_Pin 										GPIO_Pin_0
#define D2_GPIO_Port 							GPIOB
#define D3_Pin 										GPIO_Pin_7
#define D3_GPIO_Port 							GPIOA
#define D4_Pin 										GPIO_Pin_6
#define D4_GPIO_Port 							GPIOA
#define D5_Pin 										GPIO_Pin_15
#define D5_GPIO_Port 							GPIOA
#define D6_Pin 										GPIO_Pin_14
#define D6_GPIO_Port 							GPIOC
#define D7_Pin 										GPIO_Pin_15
#define D7_GPIO_Port 							GPIOC
#define D9_Pin 										GPIO_Pin_0
#define D9_GPIO_Port 							GPIOC
#define D8_Pin 										GPIO_Pin_1
#define D8_GPIO_Port 							GPIOC
/*SMG*/
#define A_Pin 										GPIO_Pin_0
#define A_GPIO_Port 							GPIOA
#define B_Pin 										GPIO_Pin_8
#define B_GPIO_Port 							GPIOB
#define C_Pin 										GPIO_Pin_7
#define C_GPIO_Port 							GPIOB
#define D_Pin 										GPIO_Pin_6
#define D_GPIO_Port 							GPIOB
#define E_Pin 										GPIO_Pin_4
#define E_GPIO_Port 							GPIOB
#define F_Pin 										GPIO_Pin_3
#define F_GPIO_Port 							GPIOB
#define G_Pin 										GPIO_Pin_5
#define G_GPIO_Port 							GPIOB
/*BUTTON*/
//#define BUTTON_SWITCH_Pin 						GPIO_Pin_10
//#define BUTTON_SWITCH_GPIO_Port 			GPIOB
#define BUTTON_SET_Pin 								GPIO_Pin_9
#define BUTTON_SET_GPIO_Port 					GPIOA
#define BUTTON_MODE_Pin 							GPIO_Pin_11
#define BUTTON_MODE_GPIO_Port 				GPIOA
#define BUTTON_DOWN_Pin 							GPIO_Pin_12
#define BUTTON_DOWN_GPIO_Port 				GPIOA
#define BUTTON_UP_Pin 								GPIO_Pin_10
#define BUTTON_UP_GPIO_Port 					GPIOA
/*OUT*/
#define OUT1_Pin 											GPIO_Pin_3
#define OUT1_GPIO_Port 								GPIOA
/*PWM*/
#define DIS_Pin 											GPIO_Pin_4
#define DIS_GPIO_Port 								GPIOA
#define CLK_Pin 											GPIO_Pin_8
#define CLK_GPIO_Port 								GPIOA
#define PWM_Pin 											GPIO_Pin_5
#define PWM_GPIO_Port 								GPIOA
#define SI_Pin 												GPIO_Pin_1
#define SI_GPIO_Port 									GPIOB
/*DAC*/
#ifdef  DAC_OUT_Enable
//	#define DACOUT1_Pin						GPIO_Pin_4  //?????
//	#define DACOUT1_GPIO_Port			GPIOA
	#endif 
#define ADCIN_1_Pin						GPIO_Pin_2
#define ADCIN_1_GPIO_Port			GPIOA
//#define ADCIN_2_Pin						GPIO_Pin_2
//#define ADCIN_2_GPIO_Port			GPIOA


	 
#define ADVtimeFlag   		0x01
#define ButtontimeFlag   	0x02 
#define D4toD1timeFlag   	0x04
#define D9toD5timeFlag   	0x08
#define Blink500msFlag   	0x10
#define Blink100msFlag   	0x20
#define EndDispalyFlag   	0x40
	 
typedef enum
{
		ULOC = 51U,
		LOC
}Button_STATUS;	 


//#include "bsp_init.h"

extern float 	Final;

extern int16_t adc_dma_tab[1]; 
extern int16_t Threshold;
extern uint8_t 	RegisterA;
extern uint32_t ADCValue;
extern uint8_t  EventFlag; 
extern int32_t 	DACOUT1;
extern int32_t 	DACOUT2;
extern uint32_t 	ShortCircuitCounter;

void Get_SA_Value(uint32_t *SAvalue);
void Get_SB_Value(uint32_t *SBvalue);
void Get_S1_Value(uint32_t *S1value);
void Get_S2_Value(uint32_t *S2value);
void Main_Function(void);	 
void GetADCAverageValue(uint32_t *AverageValue);
void GetEEPROM(void);
void ResetParameter(void);
void SetOUT1Status(void);
void GetTotalADCValue(void);
	#ifdef __cplusplus
	}
	#endif
#endif /*__ differentialDC_H */


