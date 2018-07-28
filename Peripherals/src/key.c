///**
//  ********************************  STM32F0x1  *********************************
//  * @文件名     ： key.c
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

#include "key.h"

Button_STATUS KEY = ULOC;

//uint32_t key_counter;
ButtonStruct SetButton;
ButtonStruct ModeButton;
ButtonStruct UpButton;
ButtonStruct DownButton;

Button_Status ReadButtonStatus(ButtonStruct *Button);
void PressCallback(ButtonStruct* Button);

void Button_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);   
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);  

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;      
		
	GPIO_InitStructure.GPIO_Pin = SetButton.ButtonPin; 
	GPIO_Init(SetButton.ButtonPort, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = UpButton.ButtonPin; 
	GPIO_Init(UpButton.ButtonPort, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DownButton.ButtonPin; 
	GPIO_Init(DownButton.ButtonPort, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ModeButton.ButtonPin; 
	GPIO_Init(ModeButton.ButtonPort, &GPIO_InitStructure);
	
	//GPIO_Init_structure.GPIO_Pin = BUTTON_SWITCH_Pin; 
	//GPIO_Init(BUTTON_SWITCH_GPIO_Port, &GPIO_Init_structure);	
		
}

void Button_Init(void)
{
	SetButton.ButtonPort = BUTTON_SET_GPIO_Port;
	SetButton.ButtonPin = BUTTON_SET_Pin;
	SetButton.Mode = ShortAndLong;
	SetButton.PressCounter = 0;
	SetButton.PressTimer = 0;
	SetButton.Status = Release;
	SetButton.WorkIn = WorkLow;
	SetButton.Effect = PressNOEffect;
	SetButton.ShortTime = 2*timer_period;
	SetButton.LongTime = 5*timer_period;   
 
	ModeButton.ButtonPort = BUTTON_MODE_GPIO_Port;
	ModeButton.ButtonPin = BUTTON_MODE_Pin;
	ModeButton.Mode = ShortAndLong;
	ModeButton.PressCounter = 0;
	ModeButton.PressTimer = 0;
	ModeButton.Status = Release;
	ModeButton.WorkIn = WorkLow;
	ModeButton.Effect = PressNOEffect;
	ModeButton.ShortTime = 2*timer_period;  
	ModeButton.LongTime = 10*timer_period;		
	
	UpButton.ButtonPort = BUTTON_UP_GPIO_Port;
	UpButton.ButtonPin = BUTTON_UP_Pin;
	UpButton.Mode = ShortAndLong;
	UpButton.PressCounter = 0;
	UpButton.PressTimer = 0;
	UpButton.Status = Release;
	UpButton.WorkIn = WorkLow;
	UpButton.Effect = PressNOEffect;
	UpButton.ShortTime = 2*timer_period;
	UpButton.LongTime = 10*timer_period;
	
	DownButton.ButtonPort = BUTTON_DOWN_GPIO_Port;
	DownButton.ButtonPin = BUTTON_DOWN_Pin;
	DownButton.Mode = ShortAndLong;
	DownButton.PressCounter = 0;
	DownButton.PressTimer = 0;
	DownButton.Status = Release;
	DownButton.WorkIn = WorkLow;
	DownButton.Effect = PressNOEffect;
	DownButton.ShortTime = 2*timer_period;
	DownButton.LongTime = 10*timer_period;
	
	
	Button_GPIO_Init();
	
}

void PressCallback(ButtonStruct* Button)
{	
	if(Button->Mode == ShortAndLong)		//长短模式，根据时间判断长按短按
		{
			if(Button->PressTimer>=Button->LongTime) //按键按下时长对比
			{
				Button->Effect = PressLong;  
				if(Button->Status==Release)
				{
					Button->PressTimer = 0; 
					Button->PressCounter++;				//记录按键被按下次数
				}
			}
			else// if((Button->PressTimer)<(Button->ShortTime)) 
			{
				Button->Effect = PressShort;       
				Button->PressTimer = 0; 
				Button->PressCounter++;				//记录按键被按下次数
			}
		}
		else 
		{	
				if(Button->Mode == Shortpress)
				{
						Button->Effect = PressShort;       //短按模式
						Button->PressTimer = 0; 
						Button->PressCounter++;				//记录按键被按下次数
				}
				else if(Button->Mode == Longpress)		//长按模式
				{
					if(Button->PressTimer>=Button->LongTime) //判断长按时间
					{
						Button->Effect = PressLong;       
						Button->PressTimer = 0; 
						Button->PressCounter++;				//记录按键被按下次数
					} 
				}
		}			 
}


/*按键扫描*/  
void Key_Scan(void)  
{
			/*MODE BUTTON*/
		if(ReadButtonStatus(&ModeButton) == Press )     //UP键按下，一直计算按下时长,根据定时器周期性，计算时长									
    {
				ModeButton.PressTimer++;
				ModeButton.Status = Press;
    } 
		else if(ReadButtonStatus(&ModeButton) == Release)
		{
			ModeButton.Status = Release;
		}
		if(ModeButton.PressTimer>0 && ReadButtonStatus(&ModeButton) == Release)  //按键释放之后再判断按下的时间长度
		{
			PressCallback(&ModeButton);
		}
		else if(ModeButton.PressTimer>ModeButton.LongTime && ReadButtonStatus(&ModeButton) == Press) /*长安，还在按下状态*/
		{
			PressCallback(&ModeButton);
		}
		
		
		/*SET BUTTON*/
		if(ReadButtonStatus(&SetButton) == Press )     //UP键按下，一直计算按下时长,根据定时器周期性，计算时长									
    {
				SetButton.PressTimer++;
				SetButton.Status = Press;
    } 
		else if(ReadButtonStatus(&SetButton) == Release)
		{
			SetButton.Status = Release;
		}
		if(SetButton.PressTimer>0 && ReadButtonStatus(&SetButton) == Release)  //按键释放之后再判断按下的时间长度
		{
			PressCallback(&SetButton);
		}
		else if(SetButton.PressTimer>SetButton.LongTime && ReadButtonStatus(&SetButton)== Press) /*长安，还在按下状态*/
		{
			PressCallback(&SetButton);
		}
		
		/*UP BUTTON*/
		if(ReadButtonStatus(&UpButton) == Press )     //UP键按下，一直计算按下时长,根据定时器周期性，计算时长									
    {
				UpButton.PressTimer++;
				UpButton.Status = Press;
    } 
		else if(ReadButtonStatus(&UpButton) == Release)
		{
			UpButton.Status = Release;
		}
		if(UpButton.PressTimer>0 && ReadButtonStatus(&UpButton) == Release)  //按键释放之后再判断按下的时间长度
		{
			PressCallback(&UpButton);
		}
		else if(UpButton.PressTimer>UpButton.LongTime &&  ReadButtonStatus(&UpButton) == Press) /*长安，还在按下状态*/
		{
			PressCallback(&UpButton);
		}
		/*DOWN BUTTON*/
		if(ReadButtonStatus(&DownButton) == Press )     //DOWN键按下，一直计算按下时长,根据定时器周期性，计算时长									
    {
				DownButton.PressTimer++;
				DownButton.Status = Press;
    } 
		else if(ReadButtonStatus(&DownButton) == Release)
		{
			DownButton.Status = Release;
		}
		if(DownButton.PressTimer>0 &&  ReadButtonStatus(&DownButton) == Release)  //按键释放之后再判断按下的时间长度
		{
			PressCallback(&DownButton);
		}
		else if(DownButton.PressTimer>DownButton.LongTime && ReadButtonStatus(&DownButton)== Press) /*长安，还在按下状态*/
		{
			PressCallback(&DownButton);
		}
}  

Button_Status ReadButtonStatus(ButtonStruct *Button)
{
	uint8_t PinState=0;
	PinState = ReadGPIO_Pin_State(Button->ButtonPort ,Button->ButtonPin);
	if(Button->WorkIn == WorkLow )
	{
		if(PinState==(uint8_t)IO_Bit_RESET)
			return Press;
		else
			return Release;
	}
	if(Button->WorkIn == WorkHigh )
	{
		if(PinState==(uint8_t)IO_Bit_SET)
			return Press;
		else
			return Release;
	}
}
