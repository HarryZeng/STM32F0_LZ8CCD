#include "bsp_init.h"
#include "arch.h"

int16_t adc_dma_tab[DMA_BUFFER_SIZE];  
RCC_ClocksTypeDef SysClock;


void RCC_Configuration(void)
{
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
	{
		
	}
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(RCC_GetSYSCLKSource()!=0x08)
	{
	}
}

/*******************************************
ÊýÂëGPIO³õÊ¼»¯
********************************************/
void SMG_GPIO_INIT(void)
{
	
	   GPIO_InitTypeDef GPIO_InitStructure;  
    //??GPIO??  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);   
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);  
		
	
    GPIO_StructInit(&GPIO_InitStructure);  
	
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //PB3,PB4,PA15£¬×÷ÎªÆÕÍ¨IOÊ¹ÓÃ
		//GPIO_PinRemapConfig( GPIO_Remap_PD01 , ENABLE );

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

	
    GPIO_InitStructure.GPIO_Pin = D4_Pin;  
    GPIO_Init(D4_GPIO_Port, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = D3_Pin;
		GPIO_Init(D3_GPIO_Port, &GPIO_InitStructure);  
		GPIO_InitStructure.GPIO_Pin = D2_Pin;
		GPIO_Init(D2_GPIO_Port, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = D1_Pin;
		GPIO_Init(D1_GPIO_Port, &GPIO_InitStructure); 
	  //GPIOD5~7                                                       
    GPIO_InitStructure.GPIO_Pin = D5_Pin;                            
    GPIO_Init(D5_GPIO_Port, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = D6_Pin;  		
		GPIO_Init(D6_GPIO_Port, &GPIO_InitStructure);  
		GPIO_InitStructure.GPIO_Pin = D7_Pin;  
		GPIO_Init(D7_GPIO_Port, &GPIO_InitStructure);  
		//GPIOA                                                        
    GPIO_InitStructure.GPIO_Pin = D8_Pin;	
    GPIO_Init(D8_GPIO_Port, &GPIO_InitStructure);  
		GPIO_InitStructure.GPIO_Pin = D9_Pin;  
		GPIO_Init(D9_GPIO_Port, &GPIO_InitStructure);  

		//GPIOB
	  GPIO_InitStructure.GPIO_Pin = A_Pin;             
		GPIO_Init(A_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = B_Pin; 
		GPIO_Init(B_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = C_Pin; 
		GPIO_Init(C_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = D_Pin; 
		GPIO_Init(D_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = E_Pin; 
		GPIO_Init(E_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = F_Pin; 
		GPIO_Init(F_GPIO_Port, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = G_Pin; 
		GPIO_Init(G_GPIO_Port, &GPIO_InitStructure); 
		
		
		GPIO_WriteBit(D1_GPIO_Port, D1_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D2_GPIO_Port, D2_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D3_GPIO_Port, D3_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D4_GPIO_Port, D4_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D5_GPIO_Port, D5_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D6_GPIO_Port, D6_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D7_GPIO_Port, D7_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D8_GPIO_Port, D8_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D9_GPIO_Port, D9_Pin, IO_Bit_RESET);

		GPIO_WriteBit(A_GPIO_Port, A_Pin, IO_Bit_RESET);
		GPIO_WriteBit(B_GPIO_Port, B_Pin, IO_Bit_RESET);
		GPIO_WriteBit(C_GPIO_Port, C_Pin, IO_Bit_RESET);
		GPIO_WriteBit(D_GPIO_Port, D_Pin, IO_Bit_RESET);
		GPIO_WriteBit(E_GPIO_Port, E_Pin, IO_Bit_RESET);
		GPIO_WriteBit(F_GPIO_Port, F_Pin, IO_Bit_RESET);
		GPIO_WriteBit(G_GPIO_Port, G_Pin, IO_Bit_RESET);

}

void IO_GPIO_INIT(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;  
    //??GPIO??  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);   
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);  
	
    GPIO_StructInit(&GPIO_InitStructure);  
	
		//OUT1_GPIO_Port,OUT2_GPIO_Port
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	  GPIO_InitStructure.GPIO_Pin = OUT1_Pin;                              
		GPIO_Init(OUT1_GPIO_Port, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = Test_IO_Pin;                               
		GPIO_Init(Test_IO_GPIO_Port, &GPIO_InitStructure);

}


//void TIM14_GPIO_Init(void)
//{
//		GPIO_InitTypeDef GPIO_InitStructure;
//		
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  
// 	
//	  GPIO_InitStructure.GPIO_Pin = DIS_Pin;  
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                   //????(??)??  
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //Fast speed  
//    GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_UP;                    //??  
//    GPIO_Init(DIS_GPIO_Port, &GPIO_InitStructure);
//	
//		GPIO_PinAFConfig(DIS_GPIO_Port,GPIO_PinSource4,GPIO_AF_4);	
//}

//void TIM14_PWM_OUT_Init(void)
//{
//		TIM_OCInitTypeDef         TIM_OCInitStructure;
//	
//			/*OCInit Channel 1 Configuration in PWM mode */
//		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                
//		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;         
//		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                                        
//		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                 
//		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;     
//		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 

//		TIM_OCInitStructure.TIM_Pulse = 500;  	//PWM      96->1.5us 
//		TIM_OC1Init(TIM14,&TIM_OCInitStructure);                                                 
//		TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);		
//}

//void TIM14_init(void)  
//{  
//	/*
//	4M/(15+1)/2 =125K
//	*/
//	TIM_TimeBaseInitTypeDef timer_init_structure; 
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE); 
//	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;                //Ê¹ÄÜTIM14ÖÐ¶ÏÍ¨µÀ  
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 10;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
//	NVIC_Init(&NVIC_InitStructure);
//	/*TIM14*/
//	TIM_DeInit(TIM14);                                               //TIM14
//	TIM_TimeBaseStructInit(&timer_init_structure);                  //³õÊ¼»¯TIM½á¹¹Ìå  

//	timer_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;          //ÏµÍ³Ê±ÖÓ,²»·ÖÆµ,24M  
//	timer_init_structure.TIM_CounterMode = TIM_CounterMode_Up;      //ÏòÉÏ¼ÆÊýÄ£Ê½  
//	timer_init_structure.TIM_Period = 47;                          //Ã¿300 uS´¥·¢Ò»´ÎÖÐ¶Ï,??ADC  
//	timer_init_structure.TIM_Prescaler = 1000;                      //¼ÆÊýÊ±ÖÓ·ÖÆµ,f=1M,systick=1 uS  
//	timer_init_structure.TIM_RepetitionCounter = 0x00;              //·¢Éú0+1µÄupdateÊÂ¼þ²úÉúÖÐ¶Ï 
//	
//	TIM14_GPIO_Init();
//	TIM14_PWM_OUT_Init();
//	
//	TIM_SelectInputTrigger(TIM14,TIM_TS_ITR3);									//Ñ¡Ôñ´¥·¢Æô¶¯TIM14
//	TIM_ITRxExternalClockConfig(TIM14,TIM_TS_ITR3);
//	TIM_SelectSlaveMode(TIM14,TIM_SlaveMode_Trigger);
//	
//	TIM_TimeBaseInit(TIM14, &timer_init_structure);  
//	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);                       //Ê¹ÄÜTIM14ÖÐ¶Ï
//	TIM_ARRPreloadConfig(TIM14,ENABLE);
//	
//	TIM_Cmd(TIM14, ENABLE);                                          //Ê¹ÄÜTIM14

//}


void TIM3_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
 	
	  GPIO_InitStructure.GPIO_Pin = SI_Pin;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                   //????(??)??  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //Fast speed  
    GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_UP;                    //??  
    GPIO_Init(SI_GPIO_Port, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(SI_GPIO_Port,GPIO_PinSource1,GPIO_AF_1);
		
}
void TIM3_PWM_OUT_Init(void)
{
		TIM_OCInitTypeDef         TIM_OCInitStructure;
	
			/*OCInit Channel 1 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;         
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                                        
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                 
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;     
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 

		TIM_OCInitStructure.TIM_Pulse = 31;  	//PWM      96->1.5us 
		TIM_OC4Init(TIM3,&TIM_OCInitStructure);                                                 
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);	
		
}

void TIM3_init(void)
{
	
	/*
	4M/(15+1)/2 =125K
	*/
	TIM_TimeBaseInitTypeDef timer_init_structure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                //Ê¹ÄÜTIM3ÖÐ¶ÏÍ¨µÀ  
	NVIC_InitStructure.NVIC_IRQChannelPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
	NVIC_Init(&NVIC_InitStructure);
	/*TIM3*/
	TIM_DeInit(TIM3);                                               //¸´Î»TIM3
	TIM_TimeBaseStructInit(&timer_init_structure);                  //³õÊ¼»¯TIM½á¹¹Ìå  

	timer_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;          //ÏµÍ³Ê±ÖÓ,²»·ÖÆµ,24M  
	timer_init_structure.TIM_CounterMode = TIM_CounterMode_Up;      //ÏòÉÏ¼ÆÊýÄ£Ê½  
	timer_init_structure.TIM_Period = 31;                          //Ã¿300 uS´¥·¢Ò»´ÎÖÐ¶Ï,??ADC  
	timer_init_structure.TIM_Prescaler = 11;                      //¼ÆÊýÊ±ÖÓ·ÖÆµ,f=1M,systick=1 uS  
	timer_init_structure.TIM_RepetitionCounter = 0x00;              //·¢Éú0+1µÄupdateÊÂ¼þ²úÉúÖÐ¶Ï 
	
	TIM3_GPIO_Init();
	TIM3_PWM_OUT_Init();
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_ITR0);									//Ñ¡Ôñ´¥·¢Æô¶¯TIM3
	TIM_ITRxExternalClockConfig(TIM3,TIM_TS_ITR0);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Trigger);
	
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);							//Ñ¡ÔñTIM3µÄtimerÎª´¥·¢Ô´  
	TIM_TimeBaseInit(TIM3, &timer_init_structure);  
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                       //Ê¹ÄÜTIM3ÖÐ¶Ï
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);                                          //Ê¹ÄÜTIM3

}


void TIM2_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  
 	
	  GPIO_InitStructure.GPIO_Pin = PWM_Pin;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                   //????(??)??  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //Fast speed  
    GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_UP;                    //??  
    GPIO_Init(PWM_GPIO_Port, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(PWM_GPIO_Port,GPIO_PinSource5,GPIO_AF_2);
		
}
void TIM2_PWM_OUT_Init(void)
{
		TIM_OCInitTypeDef         TIM_OCInitStructure;
	
			/*OCInit Channel 1 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                                
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;         
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                                        
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                 
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;     
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 

		TIM_OCInitStructure.TIM_Pulse = 10;  	//PWM      96->1.5us 
		TIM_OC1Init(TIM2,&TIM_OCInitStructure);                                                 
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);	
		
}


void TIM2_init(void)  
{  
		TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		/*MVIC*/
		//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannelPriority = 8;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                //Ê¹ÄÜTIM2ÖÐ¶ÏÍ¨µÀ  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //Ê¹ÄÜTIM2ÖÐ¶Ï  
    NVIC_Init(&NVIC_InitStructure); 
		
		/*TIM2 Base Init*/
    TIM_DeInit(TIM2);                                               //¸´Î»TIM2  
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;          //ÏµÍ³Ê±ÖÓ,²»·ÖÆµ,24M  
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      //ÏòÉÏ¼ÆÊýÄ£Ê½  
		TIM_TimeBaseStructure.TIM_Period = 47;                          //Ã¿100 uS´¥·¢Ò»´ÎÖÐ¶Ï,??ADC  
		TIM_TimeBaseStructure.TIM_Prescaler = 1000;                      //¼ÆÊýÊ±ÖÓ·ÖÆµ,f=1M,systick=1 uS  
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;              //·¢Éú0+1µÄupdateÊÂ¼þ²úÉúÖÐ¶Ï 

		TIM2_GPIO_Init();
		TIM2_PWM_OUT_Init();	
	
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                      //Ê¹ÄÜTIM2ÖÐ¶Ï

		TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);							//Ñ¡ÔñTIM14µÄtimerÎª´¥·¢Ô´  ´  
		//TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_ARRPreloadConfig(TIM2, ENABLE);
	
		TIM_Cmd(TIM2, ENABLE);
		
		
}  

void TIM1_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  
 	
	  GPIO_InitStructure.GPIO_Pin = CLK_Pin;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                   //????(??)??  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //Fast speed  
    GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_NOPULL;                    //??  
    GPIO_Init(CLK_GPIO_Port, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(CLK_GPIO_Port,GPIO_PinSource8,GPIO_AF_2);
}


void TIM1_Init(void)
{
	
    TIM_TimeBaseInitTypeDef timer_init_structure;  
		TIM_OCInitTypeDef timer_OCinit_structure; 
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		
		TIM1_GPIO_Init();
		
		/*MVIC*/
		NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;                //Ê¹ÄÜTIM22ÖÐ¶ÏÍ¨µÀ  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //Ê¹ÄÜTIM2ÖÐ¶Ï  
		NVIC_Init(&NVIC_InitStructure); 
			
	
  /* Time ??????*/
  timer_init_structure.TIM_Prescaler = 3;
  timer_init_structure.TIM_CounterMode = TIM_CounterMode_Up;  /* Time ????????????*/
  timer_init_structure.TIM_Period = 2;
  timer_init_structure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &timer_init_structure);

  /* ??1,2,3,4?PWM ???? */
  timer_OCinit_structure.TIM_OCMode = TIM_OCMode_PWM1;
  timer_OCinit_structure.TIM_OutputState = TIM_OutputState_Enable ;//TIM_OutputState_Enable; //PWM?????
  timer_OCinit_structure.TIM_OutputNState = TIM_OutputNState_Disable ;//TIM_OutputNState_Enable; //??PWM?????
  timer_OCinit_structure.TIM_OCPolarity = TIM_OCPolarity_High;  //PWM 1?????
  timer_OCinit_structure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //PWM?? 0?????
  timer_OCinit_structure.TIM_OCIdleState = TIM_OCIdleState_Set;
  timer_OCinit_structure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  timer_OCinit_structure.TIM_Pulse = 1; //?????
  TIM_OC1Init(TIM1, &timer_OCinit_structure);//????1??
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
  //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);                      //Ê¹ÄÜTIM1ÖÐ¶Ï
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
  /* TIM1 ?????*/
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);							//Ñ¡ÔñTIM1µÄtimerÎª´¥·¢Ô´  ´  
	TIM_SelectMasterSlaveMode(TIM1,TIM_MasterSlaveMode_Enable);
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);     //Çå³ýupdateÊÂ¼þÖÐ¶Ï±êÖ¾
 
	
  TIM_Cmd(TIM1, ENABLE);
	
  /* TIM1 ????? */
}

void ADC1_GPIO_Config()
{
    GPIO_InitTypeDef gpio_init_structure;  
    //??GPIO??  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);  
    //GPIOA                                                         //PA-0~3??ADC  
    gpio_init_structure.GPIO_Pin = ADCIN_1_Pin;  
    gpio_init_structure.GPIO_Mode = GPIO_Mode_AN;                   //????(??)??  
    gpio_init_structure.GPIO_OType = GPIO_OType_PP;                 //????  
    gpio_init_structure.GPIO_Speed = GPIO_Speed_2MHz;              //Fast speed  
    gpio_init_structure.GPIO_PuPd= GPIO_PuPd_UP;                    //??  
    GPIO_Init(ADCIN_1_GPIO_Port, &gpio_init_structure);  	
}

void ADC1_DMA1_Init()
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc_dma_tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = DMA_BUFFER_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC1);
  DMA_ClearITPendingBit(DMA1_IT_TC1);
  
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);  //DMA´«ÊäÍê³ÉÖÐ¶Ï
	
	  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
	
}

void ADC1_Init(void)
{
		ADC_InitTypeDef ADC_InitStructure;  
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);            //??ADC?? 

		NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;            //????????  
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;         //???????  
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO; //???????TIM1
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;//?????  
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;         //12????  
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;//????0-18??  
		
    ADC_Init(ADC1, &ADC_InitStructure);  
	
    ADC_OverrunModeCmd(ADC1, ENABLE);                               //????????  
    ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_1_5Cycles);               //??????,????125nS  
    ADC_GetCalibrationFactor(ADC1);                                 //?????ADC  
    ADC_Cmd(ADC1, ENABLE);                                          //??ADC1  
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN) == RESET);         //??ADC1????  
  
    ADC_DMACmd(ADC1, ENABLE);                                       //??ADC_DMA  
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);           //??DMA?????????  

		ADC_StartOfConversion(ADC1);
}

void ADC1_Configuration(void)
{
    ADC1_GPIO_Config();
    ADC1_DMA1_Init();
    ADC1_Init();
}


void IWDG_Config(void)
{
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
			RCC_ClearFlag();
	}

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	IWDG_SetReload(40000 / 20);
	IWDG_ReloadCounter();

	IWDG_Enable();
}
/******************************************
 BSP µ×²ã³õÊ¼»¯
******************************************/
void bsp_init(void)
{
	RCC_Configuration();
	TIM1_Init();
	TIM2_init();
	TIM3_init();
	//TIM14_init();
	ADC1_Configuration();
	RCC_GetClocksFreq(&SysClock);
	IO_GPIO_INIT();
	SMG_GPIO_INIT();
	Button_Init();
}




