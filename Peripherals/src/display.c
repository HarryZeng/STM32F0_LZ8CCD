///**
//  ********************************  STM32F0x1  *********************************
//  * @�ļ���     �� display.c
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
#include "arch.h"
#include "display.h"


/************************* �������� ***********************************/
SMG_Data_Typedef	SMG_Data=		
{
	0,0,
};


const  uint16_t  data_SMG_bit_table[SMG_bit_sum]= {
	
															SMG_data_bit1,
															SMG_data_bit2,
															SMG_data_bit3,
															SMG_data_bit4,
	
															SMG_data_bit5,
															SMG_data_bit6,
															SMG_data_bit7,
															SMG_data_bit8,
															SMG_data_bit9,
	
													 };

const uint16_t  data_SMG_seg_table[]= {
															SMG_seg_Data_0,		//0
															SMG_seg_Data_1,		//1
															SMG_seg_Data_2,		//2
															SMG_seg_Data_3,		//3
															SMG_seg_Data_4,		//4
															SMG_seg_Data_5,		//5
															SMG_seg_Data_6,		//6
															SMG_seg_Data_7,		//7
															SMG_seg_Data_8,		//8
															SMG_seg_Data_9,		//9
															SMG_seg_Data_A,		//10
															SMG_seg_Data_b,		//11
															SMG_seg_Data_C,		//12
															SMG_seg_Data_d,		//13
															SMG_seg_Data_E,		//14
															SMG_seg_Data_f,		//15
															SMG_seg_Data__,  	//16
															SMG_seg_Data_o,		//17
															SMG_seg_Data_n,		//18
															SMG_seg_Data_V,		//19
															SMG_seg_Data_S,		//20
															SMG_seg_Data_t,		//21
															SMG_seg_Data_dark,//22
															SMG_seg_Data_L,		//23
															SMG_seg_Data_P,		//24
															SMG_seg_Data_f,		//25 
															SMG_seg_Data_H,		//26
															SMG_seg_Data_I,		//27
															SMG_seg_Data_r,		//28
															
															
														 SMG_seg_Data_a_,		//29
														 SMG_seg_Data_b_, 	//30			
														 SMG_seg_Data_c_,	 	//31		
														 SMG_seg_Data_d_, 	//32		
														 SMG_seg_Data_e_,	 	//33		
														 SMG_seg_Data_f_, 	//34			
														 SMG_seg_Data_g_, 	//35		
														 SMG_seg_Data_h_, 	//36		
														 SMG_seg_Data_abcdefgh_,	//37 		
														 SMG_seg_Data_dark,	 //38
														 
														 SMG_seg_Data_U,		//39
															
													 };


unsigned char SMG_D4_to_D1_bit=0;
unsigned char SMG_D8_to_D5_bit=4;
uint8_t SMG_BIT=0;
uint8_t SMG_D9_BIT=0;		 
unsigned char SMG_data_Decode_table[1][SMG_bit_sum]=
{ 
     0x00,  0x00,  0x00,  0x00,  0x00,  0x00,		0x00, 	0x00,0x00
};

int SMG_D9_Decode_table=0x00;

/************************* �������� ***********************************/

/***********************************************************************
*
*����ܸ�����ʾ�˵�
*
************************************************************************/
void SMG_data_update(void)
{ 
		/*�����룬BIT1��BIT8��ʾ1��8������*/
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[1];
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[2];
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[3];
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[4];
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[5];
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[6];
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[7];
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[8];
}

/*����������ʾ*/
extern Button_STATUS KEY;
void ButtonMappingDisplay(uint8_t MappingFlag)
{ 
	if(MappingFlag==1)
	{
		if(KEY== ULOC)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[12];   		//D1	C
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[17];				//D2	O
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[23];				//D3	L
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[39];				//D4	U
		}
		else 
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[12];   		//D1	C
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[17];				//D2	O
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[23];				//D3	L
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];				//D4	none
		}
	}
	else if(MappingFlag==2)
	{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[21];   		//D1	t
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[27];				//D2	i
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[18];				//D3	n
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[27];				//D4	i
	}
	else if(MappingFlag==3)
	{	
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[21];   		//D1	t
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[20];				//D2	s
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[28];				//D3 	r
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];				//D4	none
	}
		
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];				//D5 	none
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];				//D6	none
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];				//D7	none
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];				//D8	none
	
	//SMG_Diplay();
}


void takeoffLED(void)
{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];				//D5 	none
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];				//D6	none
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];				//D7	none
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];				//D8	none
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];				//D5 	none
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];				//D6	none
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];				//D7	none
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];				//D8	none
}




uint8_t GetIntNumber(uint32_t Number)
{
		uint8_t K1=0;
		while (Number)  
		{  
				Number = Number / 10;  
				K1++;  
		}  
		return K1;
}
/*��ʾģʽ1*/
void SMG_DisplayModeONE(int16_t OneSecondTime,int16_t Threshold,int16_t ADCvalue)
{ 
		uint8_t k_ADCvalue,k_Threshold;
		
		k_ADCvalue = GetIntNumber(ADCvalue);
		k_Threshold = GetIntNumber(Threshold);
		
		if(OneSecondTime)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[ADCvalue%10];					//D5
			if(k_Threshold>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(ADCvalue/10)%10];		//D6
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none	
			if(k_Threshold>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(ADCvalue/100)%10];	//D7
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];		
			if(k_Threshold>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ADCvalue/1000)%10];	//D8
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
		}
		else
		{
				SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];											//none
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[26];											//H
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[21];											//T
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[13];											//D
		}
}

/*��ʾģʽ1-Detect-HI*/
void SMG_DisplayModeONE_Detect_AREA_HI(int16_t OneSecondTime, int16_t HI_Value, int16_t ADCvalue)
{ 
		uint8_t k_ADCvalue,k_Threshold;
		
		k_ADCvalue = GetIntNumber(ADCvalue);
		k_Threshold = GetIntNumber(HI_Value);
		if(OneSecondTime)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[HI_Value%10];					//D5
			if(k_Threshold>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(HI_Value/10)%10];		//D6
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none	
			if(k_Threshold>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(HI_Value/100)%10];	//D7
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];		
			if(k_Threshold>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(HI_Value/1000)%10];	//D8
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
		}
		else
		{
				SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];											//none
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[27];											//I
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[26];											//H
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[13];											//D
		}
}

/*��ʾģʽ1-Detect-LO*/
void SMG_DisplayModeONE_Detect_AREA_LO(int16_t OneSecondTime, int16_t LO_Value, int16_t ADCvalue)
{ 
uint8_t k_ADCvalue,k_Threshold;
		
		k_ADCvalue = GetIntNumber(ADCvalue);
		k_Threshold = GetIntNumber(LO_Value);
		
		if(OneSecondTime)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[LO_Value%10];					//D5
			if(k_Threshold>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(LO_Value/10)%10];		//D6
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none	
			if(k_Threshold>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(LO_Value/100)%10];	//D7
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];		
			if(k_Threshold>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(LO_Value/1000)%10];	//D8
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
		}
		else
		{
				SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];											//none
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[17];											//O
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[23];											//L
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[13];											//D
		}
}

/*��ʾģʽ2*/
void SMG_DisplayModeTWO(int16_t RegisterB)
{ 

	if(RegisterB)
	{
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[12];					//D5		c
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[18];					//D6		n
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];					//D7		none
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];					//D8		none	
	}
	else
	{
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[17];					//D5	o
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[18];					//D6	n
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];					//D7	none
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];					//D8  none
	}
		
}

/*��ʾģʽ3*/
void SMG_DisplayModeTHIRD(int16_t CPV_counter)
{ 
		uint8_t k_CPV_counter;
		
		k_CPV_counter = GetIntNumber(CPV_counter);
	
		
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[CPV_counter%10];							//D1
		if(k_CPV_counter>=2)
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[(CPV_counter/10)%10];				//D2
		else
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
		if(k_CPV_counter>=3)
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[(CPV_counter/100)%10];				//D3
		else
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
		if(k_CPV_counter>=4)
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[(CPV_counter/1000)%10];			//D4
		else
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none

		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];										//none
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[26];													//D6	H
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[21];													//D7	t
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[13];													//D8	D
}

/*��ʾģʽDETECT*/
void SMG_DisplayModeDETECT(int16_t DETECT)
{ 
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[12];					//D1	c
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];					//D2	t
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];					//D3	e
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[13];					//D4	d
	
	if(DETECT)
	{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[10];					//D5		a
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[14];					//D6		e
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[28];					//D7		r
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[10];					//D8		a
	}
	else
	{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D5	none
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[13];					//D6	d
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[21];					//D7	t
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[20];					//D8  s
	}
		
}

/*���ܲ˵�-SV*/
void SMG_DisplaSV(uint32_t SV_counter)
{ 
//		uint8_t k_CSV_counter;
//		
//		k_CSV_counter = GetIntNumber(SV_counter);
//	
//		SMG_data_Decode_table[0][0]=data_SMG_seg_table[SV_counter%10];						//D1
//	if(k_CSV_counter>=2)
//		SMG_data_Decode_table[0][1]=data_SMG_seg_table[(SV_counter/10)%10];			//D2
//	else
//			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
//	if(k_CSV_counter>=3)
//		SMG_data_Decode_table[0][2]=data_SMG_seg_table[(SV_counter/100)%10];			//D3
//	else
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
//	if(k_CSV_counter>=4)
//		SMG_data_Decode_table[0][3]=data_SMG_seg_table[(SV_counter/1000)%10];		//D4
//	else
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//	if(k_CSV_counter>=5)
//		SMG_data_Decode_table[0][4]=data_SMG_seg_table[(SV_counter/10000)%10];		//D5
//	else
//			SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];										//none

//		SMG_data_Decode_table[0][5]=data_SMG_seg_table[19];												//D6	v
//		SMG_data_Decode_table[0][6]=data_SMG_seg_table[20];												//D7	s
//		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];												//D8	none
}

/*���ܲ˵�-CSV*/
void SMG_DisplaCSV(uint32_t CSV_counter)
{ 
		if(CSV_counter==0)
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[0];												//D6	0
		else if(CSV_counter==1)
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[1];												//D6	1
		else if(CSV_counter==2)
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[2];												//D6	2
		else if(CSV_counter==3)
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[3];												//D6	3
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[24];												//D6	p
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];												//D7	none
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];												//D8	none
}

/*���ܲ˵�-FSV*/
void SMG_DisplayFSV(uint32_t FSV_counter)
{ 
//		uint8_t k_CFV_counter;
//		
//		k_CFV_counter = GetIntNumber(FSV_counter);
//	
//		SMG_data_Decode_table[0][0]=data_SMG_seg_table[FSV_counter%10];						//D1
//	if(k_CFV_counter>=2)
//		SMG_data_Decode_table[0][1]=data_SMG_seg_table[(FSV_counter/10)%10];			//D2
//	else
//			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
//	if(k_CFV_counter>=3)
//		SMG_data_Decode_table[0][2]=data_SMG_seg_table[(FSV_counter/100)%10];			//D3
//	else
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
//	if(k_CFV_counter>=4)
//		SMG_data_Decode_table[0][3]=data_SMG_seg_table[(FSV_counter/1000)%10];		//D4
//	else
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//	if(k_CFV_counter>=5)
//		SMG_data_Decode_table[0][4]=data_SMG_seg_table[(FSV_counter/10000)%10];		//D5
//	else
//			SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];										//none

//		SMG_data_Decode_table[0][5]=data_SMG_seg_table[19];												//D6	v
//		SMG_data_Decode_table[0][6]=data_SMG_seg_table[20];												//D7	s
//		SMG_data_Decode_table[0][7]=data_SMG_seg_table[15];												//D8	f
}


/*���ܲ˵�-2-1,TOFF*/
void SMG_DisplayMenuTwo_TOFF(void)
{ 
	static uint8_t Blinkflag=1;
		if(Blinkflag)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[15];						//D5	f
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[15];						//D6	f
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[17];						//D7	o
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[21];						//D8	t
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];						//D5	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];						//D6	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];						//D7	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];						//D8	none
			Blinkflag = 1;
		}
}

/*���ܲ˵�-2-2,OFFD*/
void SMG_DisplayMenuTwo_OFFD(void)
{ 
		static uint8_t Blinkflag=1;
		if(Blinkflag)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[13];						//D5	d
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[15];						//D6	f
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[15];						//D7	f
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[17];						//D8	o
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];						//D5	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];						//D6	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];						//D7	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];						//D8	none
			Blinkflag = 1;
		}
	
}

/*���ܲ˵�-2-2-1,OFFD�趨�˵�*/
void SMG_DisplayMenuTwo_OFFD_SET(int16_t OFFD_DELAY,uint8_t BlinkONOFF)
{ 
		static uint8_t Blinkflag=1;
		uint8_t k_OFFD_DELAY;
		
		k_OFFD_DELAY = GetIntNumber(OFFD_DELAY);
	
	if(BlinkONOFF)
	{
		if(Blinkflag)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[OFFD_DELAY%10];					//D1
			if(k_OFFD_DELAY>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(OFFD_DELAY/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_OFFD_DELAY>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(OFFD_DELAY/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_OFFD_DELAY>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(OFFD_DELAY/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];					//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];					//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D4	none
			Blinkflag = 1;
		}
	}
	else
	{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[OFFD_DELAY%10];					//D1
			if(k_OFFD_DELAY>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(OFFD_DELAY/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_OFFD_DELAY>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(OFFD_DELAY/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_OFFD_DELAY>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(OFFD_DELAY/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
	}
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[13];											//D5	d
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[15];											//D6	f
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[15];											//D7	f
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[17];											//D8	o
	
}

/*���ܲ˵�-2-3,ON Delay*/
void SMG_DisplayMenuTwo_ON_Delay(void)
{ 
	static uint8_t Blinkflag=1;
	
		if(Blinkflag)
		{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[13];						//D5	d
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[16];						//D6	-
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[18];						//D7	n
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[17];						//D8	o
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];						//D5	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];						//D6	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];						//D7	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];						//D8	none
			Blinkflag = 1;
		}

	
}

/*���ܲ˵�-2-3_1,ON Delay�趨�˵�*/
void SMG_DisplayMenuTwo_ON_Delay_SET(int16_t ON_DELAY,uint8_t BlinkONOFF)
{ 
		static uint8_t Blinkflag=1;
		uint8_t k_ON_DELAY;
		
		k_ON_DELAY = GetIntNumber(ON_DELAY);
	if(BlinkONOFF)
	{
		if(Blinkflag)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[ON_DELAY%10];					//D1
			if(k_ON_DELAY>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(ON_DELAY/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_ON_DELAY>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(ON_DELAY/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_ON_DELAY>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ON_DELAY/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];					//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];					//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D4	none
			Blinkflag = 1;
		}
	}
	else
	{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[ON_DELAY%10];					//D1
			if(k_ON_DELAY>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(ON_DELAY/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_ON_DELAY>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(ON_DELAY/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_ON_DELAY>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ON_DELAY/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
	}
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[13];						//D5	d
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[16];						//D6	-
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[18];						//D7	n
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[17];						//D8	o
	
}

/*���ܲ˵�-2-4,SHOT*/
void SMG_DisplayMenuTwo_SHOT(void)
{ 
		static uint8_t Blinkflag=1;
	
		if(Blinkflag)
		{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[21];						//D5	t
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[17];						//D6	o
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[26];						//D7	H
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[20];						//D8	s
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];						//D5	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];						//D6	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];						//D7	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];						//D8	none
			Blinkflag = 1;
		}	
}
/*���ܲ˵�-2-4-1,SHOT�趨�˵�*/
void SMG_DisplayMenuTwo_SHOT_SET(int16_t SHOT,uint8_t BlinkONOFF)
{
		static uint8_t Blinkflag=1;
		uint8_t k_SHOT;
		
		k_SHOT = GetIntNumber(SHOT);
	if(BlinkONOFF)
	{
		if(Blinkflag)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[SHOT%10];					//D1
			if(k_SHOT>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(SHOT/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_SHOT>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(SHOT/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_SHOT>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(SHOT/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
			Blinkflag = 0;
		}
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];					//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];					//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D4	none
			Blinkflag = 1;
		}
	}
	else
	{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[SHOT%10];					//D1
			if(k_SHOT>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(SHOT/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_SHOT>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(SHOT/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_SHOT>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(SHOT/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
	}
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[21];								//D5	t
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[17];								//D6	o
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[26];								//D7	H
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s
	
}


/*���ܲ˵�-2-5,DEL*/
void SMG_DisplayMenuTwo_DEL(void)
{
//			static uint8_t Blinkflag=1;
//	
//		SMG_data_Decode_table[0][0]=data_SMG_seg_table[35];						//D1	seg->f
//		SMG_data_Decode_table[0][1]=data_SMG_seg_table[35];						//D2	seg->f
//		SMG_data_Decode_table[0][2]=data_SMG_seg_table[35];						//D3	seg->f
//		SMG_data_Decode_table[0][3]=data_SMG_seg_table[35];						//D4	seg->f
//	
//		if(Blinkflag)
//		{
//		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];						//D5	none
//		SMG_data_Decode_table[0][5]=data_SMG_seg_table[23];						//D6	L
//		SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];						//D7	E
//		SMG_data_Decode_table[0][7]=data_SMG_seg_table[13];						//D8	D
//			Blinkflag = 0;
//		}
//		else
//		{
//			SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];						//D5	none
//			SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];						//D6	none
//			SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];						//D7	none
//			SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];						//D8	none
//			Blinkflag = 1;
//		}
}

/*���ܲ˵�-2-5-1,DEL�趨�˵�*/
void SMG_DisplayMenuTwo_DEL_SET(int16_t DEL,uint8_t BlinkONOFF)
{
//		static uint8_t Blinkflag=1;
//		uint8_t k_SHOT;
//		
//		k_SHOT = GetIntNumber(DEL);
//	if(BlinkONOFF)
//	{
//		if(Blinkflag)
//		{
//			SMG_data_Decode_table[0][0]=data_SMG_seg_table[DEL%10];					//D1
//			if(k_SHOT>=2)
//				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(DEL/10)%10];			//D2
//			else
//				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
//			if(k_SHOT>=3)
//				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(DEL/100)%10];		//D3
//			else
//				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
//			if(k_SHOT>=4)
//				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(DEL/1000)%10];		//D4
//			else
//				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//			Blinkflag = 0;
//		}
//		else
//		{
//			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D1	none
//			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];					//D2	none
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];					//D3	none
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D4	none
//			Blinkflag = 1;
//		}
//	}
//	else
//	{
//			SMG_data_Decode_table[0][0]=data_SMG_seg_table[DEL%10];					//D1
//			if(k_SHOT>=2)
//				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(DEL/10)%10];			//D2
//			else
//				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
//			if(k_SHOT>=3)
//				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(DEL/100)%10];		//D3
//			else
//				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
//			if(k_SHOT>=4)
//				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(DEL/1000)%10];		//D4
//			else
//				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//		
//		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];						//D5	none
//		SMG_data_Decode_table[0][5]=data_SMG_seg_table[23];						//D6	L
//		SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];						//D7	E
//		SMG_data_Decode_table[0][7]=data_SMG_seg_table[13];						//D8	D
//	}
}


/*SET-step-1ģʽ�˵�*/
void SMG_DisplaySET_Step_1_Mode(int16_t modeflag,uint32_t ADCINvalue)
{ 
	static uint8_t bilinkflag=0;
		uint8_t k_ADCINvalue;
		
		k_ADCINvalue = GetIntNumber(ADCINvalue);
		/* 3�����ѣ���˸*/
		if(modeflag==1)   
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];								//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];								//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];								//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];								//D4	none
			
			/*��˸Ч��*/
			if(bilinkflag)
			{
				SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];								//D5	1
				SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
				SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
				SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s	
				bilinkflag = 0;
			}
			else
			{
				SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];								//D5	none
				SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];								//D6	none
				SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];								//D7	none
				SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];								//D8	none
				bilinkflag = 1;
			}
		}
		/*3���*/
		else if(modeflag==2)
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[ADCINvalue%10];					//D1
			if(k_ADCINvalue>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(ADCINvalue/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_ADCINvalue>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(ADCINvalue/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_ADCINvalue>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ADCINvalue/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
			SMG_data_Decode_table[0][4]=data_SMG_seg_table[1];								//D5	1
			SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
			SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
			SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s	
		}
		/*3����*/
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];								//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];								//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];								//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];								//D4	none
			SMG_data_Decode_table[0][4]=data_SMG_seg_table[1];								//D5	1
			SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
			SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
			SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s
		}
}

/*SET-step-2ģʽ�˵�*/
void SMG_DisplaySET_Step_2_Mode(int16_t modeflag,uint32_t ADCINvalue,uint32_t NewThreshold)
{ 
	static uint8_t bilinkflag=0;
	uint8_t k_NewThreshold;
		
	k_NewThreshold = GetIntNumber(NewThreshold);
		/* 3�����ѣ���˸*/
		if(modeflag==1)   
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];								//D1	none
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];								//D2	none
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];								//D3	none
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];								//D4	none
			
			/*��˸Ч��*/
			if(bilinkflag)
			{
				SMG_data_Decode_table[0][4]=data_SMG_seg_table[2];								//D5	2
				SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
				SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
				SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s	
				bilinkflag = 0;
			}
			else
			{
				SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];								//D5	none
				SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];								//D6	none
				SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];								//D7	none
				SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];								//D8	none
				bilinkflag = 1;
			}
		}
		/*3���*/
		else if(modeflag==2)  //modeflag  ==2
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[NewThreshold%10];					//D1
			if(k_NewThreshold>=2)
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[(NewThreshold/10)%10];			//D2
			else
				SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
			if(k_NewThreshold>=3)
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[(NewThreshold/100)%10];		//D3
			else
				SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
			if(k_NewThreshold>=4)
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[(NewThreshold/1000)%10];		//D4
			else
				SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none			
			
				SMG_data_Decode_table[0][4]=data_SMG_seg_table[2];								//D5	2
				SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
				SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
				SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s	
		}
		/*3����*/
		else
		{
			SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D1	
			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];					//D2
			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];					//D3
			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D4
			SMG_data_Decode_table[0][4]=data_SMG_seg_table[2];								//D5	2
			SMG_data_Decode_table[0][5]=data_SMG_seg_table[21];								//D6	t
			SMG_data_Decode_table[0][6]=data_SMG_seg_table[14];								//D7	E
			SMG_data_Decode_table[0][7]=data_SMG_seg_table[20];								//D8	s
		}
}

/*OUT1,OUT2״̬��ʾ*/
void SMG_DisplayOUT_STATUS(uint8_t OUT1_STATUS,uint8_t OUT2_STATUS)
{ 
		OUT1_STATUS = ReadGPIO_Pin_State(OUT1_GPIO_Port,OUT1_Pin);
		//OUT2_STATUS = GPIO_ReadInputDataBit(OUT2_GPIO_Port,OUT2_Pin);
		//OUT3_STATUS = !GPIO_ReadInputDataBit(OUT3_GPIO_Port,OUT3_Pin);

		if(OUT1_STATUS==0 && OUT2_STATUS==1)
		{
			SMG_data_Decode_table[0][8] = data_SMG_seg_table[33]|data_SMG_seg_table[34];						//D1	33->e f seg	
		}
		else if(OUT1_STATUS==1 && OUT2_STATUS==0)
		{								
			SMG_data_Decode_table[0][8] = data_SMG_seg_table[30]|data_SMG_seg_table[31];						//D1	30->b,3->c seg
		}
		else if(OUT1_STATUS==1 && OUT2_STATUS==1)
		{
			SMG_data_Decode_table[0][8] = data_SMG_seg_table[30]|data_SMG_seg_table[31]|data_SMG_seg_table[33]|data_SMG_seg_table[34];						//D1	b c e f seg
		}
		else
		{
			SMG_data_Decode_table[0][8] = data_SMG_seg_table[22];
		}
}

/*END ��ʾ�˵�*/
void END_Display(void)
{

		SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];

		SMG_data_Decode_table[0][2]=data_SMG_seg_table[13];
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[18];
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[14];

		SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];
}

/*DUST ��ʾ�˵�*/
void Dust_Display(void)
{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[21]; //T
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[20];	//S
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[39];	//U
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[13];	//D
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];
}

void ParameterDisplay(void)
{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[21];
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[27];
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[18];
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[27];
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];
}

/*ATT100  �˵�*/
void SMG_DisplayATT100(int16_t ATT100Value,uint32_t ADCValue)
{ 
//		uint8_t k_ADC_counter,k_ATT_Counter;
//		
//	/*ADC*/
//		k_ADC_counter = GetIntNumber(ADCValue);
//		SMG_data_Decode_table[0][0]=data_SMG_seg_table[ADCValue%10];							//D1
//		if(k_ADC_counter>=2)
//			SMG_data_Decode_table[0][1]=data_SMG_seg_table[(ADCValue/10)%10];				//D2
//		else
//			SMG_data_Decode_table[0][1]=data_SMG_seg_table[22];										//none
//		if(k_ADC_counter>=3)
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[(ADCValue/100)%10];				//D3
//		else
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none
//		if(k_ADC_counter>=4)
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ADCValue/1000)%10];			//D4
//		else
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//		if(k_ADC_counter>=4)
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[(ADCValue/1000)%10];			//D4
//		else
//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];										//none
//		
//		/*ATT100*/
//		k_ATT_Counter = GetIntNumber(ATT100Value);
//		SMG_data_Decode_table[0][4]=data_SMG_seg_table[ATT100Value%10];								//D5
//		if(k_ATT_Counter>=2)
//			SMG_data_Decode_table[0][5]=data_SMG_seg_table[(ATT100Value/10)%10];				//D6
//		else
//			SMG_data_Decode_table[0][5]=data_SMG_seg_table[22];													//none
//		if(k_ATT_Counter>=3)
//			SMG_data_Decode_table[0][6]=data_SMG_seg_table[(ATT100Value/100)%10];				//D7
//		else
//			SMG_data_Decode_table[0][6]=data_SMG_seg_table[22];													//none

//		SMG_data_Decode_table[0][7]=data_SMG_seg_table[10];														//D8	A
}

/*PERCENTAGE  �˵�*/
void SMG_DisplayPERCENTAGE(int16_t PERCENTAGE_Value)
{ 
//		uint8_t k_PER_counter;
//		
//		/*PERCENTAGE*/
//		k_PER_counter = GetIntNumber(PERCENTAGE_Value);
//		
//		SMG_data_Decode_table[0][0]=data_SMG_seg_table[24];				//P 24
//		
//		SMG_data_Decode_table[0][1]=data_SMG_seg_table[PERCENTAGE_Value%10];							//D1
//		if(k_PER_counter>=2)
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[(PERCENTAGE_Value/10)%10];				//D2
//		else
//			SMG_data_Decode_table[0][2]=data_SMG_seg_table[22];										//none

//			SMG_data_Decode_table[0][3]=data_SMG_seg_table[35];      // 35 -
//		
//			SMG_data_Decode_table[0][4]=data_SMG_seg_table[28];				//	R	28
//			SMG_data_Decode_table[0][5]=data_SMG_seg_table[14];				//	E	14
//			SMG_data_Decode_table[0][6]=data_SMG_seg_table[24];				//	P 24
//			SMG_data_Decode_table[0][7]=data_SMG_seg_table[22];
}


/*DSC �˵�*/
void SMG_DisplayMenuDSC(int16_t DSC)
{ 
		SMG_data_Decode_table[0][4]=data_SMG_seg_table[22];					//D1	none
		SMG_data_Decode_table[0][5]=data_SMG_seg_table[12];					//D2	C
		SMG_data_Decode_table[0][6]=data_SMG_seg_table[20];					//D3	S
		SMG_data_Decode_table[0][7]=data_SMG_seg_table[13];					//D4	D
	
	if(DSC)
	{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[22];					//D5		none
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[18];					//D6		n
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[17];					//D7		o
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D8		none
	}
	else
	{
		SMG_data_Decode_table[0][0]=data_SMG_seg_table[15];					//D5	f
		SMG_data_Decode_table[0][1]=data_SMG_seg_table[15];					//D6	f	
		SMG_data_Decode_table[0][2]=data_SMG_seg_table[17];					//D7	o
		SMG_data_Decode_table[0][3]=data_SMG_seg_table[22];					//D8  none
	}
		
}

/***********************************************************************
*
*����ܵĻ�����������
*
************************************************************************/
void SMG_Init(void)
{
	//��������	
//	send_seg_RP0(SMG_seg_Data_dark);
//	send_bit_RP1(SMG_data_bit_allnot);
}	
	

/*����*/

void send_seg_RP0(int32_t RP0_data)
{
		if(RP0_data & BIT0)	
			SMG_seg_a( SMG_OFF );
	else	SMG_seg_a( SMG_ON );
		
		if(RP0_data & BIT1)	
			SMG_seg_b( SMG_OFF );
	else	SMG_seg_b( SMG_ON );
		
		if(RP0_data & BIT2)	
			SMG_seg_c( SMG_OFF );
	else	SMG_seg_c( SMG_ON );
		
		if(RP0_data & BIT3)	
			SMG_seg_d( SMG_OFF );
	else	SMG_seg_d( SMG_ON );
		
		if(RP0_data & BIT4)	
			SMG_seg_e( SMG_OFF );
	else	SMG_seg_e( SMG_ON );
		
		if(RP0_data & BIT5)	
			SMG_seg_f( SMG_OFF );
	else	SMG_seg_f( SMG_ON );
		
		if(RP0_data & BIT6)	
			SMG_seg_g( SMG_OFF );
	else	SMG_seg_g( SMG_ON );
	
}

/*λƬѡ*/
void send_bit_RP1(int32_t RP1_data)
{
		if(RP1_data & BIT0)	
			SMG_bit1( SMG_ON );
	else	SMG_bit1( SMG_OFF);
		
		if(RP1_data & BIT1)	
			SMG_bit2( SMG_ON );
	else	SMG_bit2( SMG_OFF);
		
		if(RP1_data & BIT2)	
			SMG_bit3( SMG_ON );
	else	SMG_bit3( SMG_OFF);
		
		if(RP1_data & BIT3)	
			SMG_bit4( SMG_ON );
	else	SMG_bit4( SMG_OFF );
		
		if(RP1_data & BIT4)	
			SMG_bit5( SMG_ON );
	else	SMG_bit5( SMG_OFF );
		
		if(RP1_data & BIT5)	
			SMG_bit6( SMG_ON );
	else	SMG_bit6( SMG_OFF );
		
		if(RP1_data & BIT6)	
			SMG_bit7( SMG_ON );
	else	SMG_bit7( SMG_OFF );
		
		if(RP1_data & BIT7)	
			SMG_bit8( SMG_ON );
	else	SMG_bit8( SMG_OFF );
		
		if(RP1_data & BIT8)	
			SMG_bit9( SMG_ON );
	else	SMG_bit9( SMG_OFF );

}

///*D4 �� D1�Ķ�̬ɨ��*/
//void SMG_D4_to_D1_Display(void)
//{
//		//SMG_Data.SMG_seg=SMG_data_Decode_table[0][SMG_D4_to_D1_bit];	 //���룬�������
//		SMG_Data.SMG_seg = 	SMG_seg_Data_0;
//		SMG_Data.SMG_bit=data_SMG_bit_table[SMG_D4_to_D1_bit];				//λƬѡ���������
//	
//		/*ʧ�ܣ���������*/
// 		send_seg_RP0(SMG_seg_Data_dark);
// 		send_bit_RP1(SMG_Data.SMG_bit);
//		/*ʹ�ܣ�����ʾ*/
//		send_seg_RP0(SMG_Data.SMG_seg);
//		send_bit_RP1(SMG_Data.SMG_bit);
//		/*ѭ����ʾ*/
//		if(SMG_D4_to_D1_bit++>=3)	
//			SMG_D4_to_D1_bit=0;
//}

///*D8 �� D5�Ķ�̬ɨ��*/
//void SMG_D8_to_D5_Display(void)
//{
//		//SMG_Data.SMG_seg=SMG_data_Decode_table[0][SMG_D8_to_D5_bit];	 //���룬�������
//		SMG_Data.SMG_seg = 	SMG_seg_Data_0;
//		SMG_Data.SMG_bit=data_SMG_bit_table[SMG_D8_to_D5_bit];				//λƬѡ���������
//	
//		/*ʧ�ܣ���������*/
// 		send_seg_RP0(SMG_seg_Data_dark);
// 		send_bit_RP1(SMG_Data.SMG_bit);
//		/*ʹ�ܣ�����ʾ*/
//		send_seg_RP0(SMG_Data.SMG_seg);
//		send_bit_RP1(SMG_Data.SMG_bit);

//		/*ѭ����ʾ*/
//		if(SMG_D8_to_D5_bit++>=SMG_bit_sum-1)	
//			SMG_D8_to_D5_bit=4;
//}

///*D9��ʾ*/
//void SMG_D9_Display(void)
//{
//		SMG_Data.SMG_seg=SMG_D9_Decode_table;	 												//���룬�������
//		SMG_Data.SMG_bit=SMG_data_bit9;				//λƬѡ���������
//	
//		/*ʧ�ܣ���������*/
// 		send_seg_RP0(SMG_seg_Data_dark);
// 		send_bit_RP1(SMG_Data.SMG_bit);
//		/*ʹ�ܣ�����ʾ*/
//		send_seg_RP0(SMG_Data.SMG_seg);
//		send_bit_RP1(SMG_Data.SMG_bit);
//}


void SMG_Diplay(void)
{
		SMG_Data.SMG_seg=SMG_data_Decode_table[0][SMG_BIT];
		SMG_Data.SMG_bit=data_SMG_bit_table[SMG_BIT];				//λƬѡ���������
//	
	
//		SMG_Data.SMG_seg=SMG_seg_Data_7;
//		SMG_Data.SMG_bit=SMG_data_bit1;				//λƬѡ���������
	
		/*ʧ�ܣ���������*/
 		send_seg_RP0(SMG_seg_Data_dark);
 		send_bit_RP1(SMG_Data.SMG_bit);
		/*ʹ�ܣ�����ʾ*/
		send_seg_RP0(SMG_Data.SMG_seg);
		send_bit_RP1(SMG_Data.SMG_bit);

		/*ѭ����ʾ*/
		if(SMG_BIT++>=SMG_bit_sum-1)	
			SMG_BIT=0;
}


