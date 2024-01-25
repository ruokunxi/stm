#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"
#include "system.h"

#define BOUND 115200 //������ - ����1

extern void UART_Init(void); //����1��ʼ������
extern void UART_Putc(u8 c); //����1�����ַ�����
extern void UART_Puts(u8 *pstr); //����1�����ַ�������
	
extern u8 UART_Getc(void);
extern void UART_Gets(u8 *buf,u32 len);
#endif