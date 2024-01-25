#include "uart.h"

//����1��ʼ������
void UART_Init(void){
	//���ô���1 GPIO
	GPIO_InitTypeDef GPIO_Config;
	//���ô���1������
	USART_InitTypeDef UART_Config;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//����PA9���� - ���� - ���츴��
	GPIO_Config.GPIO_Pin = GPIO_Pin_9;//��9������
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;//���츴��
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;//�������ٶ�
	GPIO_Init(GPIOA,&GPIO_Config);
	
	//����PA10���� - ���� - ��������
	GPIO_Config.GPIO_Pin = GPIO_Pin_10;//��10������
	GPIO_Config.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA,&GPIO_Config);
	
	//����UART1�Ŀ�����
	UART_Config.USART_BaudRate = BOUND;//115200 - ������
	UART_Config.USART_WordLength = USART_WordLength_8b;//����λ8λ
	UART_Config.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ
	UART_Config.USART_Parity = USART_Parity_No;//��У��
	UART_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//������Ӳ��������
	UART_Config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܷ��ͺͽ���
	USART_Init(USART1,&UART_Config);
	
	//ʹ�ܴ���1
	USART_Cmd(USART1,ENABLE);
	
	//����NVIC������������
	NVIC_InitTypeDef NVIC_Config;
	NVIC_Config.NVIC_IRQChannel = USART1_IRQn;//ָ������1���ж�ͨ��
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;//��ռʽ���ȼ�Ϊ2
	NVIC_Config.NVIC_IRQChannelSubPriority = 3;//ָ����Ӧʽ���ȼ�Ϊ3
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;//�򿪴���1���ж�ͨ��
	NVIC_Init(&NVIC_Config);
	
	//��������1�Ľ����жϹ���
	//��UART1���������յ����ݺ���CPU�˷���һ���ж��ź�
	//֪ͨCPU������׼������,�����ȡ����
	//CPU�˶�ȡ����,�ٻص�����ϵ�λ�ü���ִ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

//����1�����ַ�����
void UART_Putc(u8 c){
	//�жϷ������ݼĴ���
	//������,��ѯ����;û������,����
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	//�������� - ���ǽ�c�ŵ��˷������ݼĴ�����
	USART_SendData(USART1,c);
}

//����1�����ַ�������
void UART_Puts(u8 *pstr){
	while(*pstr){
		UART_Putc(*pstr);
		pstr++;
	}
}

//�����ַ�����
u8 UART_Getc(void){
	//�жϽ������ݼĴ����Ƿ�ǿ�
	//�� - ��ѯ�ȴ� - RESET
	//�ǿ� - ��ȡ���� - SET
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	
	return (u8)USART_ReceiveData(USART1);
}

//�����ַ�������
//u8-char
//char buf[32];
void UART_Gets(u8 *buf,u32 len){
	int i;
	for(i=0;i<len-1;i++){
		buf[i]=UART_Getc();
		if(buf[i]=='\n')
			break;
	}
	//��ʱbuf[i-1]='\r'
	//��λ�����ڹ��߷��͹������ַ�����ʽ-"hello\r\n"
	buf[i-1]='\0';//��ʾ�ַ����Ľ���
}
