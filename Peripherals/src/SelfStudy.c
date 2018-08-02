
///**
//  ********************************  STM32F0x1  *********************************
//  * @�ļ���     �� SelftStudy.c
//  * @����       �� HarryZeng
//  * @��汾     �� V1.5.0
//  * @�ļ��汾   �� V1.0.0
//  * @����       �� 2017��11��24��
//  * @ժҪ       �� ���ݴ���
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  ������־:
//  2017-11-24 V1.0.0:��ʼ�汾
//  ----------------------------------------------------------------------------*/
///* ������ͷ�ļ� --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/

#include "SelfStudy.h"



/*��һ��SET�������´�����*/
uint32_t SelfStudy_SET1(void);

/*�ڶ���SET�������´�����*/
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
extern uint32_t ADC_Display;//ADC��ʾ
extern uint8_t 	FX_Flag;




/*��һϵ�е�ADCvalue��Ѱ������ADV MAX*/
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
/*ADCIN�����ݵ���*/

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
			/*��һ�ν���SETģʽ*/
			while(SetButton.Status == Press && SetButton.PressTimer >= SetButton.LongTime)     //ֻҪ����ʾģʽ�µ�һ�ΰ���SET����
			{	
				SelftStudyflag = 1; //��ǽ�����ѧϰ״̬
				sample_finish = 0;  //��������������
					/*����OUT1��״̬*/
				OUT1_STATUS = ReadGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin);/*��ȡ��ǰ��OUT1״̬*/
				WriteGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin,(uint8_t)OUT1_STATUS);/*������OUT1״̬*/

				SMG_DisplaySET_Step_1_Mode(23,SelfADCValue);  //��ʾSET1���ź�ֵ  //2018-7-11->Final_1��ʾ�ź�ֵ

				//SelfStudy_SET1();
				SelfADCValue = SelfStudy_GetThreshold();
				
				while(SetButton.PressCounter==1)
				{
					SMG_DisplaySET_Step_1_Mode(2,SelfADCValue);  //��ʾSET1���ź�ֵ  //2018-7-11->Final_1��ʾ�ź�ֵ
				} //�ȴ�Set�����ͷ�
				
					if(SetButton.PressCounter>=2) /*�����ﵽ3��󣬵�һ�ν�����ѧϰ���ȴ��ڶ��ΰ���SET 3��*/
					{
						//SelfStudy_SET2();
						//SelfStudy_End();
						//SMG_DisplaySET_Step_2_Mode(2,0,Threshold);  //��ʾSET2����ֵ
						
						//FX_Flag = 1;  //������ѧϰ������FX
						/*һֱ�ȴ��ڶ���SET�İ���*
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
						SelftStudyflag = 0;//�����ѧϰ���-- ��������ѧϰ
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

			if(displayModeONE_FLAG)//����ģʽ
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
			else    //��׼ģʽ
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
			S2_MaxValue = 	Final_1 ;     //2018-7-12  ֱ��ȡFinal_1
		}
		
//		if(SET2_ADCValue>=S2_MaxValue)   //����Ѱ�����ֵ
//		{
//			S2_MaxValue = SET2_ADCValue;
//		}
}

///*��ȡ�ĸ�ADCͨ����������ƽ����ֵ*/
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

/*ADCIN�����ݵ���*/

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

