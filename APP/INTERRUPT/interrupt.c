#include "interrupt.h"
//���崮��1�������ݵĳ���
u32 UART_RxCounter = 0;
//���崮��1���ջ�����,�����ڴ��ݴ��յ�������
u8 UART_RxBuff[UART_RXBUFF_SIZE];
//�������������ɵı�־λ,����������,���Խ����յ������ݴ��ݸ���λ��
//0-��λ�����͹����������ַ�����û�н������
//1-��ʾ�������,���Է��͸���λ��������
u8 UART_Send_Flag=0;

//���崮��1�жϴ�����
void USART1_IRQHandler(void){
	u8 c;
	//�ж��Ƿ��Ǵ���1�Ľ������ݲ������ж�
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
		//����жϵ���λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		//��ȡ���յ�������
		c = USART_ReceiveData(USART1);
		//����ȡ���������ݴ浽��Ĵ洢��
		UART_RxBuff[UART_RxCounter++]=c;
		//��λ����SSCOM���߷��͵��ַ���:"led on\r\n\0"
		if(c=='\n'){//��Ϊ�Ѿ�������
			//��ʱRxCounterΪ\0�ַ����±�
			UART_RxBuff[UART_RxCounter-2]='\0';
			UART_RxCounter=0;
			//��ʾ��λ�����͵������Ѿ��������,���Խ����ܵ�����ظ���λ��
			UART_Send_Flag = 1;
		}
		
	}
}