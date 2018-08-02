
///**
//  ********************************  STM32F0x1  *********************************
//  * @文件名     ： differentialDC.c
//  * @作者       ： HarryZeng
//  * @库版本     ： V1.5.0
//  * @文件版本   ： V1.0.0
//  * @日期       ： 2017年05月11日
//  * @摘要       ： 数据处理
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  更新日志:
//  2017-05-11 V1.0.0:初始版本
//  ----------------------------------------------------------------------------*/
///* 包含的头文件 --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "project.h"


/*DSP库宏定义：ARM_MATH_CM0*/

uint32_t DealyBaseTime = 8;
uint16_t DEL = 50;
uint8_t PWM_Set_Flag=0;
int16_t HI = 1000;
int16_t LO = 500;
bool timeflag = 0;
uint8_t LastOUT1 = 1;
uint8_t RegisterA = 0;
uint8_t LastRegisterA = 0;
uint8_t RegisterB = 1;
uint8_t RegisterC = 0;
uint8_t OUT1 = 0;
uint8_t OUT2 = 0;
uint8_t OUT3 = 0;
int16_t OUT2_TimerCounter = 0;
uint16_t OUT2_Timer = 0;
int16_t OUT3_TimerCounter = 0;
uint16_t OUT3_Timer = 0;
uint32_t ADCRawValue = 0;
int32_t ADC_Display = 0;
int32_t DACOUT1 = 1000;
int32_t DACOUT2 = 1000;
uint32_t CPV = 0;
uint8_t F1_F2_Mode=0;

//uint8_t ConfirmShortCircuit = 0;
//uint32_t ShortCircuitCounter = 0;
//uint32_t ShortCircuitLastTime = 0;
uint8_t KeyMappingFlag = 0;

uint8_t ShortCircuit = 0;
//uint32_t ShortCircuitTimer = 0;

uint8_t DisplayModeNo = 0;

void SetRegisterA(uint32_t GetADCValue);
void DisplayMODE(void);
void DisplayModeONE(void);
void DisplayModeTWO(void);
void DisplayModeTHIRD(void);
void DisplayModeFour(void);
void ShortCircuitProtection(void);
void SetOUT1Status(void);
void SetOUT2Status(void);
void SetOUT3Status(void);
void ButtonMapping(void);
void DEL_Set(void);
void DisplayModeONE_STD(void);
void DisplayModeONE_AREA(void);
void ResetParameter(void);
void Test_Delay(uint32_t ms);
uint8_t CheckDust(void);

extern int8_t PERCENTAGE;
extern int16_t ATT100;
extern uint16_t FSV;
extern int32_t SV;
extern uint8_t SelftStudyflag;
extern int8_t DSC;
/*----------------------------------宏定义-------------------------------------*/

uint32_t S_Buffer[5][32];
int8_t 	S_Row = 0;
float Final_1 = 0;
float Final = 0;

int32_t SX[4];
int32_t SX_Final[32];
uint8_t SX_Flag;
uint8_t SX_Index = 0;

int32_t S_Final = 0; /*S-SET*/
uint8_t S_Final_FinishFlag = 0;

uint32_t S32 = 0;
uint8_t S32_Flag = 0;


uint32_t S_Selft = 0;

int16_t Threshold = 1000;

int16_t DX = 0;
int16_t DX_Index = 0;
int16_t Last_DX = 0;
int16_t Min_DX = 4095;
int16_t Max_DX = 0;
uint8_t DX_Flag = 1;

int32_t TX_Index = 0;
int32_t TX = 0;
int32_t TX_Temp[4]={4096,4096,4096,4096};
int32_t TX_Sum=0;

int32_t 	SET_VREF = 0;
int16_t 	FX = 0;
uint8_t 	FX_Flag = 1;

/*求总和*/
void GetSum(uint32_t *SUM, uint32_t *arry, uint8_t arryLength)
{
	int j;
	for (j = 0; j < arryLength; j++)
	{
		*SUM += arry[j];
	}
}

/*求平均*/
void GetAverage(uint32_t *Average, uint32_t *arry, uint8_t arryLength)
{
	int j;
	uint32_t sum;
	for (j = 0; j < arryLength; j++)
	{
		sum += arry[j];
	}
	*Average = sum / j;
}


void JudgeTX(void)
{
	if(RegisterA==0)
	{
		if(TX_Temp[0]>Final_1)
			TX_Temp[0] = Final_1;
		else if(TX_Temp[1]>Final_1)
			TX_Temp[1] = Final_1;
		else if(TX_Temp[2]>Final_1)
			TX_Temp[2] = Final_1;
		else if(TX_Temp[3]>Final_1)
			TX_Temp[3] = Final_1;

		TX_Sum = TX_Temp[0]+TX_Temp[1]+TX_Temp[2]+TX_Temp[3];
		//TX_Index = 0;
		TX = TX_Sum / 4;
		TX_Sum = 0;
	
	}
}


/******************
找最大值
******************/
int16_t GetMAXValue(uint32_t *a,int16_t N)
{
	uint32_t max=0,sum;
	int16_t i,num;
	for(i=0; i<N; i++)
	{
		if(a[i]>max)
		{
		 max = a[i];
		 num = i;
		}
	}
	return num;
}


/*******************/
//void PWM_And_DIS_Set(uint16_t Pmode)
//{
//	PWM_GPIO_Port->BRR  = PWM_Pin;  //0
//	PWM_GPIO_Port->BSRR = PWM_Pin; 	//1
//}


/*	正常显示*/
/********************
*
*显示ADC的值处理
*
**********************/

void GetTotalADCValue(void)
{
	uint32_t Dispaly_Max = 0;
	uint32_t Dispaly_Min = 0;

	ADC_Display = Final;
}

uint8_t sample_finish = 0;

uint32_t Start_Counter = 0;
uint8_t RegisterA_1_Counter = 0;
uint8_t RegisterA_0_Counter = 0;
uint8_t TempRegisterA = 0;
int16_t DMA_ADC_Counter = 0;
uint8_t CheckCounter = 0;
uint8_t StartFlag=0;

int16_t TDIS=0;
int16_t TDIS1=0;
uint8_t N=0,N_1=0,N_2=0,N__1=0,N__2=0;
uint32_t DValue,DN_1=0,DN_2=0,DN__1=0,DN__2=0;
uint32_t DMAX=0;
uint32_t CCDMAX1=0;
uint8_t D_ERROR_Flag=0;
uint32_t PWM_Time_Counter=0;
uint32_t DS=0;
uint32_t DXYZ=0;
void DMA1_Channel1_IRQHandler(void)
{
	int i;
	if (DMA_GetITStatus(DMA_IT_TC)) //判断DMA传输完成中断
	{
			S_Buffer[S_Row][DMA_ADC_Counter] = 4095 - adc_dma_tab[0];
			DMA_ADC_Counter++;
			/*PWM和DIS 的输出*/
			if(PWM_Set_Flag)
			{
				_Gpio_PWM_Set;
				_Gpio_DIS_Reset;
				PWM_Time_Counter++;
				
				if(PWM_Time_Counter>=(TDIS/0.25))
				{
					PWM_Time_Counter=0;
					PWM_Set_Flag = 0;
					_Gpio_DIS_Set;
					_Gpio_PWM_Reset;
				}
			}
			
			if (DMA_ADC_Counter >= 32)
			{
				DMA_ADC_Counter = 0;
				Start_Counter++;
				if (StartFlag==1)  //用作延时200ms，0.000008s*25000 = 200ms 开机等待
				{
					//_Gpio_DIS_TRO;
						S_Row++;
						/*采集够四组数据*/
						if(S_Row>=4)
						{
							/*求四组数据对应累加平均*/
							for(i=0;i<32;i++)
								S_Buffer[S_Row][i] = (S_Buffer[0][i]+S_Buffer[1][i]+S_Buffer[2][i]+S_Buffer[3][i])/4;
							/*将PIX 0和PIX 31清零*/
							S_Buffer[4][0] = 0;
							S_Buffer[4][31] = 0;
							/*找出剩下30个数据最大值和下标*/
							N = GetMAXValue(S_Buffer[4],32);
							DMAX = S_Buffer[4][N];
							/*****DMAX是否在范围之内*****/
							//N = 15;
							if(DMAX>=50 && DMAX<=4000)
							{
								if(N>2 && N<30)
								{
									N_1 = N-1;
									N_2 = N-2;
									N__1 = N+1;
									N__2 = N+2;
									DN_1 = S_Buffer[4][N_1];
									DN_2 = S_Buffer[4][N_2];
									DN__1 = S_Buffer[4][N__1];
									DN__2 = S_Buffer[4][N__2];
								}
								else 
								{
										if(N<=2)
										{
											N_1 = 0;
											N_2 = 0;
											N__1 = N+1;
											N__2 = N+2;
											DN_1 = 0;
											DN_2 = 0;
											DN__1 = S_Buffer[4][N__1];
											DN__2 = S_Buffer[4][N__2];
										}
										else if(N>=30)
										{
											N_1 = N-1;
											N_2 = N-2;
											N__1 = 0;
											N__2 = 0;
											DN_1 = S_Buffer[4][N_1];
											DN_2 = S_Buffer[4][N_2];
											DN__1 = 0;
											DN__2 = 0;		
										}									
								}
								
								DValue = ((N_2*DN_2+N_1*DN_1+N*DMAX+N__1*DN__1+N__2*DN__2)*256)/(DN_2+DN_1+DMAX+DN__1+DN__2);
								
								Final_1 = DValue ;
								
								S_Row = 0;
				
//								if(displayModeONE_FLAG==1 || FX_Flag==0)	/**AREA模式下或者自学习情况下，FX=0，TX=0**/  //2018-7-12 去掉|| SelftStudyflag==1 
//								{
//									FX = 0;
//								}
//								else/*STD模式下*/
//								{					
//									/******TX******/
//									JudgeTX();
//									/*******FX*******/
//									FX = SET_VREF - TX;     /*求FX*/
//									if(FX>=600) FX = 600;		/**FX范围**/
//									else if(FX<=-600) FX = -600;
//								}
								
								FX = 0;
								Final = Final_1 - FX ;  //最终信号值
								
								if(Final>=9999)
										Final = 9999;
								if(Final<=0)
										Final = 0;
								
								/******Titme of DIS and PWM**********/
								
								if(F1_F2_Mode==0)  //F1 模式
								{
									TDIS = (TDIS1/DMAX)*2000;
									
									if(P_mode==0) 
									{
										if(TDIS>=40) TDIS =40;//P0 Mode
									}
									else if(P_mode==1) 
									{
										if(TDIS>=170) TDIS =170;//P1 Mode
									}
									else if(P_mode==2) 
									{
										if(TDIS>=370) TDIS =370;//P2 Mode
									}
									else if(P_mode==3) 
									{
										if(TDIS>=1570) TDIS =1570;//P3 Mode
									}
									
									TDIS1 = TDIS;  //纪录上一帧的DIS time
									
									/***************DX*************/
									
									DX_Index++;
									if(Final>=Max_DX)
										Max_DX = Final;
									if(Final<=Min_DX)
										Min_DX = Final;
									if(DX_Index>6)
									{
										DX_Index = 0;
										DX = Max_DX - Min_DX;
										Max_DX = 0;    /*初始化变量*/
										Min_DX = 4095; /*初始化变量*/
									}
									
									/***********Register A**********/
									if(displayModeONE_FLAG==1)	/**AREA模式**/
									{
										if(Final>=LO && Final<=HI)
											RegisterA = 1;
										else if((Final>=0&&Final<=(LO-DX-80))||(Final>=(HI+DX+80) && Final<=9999))
											RegisterA = 0;
									}
									else if(displayModeONE_FLAG==0)/**STD模式**/
									{
										if(Final<=Threshold-0.25*DX)
											RegisterA = 1;
										else if(Final>=Threshold+DX+80) 
											RegisterA = 0;
									}	
								}	
								else //F2模式 固定8000
								{
									if(Final >= Threshold)  DS = Final - Threshold;
									else if(Final < Threshold)  DS = Threshold - Final;
									
									
									
									
								}
							}
							else //DMAX不在范围之内
							{
									D_ERROR_Flag = 1;
									RegisterA = 0;  //OUT直接拉低
							}
							sample_finish = 1;

							/*设置OUT1的状态*/
							SetOUT1Status();
								/*OUT2输出*/
							SetOUT2Status();
								
							/*显示OUT1和OUT2的状态*/
							SMG_DisplayOUT_STATUS(OUT1, OUT2);
					}	
			}
			else 
			{
				//JudgeTX();//TX = Final_1;
				if(Start_Counter >=2500)
				{
					StartFlag = 1;
					//FX = SET_VREF;
				}
			}
		}
		DMA_ClearITPendingBit(DMA_IT_TC); //清楚DMA中断标志位
	}
}

void Main_Function(void)
{
	//GetEEPROM();
	
	while (1)
	{
		if (0)
		{
			Dust_Display();
			WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET); /*一直将OUT1拉低*/
		}
		else
		{
			/*正常显示模式*/
			if(D_ERROR_Flag==0)
			{
				DisplayMODE();
			}
			else 
			{
				DisplayFFFF();
			}

			/*按键复用*/
			ButtonMapping();

			if (KEY == ULOC) /*判断按键是否上锁*/
			{
				/*SET自学习模式*/
				if ((DisplayModeNo == 0 && displayModeONE_FLAG == 0) || (DisplayModeNo <= 1 && displayModeONE_FLAG == 1))
					selfstudy();
				/*Mode菜单模式*/
				menu();
			}
		}
	}
}


/******************************************
Main主函数
******************************************/
int main_start(void)
{
	uint32_t checkcouter;
	uint8_t CheckFLag;
	
	bsp_init();
	
	//CheckFLag = FlashCheck();

	if (1)
	//if(CheckFLag)
	{
		/*程序运行次数检测*/
		//ProgramCheck();
		/*主要运行函数*/
		
		Main_Function();
	}
	else
		while (1)
		{
			checkcouter++;
		}
}

/*******************************
*
*显示模式切换
*
*******************************/

void DisplayMODE(void)
{
	if (ModeButton.Status == Press && (DownButton.Status == Press || SetButton.Status == Press || UpButton.Status == Press))
	{
	}
	else
	{
		if (KEY == ULOC)
		{
			if (ModeButton.PressCounter == 0)
			{
				DisplayModeNo = 0;
			}
			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 1 && DownButton.Status == Release && UpButton.Status == Release)
			{
				DisplayModeNo = 1;
			}
			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 2 && DownButton.Status == Release && UpButton.Status == Release)
			{
				DisplayModeNo = 2;
			}
			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 3 && DownButton.Status == Release && UpButton.Status == Release)
			{
				DisplayModeNo = 3;
			}
			//			else if(ModeButton.Effect == PressShort && ModeButton.PressCounter==4 &&DownButton.Status==Release&&UpButton.Status==Release)
			//			{
			//				DisplayModeNo = 4;
			//			}
			/********mode 按键 循环*******/
			if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 3 && DownButton.Status == Release && displayModeONE_FLAG == 0) //if need to display Mode_Four,PressCounter=4
			{
				ModeButton.PressCounter = 0;
				DisplayModeNo = 0;
			}
			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 4 && DownButton.Status == Release && displayModeONE_FLAG == 1) //if need to display Mode_Four,PressCounter=5
			{
				ModeButton.PressCounter = 0;
				DisplayModeNo = 0;
			}
		}
		else
		{
			while (ModeButton.Status == Press || SetButton.Status == Press || DownButton.Status == Press || UpButton.Status == Press)
			{
				if (ModeButton.Effect == PressLong && UpButton.Status == Release && DownButton.Effect == PressLong && DownButton.Status == Press)
				{
					if (KEY == ULOC)
						KEY = LOC;
					else
					{
						KEY = ULOC;
						KeyMappingFlag = 0;
					}
					ModeButton.PressCounter = 0;
					while (ModeButton.Effect == PressLong && UpButton.Status == Release && DownButton.Effect == PressLong && DownButton.Status == Press)
					{
						ButtonMappingDisplay(1);
					}
					WriteFlash(KEY_FLASH_DATA_ADDRESS, KEY);
					ModeButton.Effect = PressNOEffect;
					ModeButton.PressCounter = 0;
					DownButton.PressCounter = 0;
					DownButton.Effect = PressNOEffect;
				}
				else
					ButtonMappingDisplay(1);
			}
		}
		/*显示*/
		if ((DisplayModeNo == 0 && displayModeONE_FLAG == 0) || (DisplayModeNo < 1 && displayModeONE_FLAG == 1))
		{
			SMG_DisplayModeONE(1,0,ADC_Display);
			//DisplayModeONE();
		}
		else if ((DisplayModeNo == 1 && displayModeONE_FLAG == 0) || (DisplayModeNo <= 2 && displayModeONE_FLAG == 1))
		{
			//DisplayModeTWO();
			DisplayModeONE();
			//DisplayModeTHIRD();
		}
		else if ((DisplayModeNo == 2 && displayModeONE_FLAG == 0) || (DisplayModeNo == 3 && displayModeONE_FLAG == 1))
		{
			DisplayModeTWO();
			//DisplayModeTHIRD();
			//DisplayModeFour();
		}
		else if ((DisplayModeNo == 3 && displayModeONE_FLAG == 0) || (DisplayModeNo == 4 && displayModeONE_FLAG == 1))
		{
			//DisplayModeFour();
		}
	}
}

/*******************************
*
*显示模式1
*
*******************************/
int8_t LastDSC;
void DisplayModeONE(void)
{
	if (displayModeONE_FLAG)
	{
		if (DSC)
		{
			LastDSC = DSC;
			DSC = 0; //区域模式下，DX一直为0
		}
		DisplayModeONE_AREA();
	}
	else
	{
		if (LastDSC)
		{
			LastDSC = 0;
			DSC = 1;
		}
		DisplayModeONE_STD();
	}
}

/*******************************
*
*显示模式1_DETECT_STD
*
*******************************/

void DisplayModeONE_STD(void)
{
	static uint8_t lastCounter;
	static int16_t LastThreshold;


	if (ModeButton.Status == Release && KeyMappingFlag == 0 && KEY == ULOC)
	{
		/*Up Button*/
		LastThreshold = Threshold;
		if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
		{
			lastCounter = UpButton.PressCounter;
			UpButton.PressCounter = 0;
			Threshold = Threshold + 1;
			if (Threshold >= 9999)
				Threshold = 9999;
				///*数码管显示*/
			//SMG_DisplayModeONE_DTH(1,Threshold, ADC_Display);
		}
		else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
		{ /*还按着按键，并且时间超过长按时间*/
			UpButton.PressCounter = 0;
			if (UpButton.PressTimer <= KEY_LEVEL_1)
			{
				if (UpButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
				{
					Threshold = Threshold + 1;
					tempPress = 0;
				}
			}
			else if (UpButton.PressTimer > KEY_LEVEL_1 && UpButton.PressTimer <= KEY_LEVEL_2)
			{
				if (UpButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
				{
					tempPress = 0;
					Threshold = Threshold + 2;
				}
			}
			else
			{
				if (UpButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
				{
					tempPress = 0;
					Threshold = Threshold + 5;
				}
			}
			if (Threshold >= 9999)
				Threshold = 9999;
				/*数码管显示*/
			SMG_DisplayModeONE_DTH(1,Threshold, ADC_Display);
		}
//		else
//		{
//			UpButton.Effect = PressShort;
//				/*数码管显示*/
//			SMG_DisplayModeONE_DTH(timeflag,Threshold, ADC_Display);
//		}
		/*Down Button*/
		else if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
		{
			DownButton.PressCounter = 0;
			Threshold = Threshold - 1;
			if (Threshold <= 0)
					Threshold = 0;
		}
		else if (DownButton.Status == Press && (DownButton.Effect == PressLong))
		{
			DownButton.PressCounter = 0;
			if (DownButton.PressTimer < KEY_LEVEL_1)
			{
				if (DownButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
				{
					Threshold = Threshold - 1;
					tempPress = 0;
				}
			}
			else if (DownButton.PressTimer > KEY_LEVEL_1 && DownButton.PressTimer < KEY_LEVEL_2)
			{
				if (DownButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
				{
					Threshold = Threshold - 2;
					tempPress = 0;
				}
			}
			else
			{
				if (DownButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
				{
					tempPress = 0;
					Threshold = Threshold - 5;
				}
			}
			if (Threshold <= 0)
					Threshold = 0;
			/*数码管显示*/
			SMG_DisplayModeONE_DTH(1,Threshold, ADC_Display);
		}
		else
		{
			DownButton.Effect = PressShort;
			/*数码管显示*/
			SMG_DisplayModeONE_DTH(timeflag,Threshold, ADC_Display);
		}
		if (LastThreshold != Threshold && DownButton.Status == Release && UpButton.Status == Release)
		{
			WriteFlash(Threshold_FLASH_DATA_ADDRESS, Threshold);
		}
	}


}

/*******************************
*
*显示模式1_DETECT_AREA
*
*******************************/
void DisplayModeONE_AREA(void)
{
	static uint8_t lastCounter;
	static int16_t LastHIValue;
	static int16_t LastLOValue;

	/*HI display mode*/
	if (DisplayModeNo == 1)
	{
		if (ModeButton.Status == Release && KeyMappingFlag == 0 && KEY == ULOC)
		{
			/*Up Button*/
			LastHIValue = HI;
			if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
			{
				lastCounter = UpButton.PressCounter;
				UpButton.PressCounter = 0;
				HI = HI + 1;
				if (HI >= 9999)
					HI = 9999;
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, 0); /*显示阀值*/
			}
			else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
			{ /*还按着按键，并且时间超过长按时间*/
				UpButton.PressCounter = 0;
				if (UpButton.PressTimer <= KEY_LEVEL_1)
				{
					if (UpButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI + 1;
					}
				}
				else if (UpButton.PressTimer > KEY_LEVEL_1 && UpButton.PressTimer <= KEY_LEVEL_2)
				{
					if (UpButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI + 2;
					}
				}
				else
				{
					if (UpButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI + 5;
					}
				}
				if (HI >= 9999)
					HI = 9999;
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, 0); /*显示阀值*/
			}
			//					else
			//					{
			//						UpButton.Effect = PressShort;
			//						SMG_DisplayModeONE_Detect_AREA_HI(timeflag,HI,ADC_Display); /*交替显示HI与阀值*/
			//					}
			/*Down Button*/
			else if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
			{
				DownButton.PressCounter = 0;
				HI = HI - 1;
				if (HI <= 0)
					HI = 0;
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*显示阀值*/
			}
			else if (DownButton.Status == Press && (DownButton.Effect == PressLong))
			{
				DownButton.PressCounter = 0;
				if (DownButton.PressTimer < KEY_LEVEL_1)
				{
					if (DownButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI - 1;
					}
				}
				else if (DownButton.PressTimer > KEY_LEVEL_1 && DownButton.PressTimer < KEY_LEVEL_2)
				{
					if (DownButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI - 2;
					}
				}
				else
				{
					if (DownButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						HI = HI - 5;
					}
				}
				if (HI <= 0)
					HI = 0;
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*显示阀值*/
			}
			else
			{
				DownButton.Effect = PressShort;
				SMG_DisplayModeONE_Detect_AREA_HI(timeflag, HI, ADC_Display); /*交替显示HI与阀值*/
			}
			if (LastHIValue != HI && DownButton.Status == Release && UpButton.Status == Release)
			{
				WriteFlash(HI_FLASH_DATA_ADDRESS,HI);
			}
		}
	}

	/*LO display mode*/
	else if (DisplayModeNo == 2)
	{
		if (ModeButton.Status == Release && KeyMappingFlag == 0 && KEY == ULOC)
		{
			/*Up Button*/
			LastLOValue = LO;
			if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
			{
				lastCounter = UpButton.PressCounter;
				UpButton.PressCounter = 0;
				LO = LO + 1;
				if (LO >= 9999)
					LO = 9999;
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*显示阀值*/
			}
			else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
			{ /*还按着按键，并且时间超过长按时间*/
				UpButton.PressCounter = 0;
				if (UpButton.PressTimer <= KEY_LEVEL_1)
				{
					if (UpButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO + 1;
					}
				}
				else if (UpButton.PressTimer > KEY_LEVEL_1 && UpButton.PressTimer <= KEY_LEVEL_2)
				{
					if (UpButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO + 2;
					}
				}
				else
				{
					if (UpButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO + 5;
					}
				}
				if (LO >= 9999)
					LO = 9999;
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*显示阀值*/
			}
			//					else
			//					{
			//						UpButton.Effect = PressShort;
			//						SMG_DisplayModeONE_Detect_AREA_LO(timeflag,LO,ADC_Display);/*交替显示LO与阀值*/
			//					}
			/*Down Button*/
			else if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
			{
				DownButton.PressCounter = 0;
				LO = LO - 1;
				if (LO <= 0)
					LO = 0;
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*显示阀值*/
			}
			else if (DownButton.Status == Press && (DownButton.Effect == PressLong))
			{
				DownButton.PressCounter = 0;
				if (DownButton.PressTimer < KEY_LEVEL_1)
				{
					if (DownButton.PressTimer % KEY_LEVEL_1_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO - 1;
					}
				}
				else if (DownButton.PressTimer > KEY_LEVEL_1 && DownButton.PressTimer < KEY_LEVEL_2)
				{
					if (DownButton.PressTimer % KEY_LEVEL_2_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO - 2;
					}
				}
				else
				{
					if (DownButton.PressTimer % KEY_LEVEL_3_SET == 0 && tempPress == 1)
					{
						tempPress = 0;
						LO = LO - 5;
					}
				}
				if (LO <= 0)
					LO = 0;
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*显示阀值*/
			}
			else
			{
				DownButton.Effect = PressShort;
				SMG_DisplayModeONE_Detect_AREA_LO(timeflag, LO, ADC_Display); /*交替显示LO与阀值*/
			}
			if (LastLOValue != LO && DownButton.Status == Release && UpButton.Status == Release)
			{
				WriteFlash(LO_FLASH_DATA_ADDRESS,LO);
			}
		}
	}
}

/*******************************
*
*显示模式2
*
*******************************/
void DisplayModeTWO(void)
{
	static uint8_t lastCounter;
	/*数码管显示*/
	SMG_DisplayModeTWO(RegisterB);

	/*Up Button*/
	if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
	{
		lastCounter = UpButton.PressCounter;
		UpButton.PressCounter = 0;
		if (RegisterB == 0)
			RegisterB = 1;
		else
			RegisterB = 0;
		WriteFlash(RegisterB_FLASH_DATA_ADDRESS, RegisterB);
	}

	/*Down Button*/
	if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
	{
		DownButton.PressCounter = 0;
		if (RegisterB == 0)
			RegisterB = 1;
		else
			RegisterB = 0;
		WriteFlash(RegisterB_FLASH_DATA_ADDRESS, RegisterB);
	}
}

/*******************************
*
*显示模式3
*
*******************************/
void DisplayModeTHIRD(void)
{
	/*数码管显示*/
	SMG_DisplayModeTHIRD(CPV);
	/*以下为清楚按键计数，防止会影响到显示模式4*/
	DownButton.PressCounter = 0;
	UpButton.PressCounter = 0;
}

/*******************************
*
*显示模式4
*
*******************************/
void DisplayModeFour(void)
{
	DEL_Set();
}

/*******************************
*
*OUT1_DEL 应差值设置
*
*******************************/
void DEL_Set(void)
{
	static uint8_t lastCounter;
	uint16_t LastDEL;

	/*显示SHOT,闪烁*/
	SMG_DisplayMenuTwo_DEL_SET(DEL, 0);

	/*Up Button*/
	LastDEL = DEL;
	if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
	{
		lastCounter = UpButton.PressCounter;
		UpButton.PressCounter = 0;
		DEL = DEL + 1;
	}
	else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
	{ /*还按着按键，并且时间超过长按时间*/
		UpButton.PressCounter = 0;
		if (UpButton.PressTimer < KEY_LEVEL_1)
		{
			if (UpButton.PressTimer % KEY_LEVEL_1_SET == 0)
				DEL = DEL + 1;
		}
		else if (UpButton.PressTimer > KEY_LEVEL_1 && UpButton.PressTimer < KEY_LEVEL_2)
		{
			if (UpButton.PressTimer % KEY_LEVEL_2_SET == 0)
				DEL = DEL + 1;
		}
		else
		{
			if (UpButton.PressTimer % KEY_LEVEL_3_SET == 0)
				DEL = DEL + 1;
		}
	}
	else
	{
		UpButton.Effect = PressShort;
	}
	/*Down Button*/
	if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
	{
		DownButton.PressCounter = 0;
		DEL = DEL - 1;
	}
	else if (DownButton.Status == Press && (DownButton.Effect == PressLong))
	{ /*还按着按键，并且时间超过长按时间*/
		DownButton.PressCounter = 0;
		if (DownButton.PressTimer < KEY_LEVEL_1)
		{
			if (DownButton.PressTimer % KEY_LEVEL_1_SET == 0)
				DEL = DEL - 1;
		}
		else if (DownButton.PressTimer > KEY_LEVEL_1 && DownButton.PressTimer < KEY_LEVEL_2)
		{
			if (DownButton.PressTimer % KEY_LEVEL_2_SET == 0)
				DEL = DEL - 1;
		}
		else
		{
			if (DownButton.PressTimer % KEY_LEVEL_3_SET == 0)
				DEL = DEL - 1;
		}
	}
	else
	{
		DownButton.Effect = PressShort;
	}
	if (LastDEL != DEL && DownButton.Status == Release && UpButton.Status == Release)
	{
		//WriteFlash(DEL_FLASH_DATA_ADDRESS,DEL);
	}
	if (DEL >= 500)
		DEL = 500;
	else if (DEL <= 4)
		DEL = 4;
	//	}
}

/*******************************
*
*判断OUT1的输出状态
*
*******************************/
uint8_t SHOTflag = 0;
uint8_t CPV_Status=0;

void SetOUT1Status(void)
{
	if (ShortCircuit != 1) /*不是短路保护的情况下才判断OUT1的输出*/
	{
		/*同或运算*/
//		if (GPIO_ReadInputDataBit(BUTTON_SWITCH_GPIO_Port, BUTTON_SWITCH_Pin))
//			RegisterB = 0;
//		else
//			RegisterB = 1;

		OUT1 = !(RegisterB ^ RegisterA);
		if (OUT1_Mode.DelayMode == TOFF)
		{
			//GPIOA->ODR ^= GPIO_Pin_9;
			if (OUT1 == 0)
			{
				WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET);
				OUT1_Mode.DelayCounter = 0;
			}
			else
			{
				WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_SET);
				OUT1_Mode.DelayCounter = 0;
				CPV_Status = 1;
			}
		}
		/*OFFD*/
		else if (OUT1_Mode.DelayMode == OFFD)
		{
			if (OUT1 == 0)
			{
				if (OUT1_Mode.DelayCounter > (OUT1_Mode.DelayValue * DealyBaseTime))
				{
					WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET);
					CPV_Status = 1;
				}
			}
			else
			{
				WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_SET);
				OUT1_Mode.DelayCounter = 0;
			}			
		}
		/*ON_D*/
		else if (OUT1_Mode.DelayMode == ON_D)
		{
			if (OUT1 == 0)
			{
				WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET);
				OUT1_Mode.DelayCounter = 0;
			}
			else
			{
				if (OUT1_Mode.DelayCounter > (OUT1_Mode.DelayValue * DealyBaseTime))
				{
					WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_SET);
					CPV_Status = 1;
				}
			}
		}
		/*SHOT*/
		else if (OUT1_Mode.DelayMode == SHOT)
		{
			if (OUT1 == 0 && SHOTflag ==0)
			{
				OUT1_Mode.DelayCounter = 0;
				WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET);
			}
			else if(OUT1 ==1 || SHOTflag == 1)
			{
				if (OUT1_Mode.DelayCounter < (OUT1_Mode.DelayValue * DealyBaseTime))
				{
					WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_SET);
					SHOTflag = 1;
					
				}
				else
				{
					WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET);
					SHOTflag = 0;
					CPV_Status = 1;
				}
			}
		}
		
		/*********************CPV**************************/
//			if(LastOUT1 == 0 && OUT1 == 1 && CPV_Status == 1)
//			{
//				CPV++;
//				CPV_Status = 0;
//				if (CPV >= CSV) /*如果计数器达到预先设定的CSV，清零，OUT2输出一个高电平*/
//				{
//					OUT2 = 1;
//					CPV = 0;
//				}
//			}		
			LastOUT1 = OUT1;
	}
}
/*******************************
*
*判断OUT2的输出状态
*
*******************************/
void SetOUT2Status(void)
{
	if (ShortCircuit != 1) /*不是短路保护的情况下才判断OUT2的输出*/
	{
		if (OUT2)
		{
			//GPIO_WriteBit(OUT2_GPIO_Port, OUT2_Pin, Bit_SET); /*拉高*/
		}
		if (OUT2_TimerCounter >= 80)
		{
			OUT2 = 0;
			OUT2_TimerCounter = 0;								/*获取当前时间*/
			//WriteGPIO_Pin_State(OUT2_GPIO_Port, OUT2_Pin, Bit_RESET); /*80ms后拉低*/
		}
	}
}

/*******************************
*
*判断OUT3的输出状态
*
*******************************/
void SetOUT3Status(void)
{
	if (ShortCircuit != 1) /*不是短路保护的情况下才判断OUT2的输出*/
	{
		if (OUT3)
		{
			//WriteGPIO_Pin_State(OUT3_GPIO_Port,OUT3_Pin,Bit_SET);/*拉高*/
		}
		if (OUT3_TimerCounter >= 160)
		{
			OUT3 = 0;
			OUT3_TimerCounter = 0; /*获取当前时间*/
								   //GPIO_WriteBit(OUT3_GPIO_Port,OUT3_Pin,Bit_RESET);/*80ms后拉低*/
		}
	}
}

/*******************************
*
*短路保护
*
*******************************/
void ShortCircuitProtection(void)
{
//	uint8_t SCState;

//	/*读取SC引脚的状态*/
//	if (ShortCircuit != 1)
//	{
//		//SCState = GPIO_ReadInputDataBit(SC_GPIO_Port ,SC_Pin);
//		if ((BitAction)SCState == Bit_RESET)
//		{
//			/*拉低FB_SC*/
//			ShortCircuit = 1;
//		}
//		else
//		{
//			ShortCircuit = 0;
//			ConfirmShortCircuit = 0;
//		}
//	}
//	if (ShortCircuit && ShortCircuitCounter >= 100)
//	{
//		ConfirmShortCircuit = 1;
//		GPIO_WriteBit(OUT1_GPIO_Port, OUT1_Pin, Bit_RESET);
//		//GPIO_WriteBit(OUT2_GPIO_Port, OUT2_Pin, Bit_RESET); /*马上拉低OUT*/
//		//GPIO_WriteBit(OUT3_GPIO_Port,OUT3_Pin,Bit_RESET);/*马上拉低OUT*/
//		ShortCircuitTimer = ShortCircuitLastTime;
//	}
}

/*******************************
*
*按键复用
*
*******************************/
void ButtonMapping(void)
{
	/*按键上锁*/
	if (ModeButton.Effect == PressLong && UpButton.Status == Release && DownButton.Effect == PressLong && DownButton.Status == Press)
	{
		if (KEY == ULOC)
			KEY = LOC;
		else
			KEY = ULOC;
		ModeButton.PressCounter = 0;
		while (ModeButton.Effect == PressLong && UpButton.Status == Release && DownButton.Effect == PressLong && DownButton.Status == Press)
		{
			ButtonMappingDisplay(1);
			KeyMappingFlag = 1;
		}
		WriteFlash(KEY_FLASH_DATA_ADDRESS, KEY);
		ModeButton.Effect = PressNOEffect;
		ModeButton.PressCounter = 0;
		DownButton.PressCounter = 0;
		DownButton.Effect = PressNOEffect;
	}
	/*软件初始化*/
	else if (ModeButton.Effect == PressLong && SetButton.Effect == PressLong && SetButton.Status == Press && UpButton.Status == Release && DownButton.Status == Release)
	{
		takeoffLED();
		while ((ReadButtonStatus(&ModeButton)) == Press && (ReadButtonStatus(&SetButton) == Press))
		{
			EraseFlash();
			while ((ReadButtonStatus(&ModeButton)) == Press && (ReadButtonStatus(&SetButton) == Press))
				ButtonMappingDisplay(2);
		}

		ResetParameter();

		ModeButton.PressCounter = 0;
		ModeButton.Effect = PressNOEffect;
		DownButton.PressCounter = 0;
		DownButton.Effect = PressNOEffect;
		UpButton.PressCounter = 0;
		UpButton.Effect = PressNOEffect;
		Test_Delay(1000);
	}
	/*计算器清零*/
	else if (ModeButton.Effect == PressLong && UpButton.Status == Press && UpButton.Effect == PressLong && DownButton.Status == Release)
	{
		CPV = 0;
		while (ModeButton.Effect == PressLong && UpButton.Status == Press && UpButton.Effect == PressLong && DownButton.Status == Release)
		{
			ButtonMappingDisplay(3);
		}
		ModeButton.Effect = PressNOEffect;
		ModeButton.PressTimer = 0;
		ModeButton.PressCounter = 0;
		UpButton.PressCounter = 0;
		UpButton.Effect = PressNOEffect;
		Test_Delay(1000);
	}
}

void Test_Delay(uint32_t ms)
{
	uint32_t i;

	/*　
		CPU主频168MHz时，在内部Flash运行, MDK工程不优化。用台式示波器观测波形。
		循环次数为5时，SCL频率 = 1.78MHz (读耗时: 92ms, 读写正常，但是用示波器探头碰上就读写失败。时序接近临界)
		循环次数为10时，SCL频率 = 1.1MHz (读耗时: 138ms, 读速度: 118724B/s)
		循环次数为30时，SCL频率 = 440KHz， SCL高电平时间1.0us，SCL低电平时间1.2us

		上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us

		实际应用选择400KHz左右的速率即可
	*/
	for (i = 0; i < ms * 100; i++)
		;
}
/*******************************
*
*获取EEPROM参数
*
*******************************/


void GetEEPROM(void)
{

	//			//OUT1_Mode.DelayMode 	= *(__IO uint32_t*)(OUT1_Mode_FLASH_DATA_ADDRESS);
	//			OUT1_Mode.DelayValue 	= *(__IO uint32_t*)(OUT1_Value_FLASH_DATA_ADDRESS);
	//			CSV 									= *(__IO uint32_t*)(CSV_FLASH_DATA_ADDRESS);
	//			Threshold 						= *(__IO uint32_t*)(Threshold_FLASH_DATA_ADDRESS);
	//			DACOUT 								= *(__IO uint32_t*)(DACOUT_FLASH_DATA_ADDRESS);
	//			KEY 									= *(__IO uint32_t*)(KEY_FLASH_DATA_ADDRESS);
	//			RegisterB 						= *(__IO uint32_t*)(RegisterB_FLASH_DATA_ADDRESS);
	//			DEL 									= *(__IO uint32_t*)(DEL_FLASH_DATA_ADDRESS);
	//			HI 										= *(__IO uint32_t*)(HI_FLASH_DATA_ADDRESS);
	//			LO 										= *(__IO uint32_t*)(LO_FLASH_DATA_ADDRESS);
	//			displayModeONE_FLAG 	= *(__IO uint32_t*)(DETECT_FLASH_DATA_ADDRESS);

	OUT1_Mode.DelayMode = ReadFlash(OUT1_Mode_FLASH_DATA_ADDRESS);
	OUT1_Mode.DelayValue = ReadFlash(OUT1_Value_FLASH_DATA_ADDRESS);
	//CSV = ReadFlash(CSV_FLASH_DATA_ADDRESS);
	Threshold = ReadFlash(Threshold_FLASH_DATA_ADDRESS);
	DACOUT1 = ReadFlash(DACOUT1_FLASH_DATA_ADDRESS);
	KEY = ReadFlash(KEY_FLASH_DATA_ADDRESS);
	RegisterB = ReadFlash(RegisterB_FLASH_DATA_ADDRESS);
	DEL = ReadFlash(DEL_FLASH_DATA_ADDRESS);
	SET_VREF = ReadFlash(SET_VREF_FLASH_DATA_ADDRESS);
	//SB_MaxValue = ReadFlash(SB_MAX_FLASH_DATA_ADDRESS);
	displayModeONE_FLAG = ReadFlash(DETECT_FLASH_DATA_ADDRESS);
	HI = ReadFlash(HI_FLASH_DATA_ADDRESS);
	LO = ReadFlash(LO_FLASH_DATA_ADDRESS);
	DSC = ReadFlash(DSC_FLASH_DATA_ADDRESS);

//	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)DACOUT1);
//	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
//	DAC_SetChannel2Data(DAC_Align_12b_R, (uint16_t)DACOUT2);
//	DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}

/*****************************
*
*初始化所有参数
*
****************************/
void ResetParameter(void)
{
	Threshold = 1000;
	KEY = ULOC;
	OUT1_Mode.DelayMode = TOFF;
	OUT1_Mode.DelayValue = 10;
	ATT100 = 100;
	DEL = 4;
	RegisterB = 1;
	HI = 1000;
	LO = 500;
	displayModeONE_FLAG = 0;
	PERCENTAGE = 1;
	DSC = 1;
	
	TX = SET_VREF;
	TX_Sum=0;
	TX_Index = 0;
	FX = 0;
	
	WriteFlash(OUT1_Mode_FLASH_DATA_ADDRESS, OUT1_Mode.DelayMode);
	Test_Delay(50);
	WriteFlash(OUT1_Value_FLASH_DATA_ADDRESS, OUT1_Mode.DelayValue);
	Test_Delay(50);
//	WriteFlash(CSV_FLASH_DATA_ADDRESS, CSV);
//	Test_Delay(50);
	WriteFlash(Threshold_FLASH_DATA_ADDRESS, Threshold);
	Test_Delay(50);
	WriteFlash(DACOUT1_FLASH_DATA_ADDRESS, DACOUT1);
	Test_Delay(50);
	WriteFlash(KEY_FLASH_DATA_ADDRESS, KEY);
	Test_Delay(50);
	WriteFlash(RegisterB_FLASH_DATA_ADDRESS, RegisterB);
	Test_Delay(50);
	WriteFlash(DEL_FLASH_DATA_ADDRESS, DEL);
	Test_Delay(50);
	WriteFlash(SET_VREF_FLASH_DATA_ADDRESS, SET_VREF);
	Test_Delay(50);
//	WriteFlash(SB_MAX_FLASH_DATA_ADDRESS, SB_MaxValue);
	Test_Delay(50);
	WriteFlash(DETECT_FLASH_DATA_ADDRESS, displayModeONE_FLAG);
	Test_Delay(50);
	WriteFlash(HI_FLASH_DATA_ADDRESS, HI);
	Test_Delay(50);
	WriteFlash(LO_FLASH_DATA_ADDRESS, LO);
	Test_Delay(50);
	WriteFlash(DSC_FLASH_DATA_ADDRESS, DSC);

	ModeButton.Effect = PressNOEffect;
	ModeButton.PressTimer = 0;
	ModeButton.PressCounter = 0;
	SetButton.Effect = PressNOEffect;
	SetButton.PressCounter = 0;
}
