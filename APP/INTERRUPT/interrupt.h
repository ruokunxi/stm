#ifndef _INTERRUPT_H
#define _INTERRUPT_H


#include "stm32f10x.h"
#include "system.h"

#define  UART_RXBUFF_SIZE 1024// 执行串口1接收缓冲区的大小

extern u32 UART_RxCounter;//记录串口1接收数据的长度

extern u8 UART_RxBuff[UART_RXBUFF_SIZE];//指定串口1接收缓冲区大小

extern u8 UART_Send_Flag;//串口1接收数据完成的标志与此同时可以将接收到的数据发送给上位机做回显


#endif