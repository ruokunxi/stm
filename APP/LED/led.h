//led.h
#ifndef _LED_H
#define _LED_H

//������ͷ�ļ�
#include "stm32f10x.h"

//�������ֲ�������
extern void LED_Init(void);//��ʼ������
extern void LED_On(void);//���ƺ���
extern void LED_Off(void);//�صƺ���
extern void Delay(int n);//��ʱ����

//ͨ��λ������������LED0,LED1
//LED1 = 0,����;LED1 = 1,�ص�;
#define LED1 PBout(5)
#define LED2 PEout(5)



#endif


