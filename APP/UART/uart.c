#include "uart.h"

//串口1初始化函数
void UART_Init(void){
	//配置串口1 GPIO
	GPIO_InitTypeDef GPIO_Config;
	//配置串口1控制器
	USART_InitTypeDef UART_Config;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//配置PA9引脚 - 发送 - 推挽复用
	GPIO_Config.GPIO_Pin = GPIO_Pin_9;//第9个引脚
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;//推挽复用
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;//最大输出速度
	GPIO_Init(GPIOA,&GPIO_Config);
	
	//配置PA10引脚 - 接收 - 浮空输入
	GPIO_Config.GPIO_Pin = GPIO_Pin_10;//第10个引脚
	GPIO_Config.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA,&GPIO_Config);
	
	//配置UART1的控制器
	UART_Config.USART_BaudRate = BOUND;//115200 - 波特率
	UART_Config.USART_WordLength = USART_WordLength_8b;//数据位8位
	UART_Config.USART_StopBits = USART_StopBits_1;//停止位1位
	UART_Config.USART_Parity = USART_Parity_No;//不校验
	UART_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不采用硬件流控制
	UART_Config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//使能发送和接收
	USART_Init(USART1,&UART_Config);
	
	//使能串口1
	USART_Cmd(USART1,ENABLE);
	
	//对于NVIC控制器的配置
	NVIC_InitTypeDef NVIC_Config;
	NVIC_Config.NVIC_IRQChannel = USART1_IRQn;//指定串口1的中断通道
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;//抢占式优先级为2
	NVIC_Config.NVIC_IRQChannelSubPriority = 3;//指定响应式优先级为3
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;//打开串口1的中断通道
	NVIC_Init(&NVIC_Config);
	
	//开启串口1的接收中断功能
	//当UART1控制器接收到数据后会给CPU核发送一个中断信号
	//通知CPU核数据准备就绪,让其读取数据
	//CPU核读取结束,再回到被打断的位置继续执行
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

//串口1发送字符函数
void UART_Putc(u8 c){
	//判断发送数据寄存器
	//有数据,轮询死等;没有数据,发送
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	//发送数据 - 就是将c放到了发送数据寄存器中
	USART_SendData(USART1,c);
}

//串口1发送字符串函数
void UART_Puts(u8 *pstr){
	while(*pstr){
		UART_Putc(*pstr);
		pstr++;
	}
}

//接收字符函数
u8 UART_Getc(void){
	//判断接收数据寄存器是否非空
	//空 - 轮询等待 - RESET
	//非空 - 读取数据 - SET
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	
	return (u8)USART_ReceiveData(USART1);
}

//接收字符串函数
//u8-char
//char buf[32];
void UART_Gets(u8 *buf,u32 len){
	int i;
	for(i=0;i<len-1;i++){
		buf[i]=UART_Getc();
		if(buf[i]=='\n')
			break;
	}
	//此时buf[i-1]='\r'
	//上位机串口工具发送过来的字符串格式-"hello\r\n"
	buf[i-1]='\0';//表示字符串的结束
}
