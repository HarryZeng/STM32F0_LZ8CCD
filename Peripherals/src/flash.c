#include "flash.h"
#include "stm32f0xx_flash.h"


//FLASH_CHANNEL OUT1_ModeFlashChannel;
//FLASH_CHANNEL OUT1_ValueFlashChannel;
//FLASH_CHANNEL CSVFlashChannel;
//FLASH_CHANNEL Threshold_ModeFlashChannel;
//FLASH_CHANNEL DACOUT_ModeFlashChannel;
//FLASH_CHANNEL KEY_ModeFlashChannel;
//FLASH_CHANNEL RegisterB_ModeFlashChannel;
//FLASH_CHANNEL DEL_ModeFlashChannel;
//FLASH_CHANNEL HI_ModeFlashChannel;
//FLASH_CHANNEL LO_ModeFlashChannel;
//FLASH_CHANNEL DETECT_ModeFlashChannel;

/*  ��FLASH
ProgramCounter 		= *(__IO uint32_t*)(ProgramRUNcounter_Mode_FLASH_DATA_ADDRESS);
*/

void InitInternalFlash(uint32_t addr)
{
	FLASH_Unlock(); //����FLASH��̲���������
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);//�����־λ
	FLASH_ErasePage(addr); //����ָ����ַҳ
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);//�����־λ
	FLASH_Lock(); //����FLASH��̲���������
}

FLASH_Status WriteInternalFlash(uint32_t addr,uint32_t data)
{
	FLASH_Unlock(); //����FLASH��̲���������
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);//�����־λ
	//FLASH_ErasePage(addr); //����ָ����ַҳ
	FLASH_ProgramWord(addr ,data); //��ָ��ҳ��0��ַ��ʼд
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);//�����־λ
	FLASH_Lock(); //����FLASH��̲���������
}


/******************************************
����FLASH
*******************************************/
void EraseFlash(void)
{	
	InitInternalFlash(OUT1_Mode_FLASH_DATA_ADDRESS);
	InitInternalFlash(OUT1_Value_FLASH_DATA_ADDRESS);
	InitInternalFlash(CSV_FLASH_DATA_ADDRESS);
	InitInternalFlash(Threshold_FLASH_DATA_ADDRESS);
	InitInternalFlash(DACOUT1_FLASH_DATA_ADDRESS);
	InitInternalFlash(KEY_FLASH_DATA_ADDRESS);
	InitInternalFlash(RegisterB_FLASH_DATA_ADDRESS);
	InitInternalFlash(DEL_FLASH_DATA_ADDRESS);
	InitInternalFlash(SET_VREF_FLASH_DATA_ADDRESS);
	//InitInternalFlash(SB_MAX_FLASH_DATA_ADDRESS);
	InitInternalFlash(DETECT_FLASH_DATA_ADDRESS);
	InitInternalFlash(HI_FLASH_DATA_ADDRESS);
	InitInternalFlash(LO_FLASH_DATA_ADDRESS);
	InitInternalFlash(DSC_FLASH_DATA_ADDRESS);
}

/******************************************
дFLASH
*******************************************/
uint32_t tempflashdata;
void WriteFlash(uint32_t addr,uint32_t data)
{	
		uint32_t LastAddr = addr;
		tempflashdata 		= *(__IO uint32_t*)(addr);
		while(tempflashdata!=0xFFFFFFFF)
		{
			addr = addr + 4;
			if(addr-LastAddr>1024)
				InitInternalFlash(LastAddr);
			tempflashdata = *(__IO uint32_t*)(addr);
		}
		WriteInternalFlash(addr,data);
		
}

/******************************************
��FLASH
*******************************************/
//uint32_t tempflashdata;
uint32_t  ReadFlash(uint32_t addr)
{	
		uint32_t HeadAddr = addr;
		uint32_t LastAddr = addr;
		tempflashdata 		= *(__IO uint32_t*)(addr);
		while(tempflashdata!=0xFFFFFFFF)
		{
			 LastAddr = addr;
			addr = addr + 4;
			tempflashdata 		= *(__IO uint32_t*)(addr);
		}
		return tempflashdata 		= *(__IO uint32_t*)(LastAddr);
}
