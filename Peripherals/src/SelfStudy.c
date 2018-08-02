
///**
//  ********************************  STM32F0x1  *********************************
//  * @文件名     ： SelftStudy.c
//  * @作者       ： HarryZeng
//  * @库版本     ： V1.5.0
//  * @文件版本   ： V1.0.0
//  * @日期       ： 2017年11月24日
//  * @摘要       ： 数据处理
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  更新日志:
//  2017-11-24 V1.0.0:初始版本
//  ----------------------------------------------------------------------------*/
///* 包含的头文件 --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/

#include "SelfStudy.h"



/*第一次SET按键按下处理函数*/
uint32_t SelfStudy_SET1(void);

/*第二次SET按键按下处理函数*/
void SelfStudy_SET2(void);;

uint8_t SelftStudyflag=0;
uint8_t ATTcalibrationFlag=0;
uint8_t 	selfDisplayEndFlay=0;
uint32_t  SET1ADC_Value=0;
uint32_t CalibrateADCValue=0;
uint32_t CalibrateSAValue=0;
uint32_t CalibrateSBValue=0;

uint32_t CalibrateS1Value=0;
uint32_t CalibrateS2Value=0;


//extern  uint8_t DX_Flag;
extern uint8_t sample_finish;
extern int32_t 	SET_VREF;
extern uint32_t ADC_Display;//ADC显示
extern uint8_t 	FX_Flag;




/*在一系列的ADCvalue中寻找最大的ADV MAX*/
int32_t 			ADCMAX=0;
int32_t 		NewThreshold=0;
//int32_t 		S_MaxValue=0;
int32_t    	S1_MaxValue=0;
int32_t    	S2_MaxValue=0;
int32_t    	S1_SumValue=0;
int32_t    	S2_SumValue=0;
extern uint8_t displayModeONE_FLAG ;
extern uint8_t DisplayModeNo;
extern int16_t HI ;
extern int16_t LO ;
extern int32_t TX;
/*ADCIN的数据调零*/

extern uint8_t S_Final_FinishFlag;
extern uint32_t 	S[4];
extern uint32_t 	S_Final;
extern int32_t TX_Sum;
extern int32_t TX_Index;
extern float Final_1;
extern int32_t TX_Temp[4];

uint32_t  SelfStudy_GetThreshold(void);
uint32_t Self_S_Buffer_Data[4][32];
void selfstudy(void)
{
	uint8_t OUT1_STATUS,OUT2_STATUS;
	uint32_t SelfADCValue=0;
	if(SetButton.Status == Press && ModeButton.Status==Press)
	{
			
	}
	else
	{
			/*第一次进入SET模式*/
			while(SetButton.Status == Press && SetButton.PressTimer >= SetButton.LongTime)     //只要在显示模式下第一次按下SET按键
			{	
				SelftStudyflag = 1; //标记进入自学习状态
				sample_finish = 0;  //清除采样结束标记
					/*保持OUT1的状态*/
				OUT1_STATUS = ReadGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin);/*获取当前的OUT1状态*/
				WriteGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin,(uint8_t)OUT1_STATUS);/*保持着OUT1状态*/

				SMG_DisplaySET_Step_1_Mode(23,SelfADCValue);  //显示SET1和信号值  //2018-7-11->Final_1显示信号值

				//SelfStudy_SET1();
				SelfADCValue = SelfStudy_GetThreshold();
				
				while(SetButton.PressCounter==1)
				{
					SMG_DisplaySET_Step_1_Mode(2,SelfADCValue);  //显示SET1和信号值  //2018-7-11->Final_1显示信号值
				} //等待Set按键释放
				
					if(SetButton.PressCounter>=2) /*按键达到3秒后，第一次进入自学习，等待第二次按下SET 3秒*/
					{
						//SelfStudy_SET2();
						//SelfStudy_End();
						//SMG_DisplaySET_Step_2_Mode(2,0,Threshold);  //显示SET2和阈值
						
						//FX_Flag = 1;  //结束自学习，重启FX
						/*一直等待第二次SET的按下*
						**************************/
						SetButton.LastCounter = SetButton.PressCounter;
						SetButton.PressCounter = 0;
						SetButton.Effect = PressNOEffect;
						UpButton.PressCounter=0;
						UpButton.Effect=PressNOEffect;
						DownButton.PressCounter=0;
						DownButton.Effect=PressNOEffect;
						ModeButton.Effect=PressNOEffect;
						selfDisplayEndFlay =0;
						SelftStudyflag = 0;//清除自学习标记-- 结束了自学习
					}
			}
			SetButton.PressCounter = 0;
	}
}





uint32_t  SelfStudy_GetThreshold(void)
{					
	int32_t S_SET = 0;

			NewThreshold = SelfStudy_SET1();
			//S_SET = Final_1;

			if(displayModeONE_FLAG)//区域模式
			{
				if(DisplayModeNo==0)
				{
					HI = NewThreshold; 
					ModeButton.PressCounter	= 0;				
					//WriteFlash(HI_FLASH_DATA_ADDRESS,HI);
				}
				else if(DisplayModeNo==1)
				{
					LO = NewThreshold; 
					ModeButton.PressCounter	= 1;	
					//WriteFlash(LO_FLASH_DATA_ADDRESS,LO);
				}
			}
			else    //标准模式
			{

				if(NewThreshold<=20) NewThreshold=20;
				if(NewThreshold>=4095) NewThreshold=4095;	

				Threshold = NewThreshold;
				//WriteFlash(Threshold_FLASH_DATA_ADDRESS,Threshold);
			}
		
		WriteGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin,(uint8_t)ReadGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin));

		Threshold = NewThreshold;

		return Threshold;
}

void SelfStudy_SET2(void) 
{
		if(sample_finish)
		{
			sample_finish = 0;
			S2_MaxValue = 	Final_1 ;     //2018-7-12  直接取Final_1
		}
		
//		if(SET2_ADCValue>=S2_MaxValue)   //不断寻找最大值
//		{
//			S2_MaxValue = SET2_ADCValue;
//		}
}

///*获取四个ADC通道采样后，求平均的值*/
//uint8_t  JudgeSvalue(uint32_t *S_Value)
//{
//	uint8_t flag=0x00;
//		if(S_Value[0]>4000) flag |= 0x01;/*0000 0001*/
//	else flag &= 0xFE;/*1111 1110*/
//	
//		if(S_Value[1]>4000) flag |= 0x02;/*0000 0010*/
//	else flag &= 0xFD;/*1111 1101*/
//	
//		if(S_Value[2]>4000) flag |= 0x04;/*0000 0100*/
//	else flag &= 0xFB;/*1111 1011*/
//	
//		if(S_Value[3]>4000) flag |= 0x08;/*0000 1000*/
//	else flag &= 0xF7;/*1111 0111*/
//	
//	if(flag==0x0f)
//		return 1;
//	else 
//		return 0;
//}

/*ADCIN的数据调零*/

uint32_t SelfStudy_SET1(void) 
{
	uint8_t i,j;
	uint32_t SelfDTHValue=0;
	
	while(Final_1>2300 || Final_1<1600)
	{
		if(sample_finish)
		{
			sample_finish = 0;
			if(Final_1<1600)
				TDIS = TDIS+1;
			else if(Final_1>2300)
				TDIS = TDIS-1;
		}
	}
	
	if(F1_F2_Mode==0)
	{
		SelfDTHValue = Final_1;
	}
	else 
	{
		for(j=0;j<4;j++)
			for(i=0;i<32;i++)
			Self_S_Buffer_Data[j][i] = S_Buffer[j][i];
		SelfDTHValue = 8000;
	}
		return SelfDTHValue;
}

