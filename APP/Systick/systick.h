//Systick.h
#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"
#include "system.h"

#define SYSTICK (72)//ָ��SYSTICK�������Ƶ��Ϊ72MHz

extern void SysTick_Init(void);//��ʼ��systick��ʱ��
extern void delay_us(u32 nus);//��ʱ���ٺ���
extern void delay_ms(u32 nms);//��ʱ����΢��

#endif
