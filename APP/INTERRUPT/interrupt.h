#ifndef _INTERRUPT_H
#define _INTERRUPT_H


#include "stm32f10x.h"
#include "system.h"

#define  UART_RXBUFF_SIZE 1024// ִ�д���1���ջ������Ĵ�С

extern u32 UART_RxCounter;//��¼����1�������ݵĳ���

extern u8 UART_RxBuff[UART_RXBUFF_SIZE];//ָ������1���ջ�������С

extern u8 UART_Send_Flag;//����1����������ɵı�־���ͬʱ���Խ����յ������ݷ��͸���λ��������


#endif