
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
void SelfStudy_SET1(void);;

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

void SelfStudy_End(void);

void selfstudy(void)
{
	uint8_t OUT1_STATUS,OUT2_STATUS;
	
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
				//OUT2_STATUS = GPIO_ReadInputDataBit(OUT2_GPIO_Port,OUT2_Pin);/*获取当前的OUT2状态*/
				//GPIO_WriteBit(OUT2_GPIO_Port,OUT2_Pin,(BitAction)OUT2_STATUS);/*保持着OUT1状态*/

				SelfStudy_SET1();
				SMG_DisplaySET_Step_1_Mode(2,Final_1);  //显示SET1和信号值  //2018-7-11->Final_1显示信号值
				
				while(SetButton.PressCounter==1)
				{
					SMG_DisplaySET_Step_1_Mode(2,Final_1);  //显示SET1和信号值  //2018-7-11->Final_1显示信号值
				} //等待Set按键释放
				
//				while(SetButton.PressCounter==2)	
//				{
//				}

					if(SetButton.PressCounter>=2) /*按键达到3秒后，第一次进入自学习，等待第二次按下SET 3秒*/
					{
						SelfStudy_SET2();
						SelfStudy_End();
						SMG_DisplaySET_Step_2_Mode(2,0,Threshold);  //显示SET2和阈值
						
						FX_Flag = 1;  //结束自学习，重启FX
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





void SelfStudy_End(void)
{					
	int32_t S_SET = 0;

			S_SET = Final_1;

			if(displayModeONE_FLAG)//区域模式
			{
				if(DisplayModeNo==0)
				{
					HI = S_SET; 
					ModeButton.PressCounter	= 0;				
					WriteFlash(HI_FLASH_DATA_ADDRESS,HI);
				}
				else if(DisplayModeNo==1)
				{
					LO = S_SET; 
					ModeButton.PressCounter	= 1;	
					WriteFlash(LO_FLASH_DATA_ADDRESS,LO);
				}
			}
			else    //标准模式
			{
				NewThreshold = (S1_MaxValue + S2_MaxValue)/2; 

				if(NewThreshold<=20) NewThreshold=20;
				if(NewThreshold>=4095) NewThreshold=4095;	

				Threshold = NewThreshold;
				WriteFlash(Threshold_FLASH_DATA_ADDRESS,Threshold);
			}
		
		WriteGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin,(uint8_t)ReadGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin));
		//GPIO_WriteBit(OUT2_GPIO_Port,OUT2_Pin,(BitAction)GPIO_ReadInputDataBit(OUT2_GPIO_Port,OUT2_Pin));
		
		
		if(S1_MaxValue <= S2_MaxValue)  /*SET_VREF为SET1和SET2中较小的值*/
			SET_VREF = S1_MaxValue;
		else 
			SET_VREF = S2_MaxValue;
		
		//TX = SET_VREF;
		//TX_Sum=0;
		//TX_Index = 0;
//		TX_Temp[0] = 0;
//		TX_Temp[1] = 0;
//		TX_Temp[2] = 0;
//		TX_Temp[3] = 0;
		Threshold = NewThreshold;
		
		selfDisplayEndFlay = 1;
		SetButton.PressCounter = 0;					/*清楚按键次数*/
		SetButton.Status = Release;					/*释放按键*/
		SetButton.Effect = PressNOEffect;
		
		WriteFlash(SET_VREF_FLASH_DATA_ADDRESS,SET_VREF);
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

void SelfStudy_SET1(void) 
{
		if(sample_finish)
		{
			sample_finish = 0;
			S1_MaxValue = 	Final_1 ;     //2018-7-12  直接取Final_1
		}
				
//				if(SET1_ADCValue>=S1_MaxValue)   //不断寻找最大值
//				{
//					S1_MaxValue = SET1_ADCValue;
//				}
}

