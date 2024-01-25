//led.h
#ifndef _LED_H
#define _LED_H

//包含总头文件
#include "stm32f10x.h"

//声明各种操作函数
extern void LED_Init(void);//初始化函数
extern void LED_On(void);//开灯函数
extern void LED_Off(void);//关灯函数
extern void Delay(int n);//延时函数

//通过位带别名区操作LED0,LED1
//LED1 = 0,开灯;LED1 = 1,关灯;
#define LED1 PBout(5)
#define LED2 PEout(5)



#endif


