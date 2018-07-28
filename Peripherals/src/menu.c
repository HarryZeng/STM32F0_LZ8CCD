///**
//  ********************************  STM32F0x1  *********************************
//  * @文件名     ： menu.c
//  * @作者       ： HarryZeng
//  * @库版本     ： V1.5.0
//  * @文件版本   ： V1.0.0
//  * @日期       ： 2017年05月15日
//  * @摘要       ： 数据处理
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  更新日志:
//  2017-05-15 V1.0.0:初始版本
//  ----------------------------------------------------------------------------*/
///* 包含的头文件 --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "menu.h"


extern uint16_t DEL;

int32_t SV = 900; 		/*接近final Value*/
int16_t ATT100=100;
int8_t PERCENTAGE=1;
int8_t DSC=1;
int8_t P_mode=0;
uint8_t EventFlag = 0x00;
uint32_t tempPress = 0;
uint8_t displayModeONE_FLAG = 0;


#define TimerDisplayIndex   4

OUT1_DELAY_MODE_STRUCT OUT1_Mode={TOFF,10};
int8_t DispalyNo=0;
/*CSV菜单*/
void MenuOne_P_mode(void);
/*DSC  菜单*/
void Menu_DSC(void);
/*ATT100设定菜单*/
void MenuOne_ATT100(void);
/*PERCENTAGE设定菜单*/
void Menu_PERCENTAGE(void);
/*FSV COUNTER设定菜单*/
void MenuOne_FSV(void);
void MenuTwo_DEL(void);
void MenuOne_SV(void);
void MenuTwo_OUT1_DelaySET(void);
void MenuTwo_OUT1_TOFF(void);
void MenuTwo_OUT1_OFFD(void);
void MenuTwo_OUT1_ON_D(void);	
void MenuTwo_OUT1_SHOT(void);

//extern uint8_t DX_Flag;

//extern uint8_t 	FX_Flag;


void SET_SI_Mode(int8_t P_mode)
{
	if(P_mode==0)
	{
		TIM3_init(280,11,31);
	}
	else if(P_mode==1)
	{
		TIM3_init(800,11,31);
	}
	else if(P_mode==2)
	{
		TIM3_init(1600,11,31);
	}
	else if(P_mode==3)
	{
		TIM3_init(6400,11,31);
	}
}

void menu(void)
{
	static uint8_t lastCounter;
	/*Mode按键第一次按下,超过长按时间*/
	if((DownButton.Status==Press && ModeButton.Status ==Press )|| SetButton.Status == Press||UpButton.Status==Press)
	{
		
	}
	else
	{
		while(((ModeButton.Status==Press&&(ModeButton.PressTimer>=ModeButton.LongTime)) || (ModeButton.Effect==PressLong)))//&&DownButton.Status==Release)
		{
//				DX_Flag = 0;
//				DX = 0;
//				S1024 = 0;
				ModeButton.PressCounter = 0;
				UpButton.PressCounter = 0;
				MenuOne_P_mode();
				   
				while(ModeButton.PressCounter==1)
				{
					MenuOne_P_mode();
				}	
				SET_SI_Mode(P_mode);
//				
//				while(ModeButton.PressCounter==2)
//				{
//					//MenuOne_CSV();
////					Menu_PERCENTAGE();
//				}
//				
//				while(ModeButton.PressCounter==3)
//				{
//					Menu_DSC();
//				}
//				
				while(ModeButton.PressCounter==2)
				{
					/*DETECT*//*数码管显示*/
					SMG_DisplayModeDETECT(displayModeONE_FLAG);
					/*******************************/
					/*Up Button*/
					if((UpButton.PressCounter !=lastCounter)&&(UpButton.Effect==PressShort))
					{
						//lastCounter = UpButton.PressCounter;
						UpButton.PressCounter = 0;
						if(displayModeONE_FLAG==0)
							displayModeONE_FLAG = 1;
						else 
							displayModeONE_FLAG=0;
						WriteFlash(DETECT_FLASH_DATA_ADDRESS,displayModeONE_FLAG);
						//FX_Flag = 0;    //重新选择菜单后，就不能使用FX，需要重新自学习，才可以启动FX
					}

					/*Down Button*/
					else if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
					{
						//lastCounter = DownButton.PressCounter;
						DownButton.PressCounter = 0;
						if(displayModeONE_FLAG==0)
							displayModeONE_FLAG = 1;
						else 
							displayModeONE_FLAG=0;
						WriteFlash(DETECT_FLASH_DATA_ADDRESS,displayModeONE_FLAG);
						//FX_Flag = 0;    //重新选择菜单后，就不能使用FX，需要重新自学习，才可以启动FX
					}
				}
//				
//				
//				while(ModeButton.PressCounter==5)
//				{
//					/*SV COUNTER设定菜单*/
//					MenuOne_SV();
//				}
//				
//				while(ModeButton.PressCounter==6)
//				{
//					/*FSV COUNTER设定菜单*/
//					MenuOne_FSV();
//				}
//				
				/*显示先前定时器选定菜单*/
				if(ModeButton.PressCounter==3 && ModeButton.Effect==PressShort)
				{
					if(OUT1_Mode.DelayMode == TOFF)
						DispalyNo = 0;
					else if(OUT1_Mode.DelayMode == OFFD)
						DispalyNo = 1;
//					else if(OUT1_Mode.DelayMode == ON_D)
//						DispalyNo = 2;
//					else if(OUT1_Mode.DelayMode == SHOT)
//						DispalyNo = 3;
				}
				while(ModeButton.Effect==PressShort && ModeButton.PressCounter==3)
				{
						MenuTwo_OUT1_DelaySET();
				}
				while(ModeButton.Effect==PressShort && ModeButton.PressCounter==5)
				{
						END_Display();
						//DX_Flag = 1;
						/*再短按MODE，则退出菜单*/
						if(ModeButton.Effect==PressShort && ModeButton.PressCounter>=6) 
						{
							ModeButton.PressCounter = 0;
							ModeButton.Status = Release;
							WriteFlash(OUT1_Mode_FLASH_DATA_ADDRESS,OUT1_Mode.DelayMode);
							WriteFlash(OUT1_Value_FLASH_DATA_ADDRESS,OUT1_Mode.DelayValue);
							break;
						}
				}
		}
	}
}
/*CSV设定菜单*/
void MenuOne_P_mode(void)
{
	static uint8_t lastCounter;
	uint8_t Flashflag=0;
	
	SMG_DisplaCSV(P_mode);
	/*Up Button*/
	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
	{
		lastCounter = UpButton.PressCounter;
		UpButton.PressCounter = 0;
		P_mode = P_mode+1;
		Flashflag = 1;
	}
	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
	{				/*还按着按键，并且时间超过长按时间*/
		UpButton.PressCounter = 0;
		if(UpButton.PressTimer<KEY_LEVEL_1)
		{
			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode+1;
				Flashflag = 1;
			}
		}
		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
		{
			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode+1;
				Flashflag = 1;
			}
		}
		else 
		{
			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode+1;
				Flashflag = 1;
			}
		}
	}	
	else
	{
		UpButton.Effect = PressShort;
	}
	
	/*Down Button*/
	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
	{
		DownButton.PressCounter = 0;
		P_mode = P_mode-1;
		Flashflag = 1;
	}
	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
	{				/*还按着按键，并且时间超过长按时间*/
		DownButton.PressCounter = 0;
		if(DownButton.PressTimer<KEY_LEVEL_1)
		{
			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode-1;
				Flashflag = 1;
			}
		}
		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
		{
			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode-1;
				Flashflag = 1;
			}
		}
		else 
		{
			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
			{
				tempPress = 0;
				P_mode = P_mode-1;
				Flashflag = 1;
			}
		}
	}
	else
	{
		DownButton.Effect = PressShort;
	}
	
	if(P_mode<0)
			P_mode =3;
	else if(P_mode>3)
			P_mode =0;
	
		if(EventFlag&Blink500msFlag && Flashflag==1) 
		{
			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
			//WriteFlash(CSV_FLASH_DATA_ADDRESS,P_mode);
		}
		
}

/*ATT100设定菜单*/
extern uint32_t ADC_Display;//ADC显示
void MenuOne_ATT100(void)
{
//	static uint8_t lastCounter;
//	uint8_t Flashflag=0;
//	
//	SMG_DisplayATT100(ATT100,ADC_Display);
//	
//	/*Up Button*/
//	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//	{
//		lastCounter = UpButton.PressCounter;
//		UpButton.PressCounter = 0;
//		ATT100 = ATT100+1;
//		Flashflag = 1;
//	}
//	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		UpButton.PressCounter = 0;
//		if(UpButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100+1;
//				Flashflag = 1;
//			}
//		}
//		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100+2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100+5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		UpButton.Effect = PressShort;
//	}
//	
//	/*Down Button*/
//	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//	{
//		DownButton.PressCounter = 0;
//		ATT100 = ATT100-1;
//		Flashflag = 1;
//	}
//	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		DownButton.PressCounter = 0;
//		if(DownButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100-1;
//				Flashflag = 1;
//			}
//		}
//		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100-2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				ATT100 = ATT100-5;
//				Flashflag = 1;
//			}
//		}
//	}
//	else
//	{
//		DownButton.Effect = PressShort;
//	}
//	
//	if(ATT100<=1)
//			ATT100 =1;
//	else if(ATT100>=100)
//			ATT100 =100;
//	
//		if(EventFlag&Blink500msFlag && Flashflag==1) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			//WriteFlash(ATT100_FLASH_DATA_ADDRESS,ATT100);
//		}
//		
//		//ATTSet(ATT100);/*设置ATT的输出*/
	
}


void Menu_PERCENTAGE(void)
{
//	static uint8_t lastCounter;
//	uint8_t Flashflag=0;
//	
//	
//	
//	/*Up Button*/
//	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//	{
//		lastCounter = UpButton.PressCounter;
//		UpButton.PressCounter = 0;
//		PERCENTAGE = PERCENTAGE+1;
//		Flashflag = 1;
//	}
//	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		UpButton.PressCounter = 0;
//		if(UpButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE+1;
//				Flashflag = 1;
//			}
//		}
//		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE+2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE+5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		UpButton.Effect = PressShort;
//	}
//	
//	/*Down Button*/
//	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//	{
//		DownButton.PressCounter = 0;
//		PERCENTAGE = PERCENTAGE-1;
//		Flashflag = 1;
//	}
//	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		DownButton.PressCounter = 0;
//		if(DownButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE-1;
//				Flashflag = 1;
//			}
//		}
//		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE-2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				PERCENTAGE = PERCENTAGE-5;
//				Flashflag = 1;
//			}
//		}
//	}
//	else
//	{
//		DownButton.Effect = PressShort;
//	}
//	
//	if(PERCENTAGE<=0)
//			PERCENTAGE =0;
//	else if(PERCENTAGE>=50)
//			PERCENTAGE =50;
//	SMG_DisplayPERCENTAGE(PERCENTAGE); //显示
//		if(EventFlag&Blink500msFlag && Flashflag==1) 
//		{
//			//WriteFlash(PERCENTAGE_FLASH_DATA_ADDRESS,PERCENTAGE);
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//		}
}

/*******************************
*
*菜单显示 DSC
*
*******************************/
void Menu_DSC(void)
{
//	static uint8_t lastCounter;
//		/*数码管显示*/
//		SMG_DisplayMenuDSC(DSC);
//	
//		/*Up Button*/
//		if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//		{
//			lastCounter = UpButton.PressCounter;
//			UpButton.PressCounter = 0;
//			if(DSC==0)
//				DSC = 1;
//			else 
//				DSC=0;
//			WriteFlash(DSC_FLASH_DATA_ADDRESS,DSC);
//		}

//		/*Down Button*/
//		if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//		{
//			DownButton.PressCounter = 0;
//			if(DSC==0)
//				DSC = 1;
//			else 
//				DSC=0;
//			WriteFlash(DSC_FLASH_DATA_ADDRESS,DSC);
//		}
//}



///*SV COUNTER设定菜单*/
//void MenuOne_SV(void)
//{
//	static uint8_t lastCounter;
//	uint8_t Flashflag=0;
//	SMG_DisplaSV(SV);
//	
//	/*Up Button*/
//	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//	{
//		lastCounter = UpButton.PressCounter;
//		UpButton.PressCounter = 0;
//		SV = SV+1;
//		Flashflag = 1;
//	}
//	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		UpButton.PressCounter = 0;
//		if(UpButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV+1;
//				Flashflag = 1;
//			}
//		}
//		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV+2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV+5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		UpButton.Effect = PressShort;
//	}
//	
//	/*Down Button*/
//	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//	{
//		DownButton.PressCounter = 0;
//		SV = SV-1;
//		Flashflag = 1;
//	}
//	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		DownButton.PressCounter = 0;
//		if(DownButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV-1;
//				Flashflag = 1;
//			}
//		}
//		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV-2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				SV = SV-5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		DownButton.Effect = PressShort;
//	}
//	
//	if(SV<=1)
//			SV =1;
//	else if(SV>=65535)
//			SV =65535;
//	
//		if(EventFlag&Blink500msFlag && Flashflag==1) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			//WriteFlash(SV_FLASH_DATA_ADDRESS,SV);
//		}
}


/*FSV COUNTER设定菜单*/
void MenuOne_FSV(void)
{
//	static uint8_t lastCounter;
//	uint8_t Flashflag=0;
//	SMG_DisplayFSV(FSV);
//	
//	/*Up Button*/
//	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//	{
//		lastCounter = UpButton.PressCounter;
//		UpButton.PressCounter = 0;
//		FSV = FSV+1;
//		Flashflag = 1;
//	}
//	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		UpButton.PressCounter = 0;
//		if(UpButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV+1;
//				Flashflag = 1;
//			}
//		}
//		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV+2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV+5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		UpButton.Effect = PressShort;
//	}
//	
//	/*Down Button*/
//	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//	{
//		DownButton.PressCounter = 0;
//		FSV = FSV-1;
//		Flashflag = 1;
//	}
//	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		DownButton.PressCounter = 0;
//		if(DownButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV-1;
//				Flashflag = 1;
//			}
//		}
//		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV-2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;	
//				FSV = FSV-5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		DownButton.Effect = PressShort;
//	}
//	
//	if(FSV<=1)
//			FSV =1;
//	else if(FSV>=65535)
//			FSV =65535;
//	
//		if(EventFlag&Blink500msFlag && Flashflag==1) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			//WriteFlash(FSV_FLASH_DATA_ADDRESS,FSV);
//		}
	
}

/*OUT1 DELAY设定菜单*/

void MenuTwo_OUT1_DelaySET(void)
{
		static uint8_t lastCounter;
	
		/*TOFF Mode*/
		while(DispalyNo==0)
		{
			MenuTwo_OUT1_TOFF();
			if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
			{
				lastCounter = UpButton.PressCounter;
				UpButton.PressCounter = 0;
				DispalyNo++;
				if(DispalyNo>1)
					DispalyNo = 0;
			}
			if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
			{
				//lastCounter = DownButton.PressCounter;
				DownButton.PressCounter = 0;
				DispalyNo--;
				if(DispalyNo<0)
					DispalyNo = 1;
			}
			if(ModeButton.PressCounter>=(TimerDisplayIndex)) 
			{
				ModeButton.PressCounter = (TimerDisplayIndex+1); //用于跳到END菜单
				break;
			}
		}
		
		/*OFFD mode*/
		while(DispalyNo==1)
		{
				MenuTwo_OUT1_OFFD();
				if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
				{
					//lastCounter = UpButton.PressCounter;
					UpButton.PressCounter = 0;
					DispalyNo++;
					if(DispalyNo>1)
						DispalyNo = 0;
				}
				if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
				{
					//lastCounter = DownButton.PressCounter;
					DownButton.PressCounter = 0;
					DispalyNo--;
					if(DispalyNo<0)
						DispalyNo = 1;
				}
				if(ModeButton.PressCounter>=(TimerDisplayIndex+1)) break;
		}
//		/*ON_D mode*/
//		while(DispalyNo==2)
//		{
//				MenuTwo_OUT1_ON_D();
//				if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//				{
//					//lastCounter = UpButton.PressCounter;
//					UpButton.PressCounter = 0;
//					DispalyNo++;
//					if(DispalyNo>3)
//						DispalyNo = 0;
//				}
//				if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//				{
//					//lastCounter = DownButton.PressCounter;
//					DownButton.PressCounter = 0;
//					DispalyNo--;
//					if(DispalyNo<0)
//						DispalyNo = 3;
//				}
//				if(ModeButton.PressCounter>=(TimerDisplayIndex+1)) break;
//		}
//		while(DispalyNo==3)
//		{
//				MenuTwo_OUT1_SHOT();
//				if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//				{
//					//lastCounter = UpButton.PressCounter;
//					UpButton.PressCounter = 0;
//					DispalyNo++;
//					if(DispalyNo>3)
//						DispalyNo = 0;
//				}
//				if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//				{
//					//lastCounter = DownButton.PressCounter;
//					DownButton.PressCounter = 0;
//					DispalyNo--;
//					if(DispalyNo<0)
//						DispalyNo = 3;
//				}
//				if(ModeButton.PressCounter>=(TimerDisplayIndex+1)) break;
//		}
		
//		while(DispalyNo==4)
//		{
//				MenuTwo_DEL();
//				if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//				{
//					//lastCounter = UpButton.PressCounter;
//					UpButton.PressCounter = 0;
//					DispalyNo++;
//					if(DispalyNo>4)
//						DispalyNo = 0;
//				}
//				if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//				{
//					//lastCounter = DownButton.PressCounter;
//					DownButton.PressCounter = 0;
//					DispalyNo--;
//					if(DispalyNo<0)
//						DispalyNo = 4;
//				}
//				if(ModeButton.PressCounter>4) break;
//		}

		
}


/*******************************
*
*OUT1_TOFF
*
*******************************/
void MenuTwo_OUT1_TOFF(void)
{
		if(EventFlag&Blink500msFlag) 
		{
			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
			SMG_DisplayMenuTwo_TOFF();
		}
		//if(ModeButton.Effect==PressShort && ModeButton.PressCounter==4)
			OUT1_Mode.DelayMode = TOFF;
}

/*******************************
*
*OUT1_OFFD
*
*******************************/
void MenuTwo_OUT1_OFFD(void)
{
		static uint8_t lastCounter;
		uint8_t Flashflag=0;
		if(EventFlag&Blink500msFlag) 
		{
			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
			/*显示OFFD,闪烁*/
			SMG_DisplayMenuTwo_OFFD();
		}
		/*短按MODE后，进入OFFD的设置子菜单*/
		while(ModeButton.Effect==PressShort && ModeButton.PressCounter==TimerDisplayIndex)
		{
			OUT1_Mode.DelayMode = OFFD;
			/*显示OFFD value*/
			if(UpButton.Status==Release&&DownButton.Status==Release)
			{
				if(EventFlag&Blink500msFlag) 
				{
					EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
					/*显示OFFD,闪烁*/
					SMG_DisplayMenuTwo_OFFD_SET(OUT1_Mode.DelayValue,1);
				}
			}
			else
			{
				EventFlag = EventFlag &(~Blink500msFlag);
				SMG_DisplayMenuTwo_OFFD_SET(OUT1_Mode.DelayValue,0);
			}
			/*Up Button*/
			if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
			{
				lastCounter = UpButton.PressCounter;
				UpButton.PressCounter = 0;
				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
				Flashflag = 1;
			}
			else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
			{				/*还按着按键，并且时间超过长按时间*/
				UpButton.PressCounter = 0;
				if(UpButton.PressTimer<KEY_LEVEL_1)
				{
					if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
				else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
				{
					if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
				else 
				{
					if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
			}	
			else
			{
				UpButton.Effect = PressShort;
			}
				/*Down Button*/
			if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
			{
				DownButton.PressCounter = 0;
				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
				Flashflag = 1;
			}
			else if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
			{				/*还按着按键，并且时间超过长按时间*/
				DownButton.PressCounter = 0;
				if(DownButton.PressTimer<KEY_LEVEL_1)
				{
					if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
				else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
				{
					if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
				else 
				{
					if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
					{
						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
						Flashflag = 1;
						tempPress = 0;
					}
				}
			}	
			else
			{
				DownButton.Effect = PressShort;
			}
			if(OUT1_Mode.DelayValue>=9999)
				OUT1_Mode.DelayValue = 9999;
			else if(OUT1_Mode.DelayValue<=0)
					OUT1_Mode.DelayValue = 0;
			
			if(EventFlag&Blink500msFlag && Flashflag==1) 
			{
				Flashflag = 0;
				EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
				WriteFlash(OUT1_Mode_FLASH_DATA_ADDRESS,OUT1_Mode.DelayMode);
				WriteFlash(OUT1_Value_FLASH_DATA_ADDRESS,OUT1_Mode.DelayValue);
			}
			
		}
}

/*******************************
*
*OUT1_ON_D
*
*******************************/
void MenuTwo_OUT1_ON_D(void)
{
//		static uint8_t lastCounter;
//		uint8_t Flashflag=0;
//		if(EventFlag&Blink500msFlag) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			
//			SMG_DisplayMenuTwo_ON_Delay();
//		}
//		/*短按MODE后，进入ON_D的设置子菜单*/
//		while(ModeButton.Effect==PressShort && ModeButton.PressCounter==TimerDisplayIndex)
//		{
//			OUT1_Mode.DelayMode = ON_D;
//			/*显示ON_D value*/
//			if(UpButton.Status==Release&&DownButton.Status==Release)
//			{
//				if(EventFlag&Blink500msFlag) 
//				{
//					EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//					/*显示ON_D,闪烁*/
//					SMG_DisplayMenuTwo_ON_Delay_SET(OUT1_Mode.DelayValue,1);
//				}
//			}
//			else
//			{
//				EventFlag = EventFlag &(~Blink100msFlag);
//				SMG_DisplayMenuTwo_ON_Delay_SET(OUT1_Mode.DelayValue,0);
//			}
//			
//			/*Up Button*/
//			if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//			{
//				lastCounter = UpButton.PressCounter;
//				UpButton.PressCounter = 0;
//				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//				Flashflag = 1;
//			}
//			else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//			{				/*还按着按键，并且时间超过长按时间*/
//				UpButton.PressCounter = 0;
//				if(UpButton.PressTimer<KEY_LEVEL_1)
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else 
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//			}	
//			else
//			{
//				UpButton.Effect = PressShort;
//			}	
//				/*Down Button*/
//			if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//			{
//				DownButton.PressCounter = 0;
//				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//				Flashflag = 1;
//			}
//			else if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//			{				/*还按着按键，并且时间超过长按时间*/
//				DownButton.PressCounter = 0;
//				if(DownButton.PressTimer<KEY_LEVEL_1)
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else 
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//			}	
//			else
//			{
//				DownButton.Effect = PressShort;
//			}
//			
//			if(OUT1_Mode.DelayValue>=9999)
//				OUT1_Mode.DelayValue = 9999;
//			else if(OUT1_Mode.DelayValue<=0)
//					OUT1_Mode.DelayValue = 0;
//			if(EventFlag&Blink500msFlag && Flashflag==1) 
//			{
//				Flashflag = 0;
//				EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//				WriteFlash(OUT1_Mode_FLASH_DATA_ADDRESS,OUT1_Mode.DelayMode);
//				WriteFlash(OUT1_Value_FLASH_DATA_ADDRESS,OUT1_Mode.DelayValue);
//			}
//		}
}


/*******************************
*
*OUT1_SHOT
*
*******************************/
void MenuTwo_OUT1_SHOT(void)
{
//		static uint8_t lastCounter;
//		uint8_t Flashflag=0;
//		if(EventFlag&Blink500msFlag) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			
//			SMG_DisplayMenuTwo_SHOT();
//		}
//		/*短按MODE后，进入SHOT的设置子菜单*/
//		while(ModeButton.Effect==PressShort && ModeButton.PressCounter==TimerDisplayIndex)
//		{
//			OUT1_Mode.DelayMode = SHOT;
//			/*显示SHOT value*/			
//			if(UpButton.Status==Release&&DownButton.Status==Release)
//			{
//				if(EventFlag&Blink500msFlag) 
//				{
//					EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//					/*显示SHOT,闪烁*/
//					SMG_DisplayMenuTwo_SHOT_SET(OUT1_Mode.DelayValue,1);
//				}
//			}
//			else
//			{
//				EventFlag = EventFlag &(~Blink500msFlag);
//				SMG_DisplayMenuTwo_SHOT_SET(OUT1_Mode.DelayValue,0);
//			}
//			
//			/*Up Button*/
//			if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//			{
//				lastCounter = UpButton.PressCounter;
//				UpButton.PressCounter = 0;
//				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//				Flashflag = 1;
//			}
//			else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//			{				/*还按着按键，并且时间超过长按时间*/
//				UpButton.PressCounter = 0;
//				if(UpButton.PressTimer<KEY_LEVEL_1)
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else 
//				{
//					if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue+1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//			}	
//			else
//			{
//				UpButton.Effect = PressShort;
//			}	
//				/*Down Button*/
//			if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//			{
//				DownButton.PressCounter = 0;
//				OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//				Flashflag = 1;
//			}
//			else if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//			{				/*还按着按键，并且时间超过长按时间*/
//				DownButton.PressCounter = 0;
//				if(DownButton.PressTimer<KEY_LEVEL_1)
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//				else 
//				{
//					if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//					{
//						OUT1_Mode.DelayValue = OUT1_Mode.DelayValue-1;
//						Flashflag = 1;
//						tempPress = 0;
//					}
//				}
//			}	
//			else
//			{
//				DownButton.Effect = PressShort;
//			}
//			
//			if(OUT1_Mode.DelayValue>=9999)
//				OUT1_Mode.DelayValue = 9999;
//			else if(OUT1_Mode.DelayValue<=0)
//					OUT1_Mode.DelayValue = 0;
//			if(EventFlag&Blink500msFlag && Flashflag==1) 
//			{
//				Flashflag = 0;
//				EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//				WriteFlash(OUT1_Mode_FLASH_DATA_ADDRESS,OUT1_Mode.DelayMode);
//				WriteFlash(OUT1_Value_FLASH_DATA_ADDRESS,OUT1_Mode.DelayValue);
//			}
//		}
}



/*******************************
*
*OUT1_DEL 应差值设置
*
*******************************/
void MenuTwo_DEL(void)
{
//		static uint8_t lastCounter;
//	uint8_t Flashflag=0;
//			SMG_DisplayMenuTwo_DEL_SET(DEL,0);
//			
//	/*Up Button*/
//	if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
//	{
//		lastCounter = UpButton.PressCounter;
//		UpButton.PressCounter = 0;
//		DEL = DEL+1;
//		Flashflag = 1;
//	}
//	else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		UpButton.PressCounter = 0;
//		if(UpButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL+1;
//				Flashflag = 1;
//			}
//		}
//		else if(UpButton.PressTimer>KEY_LEVEL_1&&UpButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL+2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(UpButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL+5;
//				Flashflag = 1;
//			}
//		}
//	}	
//	else
//	{
//		UpButton.Effect = PressShort;
//	}
//	
//	/*Down Button*/
//	if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
//	{
//		DownButton.PressCounter = 0;
//		DEL = DEL-1;
//		Flashflag = 1;
//	}
//	else 	if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
//	{				/*还按着按键，并且时间超过长按时间*/
//		DownButton.PressCounter = 0;
//		if(DownButton.PressTimer<KEY_LEVEL_1)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_1_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL-1;
//				Flashflag = 1;
//			}
//		}
//		else if(DownButton.PressTimer>KEY_LEVEL_1&&DownButton.PressTimer<KEY_LEVEL_2)
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_2_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL-2;
//				Flashflag = 1;
//			}
//		}
//		else 
//		{
//			if(DownButton.PressTimer%KEY_LEVEL_3_SET==0&&tempPress == 1)
//			{
//				tempPress = 0;
//				DEL = DEL-5;
//				Flashflag = 1;
//			}
//		}
//	}
//	else
//	{
//		DownButton.Effect = PressShort;
//	}
//	
//	if(DEL<=50)
//			DEL =50;
//	else if(DEL>=3000)
//			DEL =3000;
//	
//		if(EventFlag&Blink500msFlag && Flashflag==1) 
//		{
//			EventFlag = EventFlag &(~Blink500msFlag);  //清楚标志位
//			WriteFlash(DEL_FLASH_DATA_ADDRESS,DEL);
//		}
}



