#ifndef _INIT_H
#define _INIT_H

//������ͷ�ļ�
#include "stm32f10x.h"
#include "system.h"

//����Ӳ����ʼ���ܺ���
extern void DEVICE_Init(void);

//��������ָ���������Ͳ���ȡ��ΪPINIIT_T,������������ı�����ָ�����Ӳ����ʼ������
typedef void (*PINIT_T)(void);

#endif
