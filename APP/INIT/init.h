#ifndef _INIT_H
#define _INIT_H

//包含总头文件
#include "stm32f10x.h"
#include "system.h"

//声明硬件初始化总函数
extern void DEVICE_Init(void);

//声明函数指针数据类型并且取名为PINIIT_T,将来用它定义的变量来指向各个硬件初始化函数
typedef void (*PINIT_T)(void);

#endif
