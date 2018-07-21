
#include "uid.h"



void DelaymsSet(int16_t ms)
{
	while (1)
	{
		ms--;
		if (ms <= 0)
			break;
	}
}

int ProgramCounter = 0;
void ProgramCheck(void)
{
	ProgramCounter = ReadFlash(ProgramRUNcounter_Mode_FLASH_DATA_ADDRESS);
	if (ProgramCounter > 65535 || ProgramCounter < 0)
	{
		ProgramCounter = 0;
		ResetParameter();
	}
	ProgramCounter = ProgramCounter + 1;
	WriteFlash(ProgramRUNcounter_Mode_FLASH_DATA_ADDRESS, ProgramCounter);
	DelaymsSet(50);
	if (ProgramCounter <= 1)
	{
		ResetParameter();
	}
}


/*************************************************************/
#define FLASH_START_ADDR1 0x08007FF0

uint8_t *UID = (uint8_t *)0x1FFFF7E8;  //获取UID  stm32f0:0x1FFFF7AC,stm32f100:0x1FFFF7E8
uint32_t Fml_Constant = 0x19101943;	//输入到公式的常熟
uint8_t *C = (uint8_t *)&Fml_Constant; //把常量转化成数组
uint8_t FormulaResult[4];
uint32_t FormulaCheck;
uint32_t UIDFlashResult;
uint16_t Fml_CRC16;
uint8_t D[12];

void Formula_100(uint8_t *D, uint8_t *Result)
{
	D[0] = UID[4];
	D[1] = UID[8];
	D[2] = UID[1];
	D[3] = UID[3];
	D[4] = UID[0];
	D[5] = UID[5];
	D[6] = UID[10];
	D[7] = UID[7];
	D[8] = UID[9];
	D[9] = UID[2];
	D[10] = UID[11];
	D[11] = UID[6];

	Result[0] = C[0] ^ D[0];
	Result[1] = C[1] ^ D[6] ^ D[7] ^ D[8] ^ D[9] ^ D[10] ^ D[11];
	Result[2] = C[2] ^ D[4];
	Result[3] = C[3] ^ D[2] ^ D[1];
}

uint8_t FlashCheck(void)
{
	uint8_t FlashFlag;
	Formula_100(D, FormulaResult);
	FormulaCheck = FormulaResult[0] + (FormulaResult[1] << 8) + (FormulaResult[2] << 16) + (FormulaResult[3] << 24);
	UIDFlashResult = *(__IO uint32_t *)(FLASH_START_ADDR1);
	if (UIDFlashResult == FormulaCheck)
		FlashFlag = 1;
	else
		FlashFlag = 0;

	return FlashFlag;
}
uint16_t Formula_CRC16(uint8_t *p, uint8_t len)
{
	uint8_t i;
	while (len--)
	{
		for (i = 0x80; i != 0; i >>= 1)
		{
			if ((Fml_CRC16 & 0x8000) != 0)
			{
				Fml_CRC16 <<= 1;
				Fml_CRC16 ^= 0x1021;
			}
			else
			{
				Fml_CRC16 <<= 1;
			}
			if ((*p & i) != 0)
			{
				Fml_CRC16 ^= 0x1021;
			}
		}
		p++;
	}
	return Fml_CRC16;
}


