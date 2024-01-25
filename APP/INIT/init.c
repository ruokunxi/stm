#include "init.h"
#include "led.h"
#include "beep.h"
#include "system.h"
#include "systick.h"//定时器的声明
#include "key.h"
#include "exti.h"
#include "uart.h"

//定义初始化函数指针数组保存各个硬件的初始化函数
//以后维护硬件的初始化代码只需这个数组即可,主函数main一个字都不动
//类比:int init_func[] ...
static PINIT_T init_func[]={
	SysTick_Init, //滴答定时器初始化
	LED_Init,     //LED初始化
	BEEP_Init,		//蜂鸣器初始化
	UART_Init,		//串口1初始化
	KEY_Init,			//按键初始化
	My_Exti_Init,	//外部中断初始化
	0							//为了退出下面的for循环
};

//定义硬件初始化总入口函数
void DEVICE_Init(void){
	//定义函数指针变量保存函数指针数组的首地址
	//类比:int *pfunc = init_func
	PINIT_T *pfunc = init_func;


	//遍历数组里面所有硬件初始化函数挨个调用
	for(; *pfunc;pfunc++)
		(*pfunc)();//注意:*运算符优先级低于后面的圆括号,所以前面需要加()
	}