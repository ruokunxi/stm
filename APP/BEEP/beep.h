//beef.h
#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"
#include "system.h"

extern void BEEP_Init(void);//��ʼ��
extern void BEEP_On(void);//��
extern void BEEP_Off(void);//��

#define BEEP PBout(8)

#endif

