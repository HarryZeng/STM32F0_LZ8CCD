#ifndef __uid_H
#define __uid_H
#ifdef __cplusplus
 extern "C" {
#endif
#include 	"stm32f0xx.h"
#include 	"arch.h"
#include 	"stdbool.h"
#include 	"stdint.h"
#include 	"flash.h"
#include  "project.h"	 
	 
uint8_t FlashCheck(void);	 
void ProgramCheck(void); 

#ifdef __cplusplus
}
#endif
#endif /*__uid_H */


