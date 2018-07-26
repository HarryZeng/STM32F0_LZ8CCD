#include "stm32f0xx.h"
#include "project.h"
#include "key.h"
#include "stdio.h"
#include "display.h"
#include "menu.h"

#include "bsp_init.h"
#include "flash.h"

uint8_t CheckFLag = 0;

/****************************??????****************************/

volatile uint32_t timenum;
extern uint8_t EventFlag;
extern uint8_t ShortCircuit;

extern int16_t OUT2_TimerCounter;
extern int16_t OUT3_TimerCounter;
extern uint8_t OUT3;
extern uint8_t OUT2;
extern uint8_t OUT1;
extern uint32_t CPV;

void timer_init(void);
void GPIO_Config(void);
uint8_t FlashCheck(void);
void GPIO_DEINIT_ALL(void);
void WriteFlash(uint32_t addr, uint32_t data);
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  //�������´���,֧��printf����,������Ҫѡ��use MicroLIB
  */

extern bool timeflag;
extern uint32_t tempPress;

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)) //�жϷ���update�¼��ж�
	{
		timenum++;
		//_Gpio_Test_TRO;
		OUT1_Mode.DelayCounter++;

		//GPIOB->ODR ^= GPIO_Pin_8;
		if (timenum % 2 == 0) /*8us*1000us=8000us*/
		{
			//_Gpio_Test_TRO;
			if (OUT2)
				OUT2_TimerCounter++;
			if (OUT3)
				OUT3_TimerCounter++;

			SMG_Diplay();
		}
		if (timenum % 6 == 0) /*20us*1000us=20000us*/
		{
			Key_Scan(); //��ʱɨ�谴��
			tempPress = 1;
		}
		if (timenum >= 500) /*500*1000us = 500,000us = 500ms*/
		{
			GetTotalADCValue();
			timeflag = !timeflag;
			EventFlag = EventFlag | Blink500msFlag;
			timenum = 0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���update�¼��жϱ�־
	}
}

void TIM1_BRK_UP_TRG_COM_IRQHandler()
{
	if (TIM_GetITStatus(TIM1, TIM_FLAG_Update)) //�жϷ���update�¼��ж�
	{

		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //���update�¼��жϱ�־
	}
}

/*TIM3 IRQ*/

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update)) //�жϷ���update�¼��ж�
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���update�¼��жϱ�־
	}
}

/******************************************
Main������
******************************************/
int main(void)
{
		while(1)
		{
			main_start();
		}
}

