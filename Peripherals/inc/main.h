/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include "stm32f0xx_adc.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_flash.h"
#include "stm32f0xx_iwdg.h"
#include "stm32f0xx_pwr.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"


/* Private define ------------------------------------------------------------*/

#define Test_IO_Pin 						GPIO_Pin_1
#define Test_IO_GPIO_Port 			GPIOF

#define HAL_ADCIN1_Pin 					GPIO_Pin_2
#define HAL_ADCIN1_GPIO_Port 		GPIOA

#define HAL_OUT_Pin 						GPIO_Pin_3
#define HAL_OUT_GPIO_Port 			GPIOA

#define HAL_DIS_Pin 						GPIO_Pin_4
#define HAL_DIS_GPIO_Port 			GPIOA
#define HAL_PWM_Pin 						GPIO_Pin_5
#define HAL_PWM_GPIO_Port 			GPIOA
#define HAL_SI_Pin 							GPIO_Pin_1
#define HAL_SI_GPIO_Port 				GPIOB
#define HAL_CLK_Pin 						GPIO_Pin_8
#define HAL_CLK_GPIO_Port 			GPIOA

#define SET_Buttom_Pin 					GPIO_Pin_9
#define SET_Buttom_GPIO_Port 		GPIOA
#define UP_Buttom_Pin 					GPIO_Pin_10
#define UP_Buttom_GPIO_Port 		GPIOA
#define DOWN_Buttom_Pin 				GPIO_Pin_12
#define DOWN_Buttom_GPIO_Port 	GPIOA
#define MODE_Buttom_Pin 				GPIO_Pin_11
#define MODE_Buttom_GPIO_Port 	GPIOA
/*SMG*/
#define SMG_D1_Pin 							GPIO_Pin_15
#define SMG_D1_GPIO_Port 				GPIOA
#define SMG_D2_Pin 							GPIO_Pin_8
#define SMG_D2_GPIO_Port 				GPIOB
#define SMG_D3_Pin 							GPIO_Pin_6
#define SMG_D3_GPIO_Port 				GPIOB
#define SMG_D4_Pin 							GPIO_Pin_3
#define SMG_D4_GPIO_Port 				GPIOB
#define SMG_D5_Pin 							GPIO_Pin_2
#define SMG_D5_GPIO_Port 				GPIOB
#define SMG_A_Pin 							GPIO_Pin_5
#define SMG_A_GPIO_Port 				GPIOB
#define SMG_B_Pin 							GPIO_Pin_0
#define SMG_B_GPIO_Port 				GPIOB
#define SMG_C_Pin 							GPIO_Pin_4
#define SMG_C_GPIO_Port	 				GPIOB
#define SMG_D_Pin 							GPIO_Pin_7
#define SMG_D_GPIO_Port 				GPIOA
#define SMG_E_Pin 							GPIO_Pin_7
#define SMG_E_GPIO_Port 				GPIOB
#define SMG_F_Pin 							GPIO_Pin_6
#define SMG_F_GPIO_Port 				GPIOA
#define SMG_G_Pin 							GPIO_Pin_0
#define SMG_G_GPIO_Port 				GPIOA

#define SMG_D6_Pin GPIO_Pin_3
#define SMG_D6_GPIO_Port GPIOF
#define SMG_D7_Pin GPIO_Pin_3
#define SMG_D7_GPIO_Port GPIOF
#define SMG_D8_Pin GPIO_Pin_3
#define SMG_D8_GPIO_Port GPIOF
#define SMG_D9_Pin GPIO_Pin_3
#define SMG_D9_GPIO_Port GPIOF
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
