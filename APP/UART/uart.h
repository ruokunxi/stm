#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"
#include "system.h"

#define BOUND 115200 //波特率 - 串口1

extern void UART_Init(void); //串口1初始化函数
extern void UART_Putc(u8 c); //串口1发送字符函数
extern void UART_Puts(u8 *pstr); //串口1发送字符串函数
	
extern u8 UART_Getc(void);
extern void UART_Gets(u8 *buf,u32 len);
#endif