#include "interrupt.h"
//定义串口1接收数据的长度
u32 UART_RxCounter = 0;
//定义串口1接收缓冲区,分配内存暂存收到的数据
u8 UART_RxBuff[UART_RXBUFF_SIZE];
//定义接收数据完成的标志位,如果接收完毕,可以将接收到的数据传递给上位机
//0-上位机发送过来的命令字符串还没有接受完毕
//1-表示接收完毕,可以发送给上位机做回显
u8 UART_Send_Flag=0;

//定义串口1中断处理函数
void USART1_IRQHandler(void){
	u8 c;
	//判断是否是串口1的接收数据产生的中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
		//清除中断到来位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		//读取接收到的数据
		c = USART_ReceiveData(USART1);
		//将读取到的数据暂存到大的存储区
		UART_RxBuff[UART_RxCounter++]=c;
		//上位机的SSCOM工具发送的字符串:"led on\r\n\0"
		if(c=='\n'){//认为已经读完了
			//此时RxCounter为\0字符的下标
			UART_RxBuff[UART_RxCounter-2]='\0';
			UART_RxCounter=0;
			//表示上位机发送的命令已经接收完毕,可以将接受的命令返回给上位机
			UART_Send_Flag = 1;
		}
		
	}
}