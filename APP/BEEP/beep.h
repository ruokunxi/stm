//beef.h
#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"
#include "system.h"

extern void BEEP_Init(void);//初始化
extern void BEEP_On(void);//开
extern void BEEP_Off(void);//关

#define BEEP PBout(8)

#endif

