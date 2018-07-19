
///**
//  ********************************  STM32F0x1  *********************************
//  * @�ļ���     �� menu.h
//  * @����       �� HarryZeng
//  * @��汾     �� V1.5.0
//  * @�ļ��汾   �� V1.0.0
//  * @����       �� 2017��05��15��
//  * @ժҪ       �� ���ݴ���
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  ������־:
//  2017-05-15 V1.0.0:��ʼ�汾
//  ----------------------------------------------------------------------------*/
///* ������ͷ�ļ� --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __menu_H
#define __menu_H
#ifdef __cplusplus
 extern "C" {
#endif
#include  "main.h"
#include 	"stdbool.h"
#include 	"stdint.h"
	 

typedef enum
{
		TOFF = 31U,
		OFFD,
		ON_D,
		SHOT
}DELAY_MODE;	 
	 
	 
typedef struct 
{
	DELAY_MODE 	DelayMode;		
	int16_t 		DelayValue;	
	uint32_t    DelayCounter;
}OUT1_DELAY_MODE_STRUCT;
	 

extern int32_t SV;	 
extern OUT1_DELAY_MODE_STRUCT OUT1_Mode;

void menu(void);

#ifdef __cplusplus
}
#endif
#endif /*__menu_H */
