#include "exti.h"
#include "led.h"
#include "beep.h"
#include "systick.h"
#include "key.h"

void My_Exti_Init(void){
	//定义EXTI结构体,用于配置EXTI控制器
	EXTI_InitTypeDef EXTI_Config;
	NVIC_InitTypeDef NVIC_Config;
	EXTI_InitTypeDef EXTI_Config1;
	//使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//将KEY0按键的引脚GPIOE4映射到EXTI4中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//配置EXTI工作参数
	EXTI_Config.EXTI_Line = EXTI_Line4|EXTI_Line3;
	EXTI_Config.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Config.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Config.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_Config);
	
	EXTI_Config1.EXTI_Line = EXTI_Line0;
	EXTI_Config1.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Config1.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Config1.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_Config1);
	
	//配置NVIC工作参数
	NVIC_Config.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Config.NVIC_IRQChannelSubPriority = 0;
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Config);
	
	NVIC_Config.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Config.NVIC_IRQChannelSubPriority = 1;
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Config);
	
	NVIC_Config.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Config.NVIC_IRQChannelSubPriority = 2;
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Config);
}

//自定义EXTI4中断处理函数 - 按键控制LED2开关
void EXTI4_IRQHandler(void){
	//判断是否由EXTI4触发中断
	if(EXTI_GetITStatus(EXTI_Line4) == SET){
		delay_ms(10);
		if(KEY0==0)
			LED2=!LED2;
	}
	//清除中断到来标志位,否则一直有中断
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI3_IRQHandler(void){
		if(EXTI_GetITStatus(EXTI_Line3) == SET){
		delay_ms(10);
		if(KEY1==0)		
			BEEP_On();
	}
	//清除中断到来标志位,否则一直有中断
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI0_IRQHandler(void){
		if(EXTI_GetITStatus(EXTI_Line0) == SET){
		delay_ms(10);
		if(KEYUP==1)
			BEEP_Off();
	}
	//清除中断到来标志位,否则一直有中断
	EXTI_ClearITPendingBit(EXTI_Line0);
}
