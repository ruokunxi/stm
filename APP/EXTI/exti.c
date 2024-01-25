#include "exti.h"
#include "led.h"
#include "beep.h"
#include "systick.h"
#include "key.h"

void My_Exti_Init(void){
	//����EXTI�ṹ��,��������EXTI������
	EXTI_InitTypeDef EXTI_Config;
	NVIC_InitTypeDef NVIC_Config;
	EXTI_InitTypeDef EXTI_Config1;
	//ʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//��KEY0����������GPIOE4ӳ�䵽EXTI4�ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	//����EXTI��������
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
	
	//����NVIC��������
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

//�Զ���EXTI4�жϴ����� - ��������LED2����
void EXTI4_IRQHandler(void){
	//�ж��Ƿ���EXTI4�����ж�
	if(EXTI_GetITStatus(EXTI_Line4) == SET){
		delay_ms(10);
		if(KEY0==0)
			LED2=!LED2;
	}
	//����жϵ�����־λ,����һֱ���ж�
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI3_IRQHandler(void){
		if(EXTI_GetITStatus(EXTI_Line3) == SET){
		delay_ms(10);
		if(KEY1==0)		
			BEEP_On();
	}
	//����жϵ�����־λ,����һֱ���ж�
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI0_IRQHandler(void){
		if(EXTI_GetITStatus(EXTI_Line0) == SET){
		delay_ms(10);
		if(KEYUP==1)
			BEEP_Off();
	}
	//����жϵ�����־λ,����һֱ���ж�
	EXTI_ClearITPendingBit(EXTI_Line0);
}
