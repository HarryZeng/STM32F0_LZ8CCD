
///**
//  ********************************  STM32F0x1  *********************************
//  * @文件名     ： SelfStudy.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SelftStudy_H
#define __SelftStudy_H
#ifdef __cplusplus
 extern "C" {
#endif
#include  "main.h"
#include 	"stdbool.h"
#include 	"stdint.h"
#include 	"project.h"
#include  "arch.h"
#include 	"flash.h"
#include 	"display.h"
#include 	"key.h"
	 
	 

 
	 
void selfstudy(void);
void ATTSet(uint16_t ATTvalue);
#ifdef __cplusplus
}
#endif
#endif /*__SelftStudy_H */
