//Systick.c
#include "systick.h"
 
static u32 fac_us = 0;
static u32 fac_ms = 0;

void SysTick_Init(void){
	//1.指定时钟源 - 9MHz
	SysTick->CTRL &=~(1<<2);
	//2.指定1us计数9次
	fac_us = SYSTICK / 8;
	//3.指定1ms计数9000次
	fac_ms = fac_us * 1000;
}

//微秒延时
void delay_us(u32 nus){
	u32 temp;
	SysTick->LOAD = nus * fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp=SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));
	//关闭systick定时器
	SysTick->CTRL &= ~(1<<0);
	//清空计数器
	SysTick->VAL = 0x00;
}

//毫秒延时
void delay_ms(u32 nms){
		u32 temp;
	SysTick->LOAD = nms * fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp=SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));
	SysTick->CTRL &= ~(1<<0);
	SysTick->VAL = 0x00;
	}

	