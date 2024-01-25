//Systick.c
#include "systick.h"
 
static u32 fac_us = 0;
static u32 fac_ms = 0;

void SysTick_Init(void){
	//1.ָ��ʱ��Դ - 9MHz
	SysTick->CTRL &=~(1<<2);
	//2.ָ��1us����9��
	fac_us = SYSTICK / 8;
	//3.ָ��1ms����9000��
	fac_ms = fac_us * 1000;
}

//΢����ʱ
void delay_us(u32 nus){
	u32 temp;
	SysTick->LOAD = nus * fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp=SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));
	//�ر�systick��ʱ��
	SysTick->CTRL &= ~(1<<0);
	//��ռ�����
	SysTick->VAL = 0x00;
}

//������ʱ
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

	