//led.c
#include "led.h"

//���庯��
void LED_Init(void){
	GPIO_InitTypeDef GPIO_Config;
	//1.��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	//2.����GPIOBΪ�������,50MHz
	GPIO_Config.GPIO_Pin =GPIO_Pin_5;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Config.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_Config);
	GPIO_Init(GPIOE, &GPIO_Config);
	//����ߵ�ƽ,Ĭ�Ϲص�
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

//���ƺ���
void LED_On(void){
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}

//�صƺ���
void LED_Off(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

//��ʱ����
void Delay(int n){
	while(n--);
}


