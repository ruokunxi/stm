//Systick.h
#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"
#include "system.h"

#define SYSTICK (72)//指定SYSTICK定制其的频率为72MHz

extern void SysTick_Init(void);//初始化systick定时器
extern void delay_us(u32 nus);//延时多少毫秒
extern void delay_ms(u32 nms);//延时多少微秒

#endif
