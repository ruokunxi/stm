//key.h
#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"
#include "system.h"

#define KEY0_PIN GPIO_Pin_4 //key0����
#define KEY1_PIN GPIO_Pin_3 //key1
#define KEY2_PIN GPIO_Pin_2 //key2
#define KEYUP_PIN GPIO_Pin_0//keyup

#define KEY_PORT GPIOE//KEY0������������E��
#define KEYUP_PORT GPIOA

#define KEY0 PEin(4)//KEY0 - GPIOE4 - ���Ÿߵ͵�ƽ
#define KEY1 PEin(3)
#define KEY2 PEin(2)
#define KEYUP PAin(0)

#define KEY0_PRESS 1//KEY0�����ļ�ֵ
#define KEY1_PRESS 2
#define KEY2_PRESS 3
#define KEYUP_PRESS 4 

extern void KEY_Init(void);//��ʼ������
extern void KEYUP_Init(void);
extern u8 KEY_Scan(void);//ɨ��,�жϰ����Ƿ���


#endif