#ifndef _CMD_H
#define _CMD_H

//������ͷ�ļ�
#include "stm32f10x.h"
#include "system.h"

//��������ָ���������Ͳ���ȡ������cb_t
typedef void (*cb_t)(void);

//���������������ԵĽṹ���������Ͳ���ȡ������cmd_t
typedef struct _cmd {
	char *name;//�������������,����:"led on"
	cb_t callback;//���������Ӧ�Ĵ�����,����:LED_On()
}cmd_t;

//�����������������Ҷ�Ӧ����ṹ������ĺ���,һ���ҵ����������Ӧ�Ľṹ��������׵�ַ
extern cmd_t *find_cmd(char *name);

#endif
