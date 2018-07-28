


#ifndef __ARCH_H
#define __ARCH_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"	 
#include "stm32f0xx_tim.h"
#include "stm32f0xx_adc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_misc.h"
#include "bsp_init.h"
	 
//#define ADC1_DR_ADDRESS    ((uint32_t)0x4001244C)
#define  ADC1_DR_ADDRESS    (0x40012440)	 
	 
#define IO_Bit_SET	 					Bit_SET
#define IO_Bit_RESET					Bit_RESET
	 
#define ReadGPIO_Pin_State  	GPIO_ReadInputDataBit
#define WriteGPIO_Pin_State	 	GPIO_WriteBit

	 
	 
/* Private define ------------------------------------------------------------*/
/*SMG*/
#define D1_Pin 										SMG_D1_Pin
#define D2_Pin 										SMG_D2_Pin
#define D3_Pin 										SMG_D3_Pin
#define D4_Pin 										SMG_D4_Pin
#define D5_Pin 										SMG_D5_Pin
#define D6_Pin 										SMG_D6_Pin
#define D7_Pin 										SMG_D7_Pin
#define D8_Pin 										SMG_D8_Pin
#define D9_Pin 										SMG_D9_Pin
#define D1_GPIO_Port 							SMG_D1_GPIO_Port
#define D2_GPIO_Port 							SMG_D2_GPIO_Port
#define D3_GPIO_Port 							SMG_D3_GPIO_Port
#define D4_GPIO_Port 							SMG_D4_GPIO_Port
#define D5_GPIO_Port 							SMG_D5_GPIO_Port
#define D6_GPIO_Port 							SMG_D6_GPIO_Port
#define D7_GPIO_Port 							SMG_D7_GPIO_Port
#define D8_GPIO_Port 							SMG_D8_GPIO_Port
#define D9_GPIO_Port 							SMG_D9_GPIO_Port 
/********************************************/
/*SMG*/
#define A_Pin 										SMG_A_Pin
#define B_Pin 										SMG_B_Pin
#define C_Pin 										SMG_C_Pin
#define D_Pin 										SMG_D_Pin
#define E_Pin 										SMG_E_Pin
#define F_Pin 										SMG_F_Pin
#define G_Pin 										SMG_G_Pin
#define A_GPIO_Port 							SMG_A_GPIO_Port
#define B_GPIO_Port 							SMG_B_GPIO_Port
#define C_GPIO_Port 							SMG_C_GPIO_Port
#define D_GPIO_Port 							SMG_D_GPIO_Port
#define E_GPIO_Port 							SMG_E_GPIO_Port
#define F_GPIO_Port 							SMG_F_GPIO_Port
#define G_GPIO_Port 							SMG_G_GPIO_Port
/***************************BUTTON*****************/
//#define BUTTON_SWITCH_Pin 					SWITCH_Buttom_Pin
#define BUTTON_SET_Pin 								SET_Buttom_Pin
#define BUTTON_MODE_Pin 							MODE_Buttom_Pin
#define BUTTON_DOWN_Pin 							DOWN_Buttom_Pin
#define BUTTON_UP_Pin 								UP_Buttom_Pin
//#define BUTTON_SWITCH_GPIO_Port 		SWITCH_Buttom_GPIO_Port
#define BUTTON_SET_GPIO_Port 					SET_Buttom_GPIO_Port
#define BUTTON_MODE_GPIO_Port 				MODE_Buttom_GPIO_Port
#define BUTTON_DOWN_GPIO_Port 				DOWN_Buttom_GPIO_Port
#define BUTTON_UP_GPIO_Port 					UP_Buttom_GPIO_Port
/*OUT*/
#define OUT1_Pin 											HAL_OUT_Pin
#define OUT1_GPIO_Port 								HAL_OUT_GPIO_Port
/*PWM*/
#define DIS_Pin 											HAL_DIS_Pin
#define CLK_Pin 											HAL_CLK_Pin
#define PWM_Pin 											HAL_PWM_Pin
#define SI_Pin 												HAL_SI_Pin

#define DIS_GPIO_Port 								HAL_DIS_GPIO_Port
#define CLK_GPIO_Port 								HAL_CLK_GPIO_Port
#define PWM_GPIO_Port 								HAL_PWM_GPIO_Port
#define SI_GPIO_Port 									HAL_SI_GPIO_Port
/*DAC*/
#ifdef  DAC_OUT_Enable
//	#define DACOUT1_Pin						GPIO_Pin_4  //?????
//	#define DACOUT1_GPIO_Port			GPIOA
	#endif 
#define ADCIN_1_Pin						HAL_ADCIN1_Pin
#define ADCIN_1_GPIO_Port			HAL_ADCIN1_GPIO_Port
//#define ADCIN_2_Pin						GPIO_Pin_2
//#define ADCIN_2_GPIO_Port			GPIOA

#define _Gpio_DIS_TRO  		DIS_GPIO_Port->ODR ^= DIS_Pin
#define _Gpio_PWM_Reset		PWM_GPIO_Port->BRR  = PWM_Pin;  //0
#define _Gpio_PWM_Set			PWM_GPIO_Port->BSRR = PWM_Pin; 	//1
#define _Gpio_DIS_Reset		DIS_GPIO_Port->BRR  = DIS_Pin;  //0
#define _Gpio_DIS_Set			DIS_GPIO_Port->BSRR = DIS_Pin; 	//1

/*************FLASH***************/
#define 	DSY_FLASH_Unlock   	HAL_FLASH_Unlock
#define 	DSY_FLASH_Lock   		HAL_FLASH_Lock
#define   DSY_FLASH_Erase			HAL_FLASHEx_Erase
#define 	DSY_FLASH_Program		HAL_FLASH_Program

#ifdef __cplusplus
}
#endif
#endif /*__ARCH_H */

