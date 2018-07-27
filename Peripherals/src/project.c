
///**
//  ********************************  STM32F0x1  *********************************
//  * @�ļ���     �� differentialDC.c
//  * @����       �� HarryZeng
//  * @��汾     �� V1.5.0
//  * @�ļ��汾   �� V1.0.0
//  * @����       �� 2017��05��11��
//  * @ժҪ       �� ���ݴ���
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  ������־:
//  2017-05-11 V1.0.0:��ʼ�汾
//  ----------------------------------------------------------------------------*/
///* ������ͷ�ļ� --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "project.h"


/*DSP��궨�壺ARM_MATH_CM0*/

uint32_t DealyBaseTime = 8;
uint16_t DEL = 50;

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
extern 
/*----------------------------------�궨��-------------------------------------*/

uint8_t DustFlag = 0;

int32_t SA = 0;
int32_t SA_Sum = 0;
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

/*���ܺ�*/
void GetSum(uint32_t *SUM, uint32_t *arry, uint8_t arryLength)
{
	int j;
	for (j = 0; j < arryLength; j++)
	{
		*SUM += arry[j];
	}
}

/*��ƽ��*/
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

/*	������ʾ*/
/********************
*
*��ʾADC��ֵ����
*
**********************/

void GetTotalADCValue(void)
{
	uint32_t Dispaly_Max = 0;
	uint32_t Dispaly_Min = 0;

	ADC_Display = Final;
}

uint8_t sample_finish = 0;

uint32_t DMA_Counter = 0;
uint8_t RegisterA_1_Counter = 0;
uint8_t RegisterA_0_Counter = 0;
uint8_t TempRegisterA = 0;
int16_t DMA_ADC_Counter = 0;
uint8_t CheckCounter = 0;
uint8_t StartFlag=0;
void DMA1_Channel1_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA_IT_TC)) //�ж�DMA��������ж�
	{
			//_Gpio_Test_TRO;
			SA = 4095 - adc_dma_tab[0];
			SA_Sum = SA_Sum+SA;
			DMA_ADC_Counter++;
			if (DMA_ADC_Counter >= 4)
			{
				//_Gpio_Test_TRO;
				DMA_ADC_Counter = 0;
				Final_1 = SA_Sum / 4;
				SA_Sum = 0;
				DMA_Counter++;
				if (StartFlag==1)  //������ʱ200ms��50us*4��=200us������200ms = 200us*1000
				{
						if(displayModeONE_FLAG==1 || FX_Flag==0)	/**AREAģʽ�»�����ѧϰ����£�FX=0��TX=0**/  //2018-7-12 ȥ��|| SelftStudyflag==1 
						{
							FX = 0;
							//TX = 0;
						}
						else/*STDģʽ��*/
						{					
							/******TX******/
							JudgeTX();
							/*******FX*******/
							FX = SET_VREF - TX;     /*��FX*/
							if(FX>=600) FX = 600;		/**FX��Χ**/
							else if(FX<=-600) FX = -600;
						}
						
						Final = Final_1 - FX ;  //�����ź�ֵ
						
						if(Final>=9999)
								Final = 9999;
						if(Final<=0)
								Final = 0;
						
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
							Max_DX = 0;    /*��ʼ������*/
							Min_DX = 4095; /*��ʼ������*/
						}
						
						/***********Register A**********/
						if(displayModeONE_FLAG==1)	/**AREAģʽ**/
						{
							if(Final>=LO+2+DX && Final<=HI-2-DX)
								RegisterA = 1;
							else if((Final>=0&&Final<=LO-20-LO/128-0.125*DX)||(Final>=HI+20+HI/128+0.125*DX && Final<=9999)) //2018-06-18
								RegisterA = 0;
						}
						else if(displayModeONE_FLAG==0)/**STDģʽ**/
						{
							if(Final>=Threshold+2+DX)  //2018-06-18  TH+2+DX
								RegisterA = 1;
							else if(Final<=Threshold-4-Threshold/128-0.125*DX) //2018-06-19 TH-4-TH/128-0.125*DX
								RegisterA = 0;
						}		

				sample_finish = 1;

				/*����OUT1��״̬*/
				SetOUT1Status();
					/*OUT2���*/
				SetOUT2Status();
					
				/*��ʾOUT1��OUT2��״̬*/
				SMG_DisplayOUT_STATUS(OUT1, OUT2);
			}
			else 
			{
				JudgeTX();//TX = Final_1;   /*200msǰ��ʹ��Final_1��ΪTX*/ 2018-7-11�޸ĳ�JudgeTX();
				if(DMA_Counter >=1000)
				{
					StartFlag = 1;
					FX = SET_VREF;
				}
			}
		}
		DMA_ClearITPendingBit(DMA_IT_TC); //���DMA�жϱ�־λ
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
			WriteGPIO_Pin_State(OUT1_GPIO_Port, OUT1_Pin, IO_Bit_RESET); /*һֱ��OUT1����*/
		}
		else
		{
			/*������ʾģʽ*/
			DisplayMODE();

			/*��������*/
			ButtonMapping();

			if (KEY == ULOC) /*�жϰ����Ƿ�����*/
			{
				/*SET��ѧϰģʽ*/
				if ((DisplayModeNo == 0 && displayModeONE_FLAG == 0) || (DisplayModeNo <= 1 && displayModeONE_FLAG == 1))
					selfstudy();
				/*Mode�˵�ģʽ*/
				menu();
			}
		}
	}
}


/******************************************
Main������
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
		/*�������д������*/
		//ProgramCheck();
		/*��Ҫ���к���*/
		
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
*��ʾģʽ�л�
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
//			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 3 && DownButton.Status == Release && UpButton.Status == Release)
//			{
//				DisplayModeNo = 3;
//			}
			//			else if(ModeButton.Effect == PressShort && ModeButton.PressCounter==4 &&DownButton.Status==Release&&UpButton.Status==Release)
			//			{
			//				DisplayModeNo = 4;
			//			}
			/********mode ���� ѭ��*******/
			if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 2 && DownButton.Status == Release && displayModeONE_FLAG == 0) //if need to display Mode_Four,PressCounter=4
			{
				ModeButton.PressCounter = 0;
				DisplayModeNo = 0;
			}
			else if (ModeButton.Effect == PressShort && ModeButton.PressCounter == 3 && DownButton.Status == Release && displayModeONE_FLAG == 1) //if need to display Mode_Four,PressCounter=5
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
		/*��ʾ*/
		if ((DisplayModeNo == 0 && displayModeONE_FLAG == 0) || (DisplayModeNo <= 1 && displayModeONE_FLAG == 1))
		{
			DisplayModeONE();
		}
		else if ((DisplayModeNo == 1 && displayModeONE_FLAG == 0) || (DisplayModeNo == 2 && displayModeONE_FLAG == 1))
		{
			DisplayModeTWO();
			//DisplayModeTHIRD();
		}
		else if ((DisplayModeNo == 2 && displayModeONE_FLAG == 0) || (DisplayModeNo == 3 && displayModeONE_FLAG == 1))
		{
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
*��ʾģʽ1
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
			DSC = 0; //����ģʽ�£�DXһֱΪ0
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
*��ʾģʽ1_DETECT_STD
*
*******************************/

void DisplayModeONE_STD(void)
{
	static uint8_t lastCounter;
	static int16_t LastThreshold;

	/*�������ʾ*/
	SMG_DisplayModeONE(timeflag,Threshold, ADC_Display);

	if (ModeButton.Status == Release && KeyMappingFlag == 0 && KEY == ULOC)
	{
		/*Up Button*/
		LastThreshold = Threshold;
		if (UpButton.PressCounter != lastCounter && UpButton.Effect == PressShort)
		{
			lastCounter = UpButton.PressCounter;
			UpButton.PressCounter = 0;
			Threshold = Threshold + 1;
		}
		else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
		{ /*�����Ű���������ʱ�䳬������ʱ��*/
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
		}
		else
		{
			UpButton.Effect = PressShort;
		}
		/*Down Button*/
		if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
		{
			DownButton.PressCounter = 0;
			Threshold = Threshold - 1;
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
		}
		else
		{
			DownButton.Effect = PressShort;
		}
		if (LastThreshold != Threshold && DownButton.Status == Release && UpButton.Status == Release)
		{
			WriteFlash(Threshold_FLASH_DATA_ADDRESS, Threshold);
		}
	}
	if (Threshold >= 9999)
		Threshold = 9999;
	else if (Threshold <= 0)
		Threshold = 0;
}

/*******************************
*
*��ʾģʽ1_DETECT_AREA
*
*******************************/
void DisplayModeONE_AREA(void)
{
	static uint8_t lastCounter;
	static int16_t LastHIValue;
	static int16_t LastLOValue;

	/*HI display mode*/
	if (DisplayModeNo == 0)
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
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*��ʾ��ֵ*/
			}
			else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
			{ /*�����Ű���������ʱ�䳬������ʱ��*/
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
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*��ʾ��ֵ*/
			}
			//					else
			//					{
			//						UpButton.Effect = PressShort;
			//						SMG_DisplayModeONE_Detect_AREA_HI(timeflag,HI,ADC_Display); /*������ʾHI�뷧ֵ*/
			//					}
			/*Down Button*/
			else if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
			{
				DownButton.PressCounter = 0;
				HI = HI - 1;
				if (HI <= 0)
					HI = 0;
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*��ʾ��ֵ*/
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
				SMG_DisplayModeONE_Detect_AREA_HI(1, HI, ADC_Display); /*��ʾ��ֵ*/
			}
			else
			{
				DownButton.Effect = PressShort;
				SMG_DisplayModeONE_Detect_AREA_HI(timeflag, HI, ADC_Display); /*������ʾHI�뷧ֵ*/
			}
			if (LastHIValue != HI && DownButton.Status == Release && UpButton.Status == Release)
			{
				WriteFlash(HI_FLASH_DATA_ADDRESS,HI);
			}
		}
	}

	/*LO display mode*/
	else if (DisplayModeNo == 1)
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
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*��ʾ��ֵ*/
			}
			else if (UpButton.Status == Press && (UpButton.Effect == PressLong))
			{ /*�����Ű���������ʱ�䳬������ʱ��*/
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
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*��ʾ��ֵ*/
			}
			//					else
			//					{
			//						UpButton.Effect = PressShort;
			//						SMG_DisplayModeONE_Detect_AREA_LO(timeflag,LO,ADC_Display);/*������ʾLO�뷧ֵ*/
			//					}
			/*Down Button*/
			else if (DownButton.PressCounter != lastCounter && DownButton.Effect == PressShort)
			{
				DownButton.PressCounter = 0;
				LO = LO - 1;
				if (LO <= 0)
					LO = 0;
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*��ʾ��ֵ*/
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
				SMG_DisplayModeONE_Detect_AREA_LO(1, LO, ADC_Display); /*��ʾ��ֵ*/
			}
			else
			{
				DownButton.Effect = PressShort;
				SMG_DisplayModeONE_Detect_AREA_LO(timeflag, LO, ADC_Display); /*������ʾLO�뷧ֵ*/
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
*��ʾģʽ2
*
*******************************/
void DisplayModeTWO(void)
{
	static uint8_t lastCounter;
	/*�������ʾ*/
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
*��ʾģʽ3
*
*******************************/
void DisplayModeTHIRD(void)
{
	/*�������ʾ*/
	SMG_DisplayModeTHIRD(CPV);
	/*����Ϊ���������������ֹ��Ӱ�쵽��ʾģʽ4*/
	DownButton.PressCounter = 0;
	UpButton.PressCounter = 0;
}

/*******************************
*
*��ʾģʽ4
*
*******************************/
void DisplayModeFour(void)
{
	DEL_Set();
}

/*******************************
*
*OUT1_DEL Ӧ��ֵ����
*
*******************************/
void DEL_Set(void)
{
	static uint8_t lastCounter;
	uint16_t LastDEL;

	/*��ʾSHOT,��˸*/
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
	{ /*�����Ű���������ʱ�䳬������ʱ��*/
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
	{ /*�����Ű���������ʱ�䳬������ʱ��*/
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
*�ж�OUT1�����״̬
*
*******************************/
uint8_t SHOTflag = 0;
uint8_t CPV_Status=0;

void SetOUT1Status(void)
{
	if (ShortCircuit != 1) /*���Ƕ�·����������²��ж�OUT1�����*/
	{
		/*ͬ������*/
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
//				if (CPV >= CSV) /*����������ﵽԤ���趨��CSV�����㣬OUT2���һ���ߵ�ƽ*/
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
*�ж�OUT2�����״̬
*
*******************************/
void SetOUT2Status(void)
{
	if (ShortCircuit != 1) /*���Ƕ�·����������²��ж�OUT2�����*/
	{
		if (OUT2)
		{
			//GPIO_WriteBit(OUT2_GPIO_Port, OUT2_Pin, Bit_SET); /*����*/
		}
		if (OUT2_TimerCounter >= 80)
		{
			OUT2 = 0;
			OUT2_TimerCounter = 0;								/*��ȡ��ǰʱ��*/
			//WriteGPIO_Pin_State(OUT2_GPIO_Port, OUT2_Pin, Bit_RESET); /*80ms������*/
		}
	}
}

/*******************************
*
*�ж�OUT3�����״̬
*
*******************************/
void SetOUT3Status(void)
{
	if (ShortCircuit != 1) /*���Ƕ�·����������²��ж�OUT2�����*/
	{
		if (OUT3)
		{
			//WriteGPIO_Pin_State(OUT3_GPIO_Port,OUT3_Pin,Bit_SET);/*����*/
		}
		if (OUT3_TimerCounter >= 160)
		{
			OUT3 = 0;
			OUT3_TimerCounter = 0; /*��ȡ��ǰʱ��*/
								   //GPIO_WriteBit(OUT3_GPIO_Port,OUT3_Pin,Bit_RESET);/*80ms������*/
		}
	}
}

/*******************************
*
*��·����
*
*******************************/
void ShortCircuitProtection(void)
{
//	uint8_t SCState;

//	/*��ȡSC���ŵ�״̬*/
//	if (ShortCircuit != 1)
//	{
//		//SCState = GPIO_ReadInputDataBit(SC_GPIO_Port ,SC_Pin);
//		if ((BitAction)SCState == Bit_RESET)
//		{
//			/*����FB_SC*/
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
//		//GPIO_WriteBit(OUT2_GPIO_Port, OUT2_Pin, Bit_RESET); /*��������OUT*/
//		//GPIO_WriteBit(OUT3_GPIO_Port,OUT3_Pin,Bit_RESET);/*��������OUT*/
//		ShortCircuitTimer = ShortCircuitLastTime;
//	}
}

/*******************************
*
*��������
*
*******************************/
void ButtonMapping(void)
{
	/*��������*/
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
	/*�����ʼ��*/
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
	/*����������*/
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

	/*��
		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us

		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us

		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
	*/
	for (i = 0; i < ms * 100; i++)
		;
}
/*******************************
*
*��ȡEEPROM����
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
*��ʼ�����в���
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
