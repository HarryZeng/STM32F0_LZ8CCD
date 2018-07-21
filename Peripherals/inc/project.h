/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __project_H
#define __project_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "key.h"
#include "display.h"
#include "SelfStudy.h"
#include "menu.h"
#include "flash.h"
#include "arch.h"
#include "uid.h"
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
int main_start(void);

	#ifdef __cplusplus
	}
	#endif
#endif /*__project_H */


