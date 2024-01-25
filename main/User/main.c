#include "init.h"
#include "string.h"
#include "cmd.h"
#include "uart.h"
#include "interrupt.h"

#define BUF_LEN 128
static u8 buf[BUF_LEN];//�����ַ��������洢����λ����ȡ�����ַ���
static cmd_t *pcmd;

/*//����ʱ�����ú���
//��һ������:ָ��HSE��Ƶϵ��:
//RCC_PLLSource_HSE_Div1:����8MHz��ΪHSEʱ�Ӵ�С
//RCC_PLLSourse_HSE_DIV2:����8/2=4MHz��ΪHSEʱ�Ӵ�С
//�ڶ�������:ָ��PLL��Ƶϵ��
//�����9��:RCC_PLLMul_9
void RCC_HSE_Config(u32 div,u32 pllm){
	//1.��RCC�Ĵ�����ֵ����ΪĬ��ֵ
	RCC_DeInit();
	//2.ʹ��HSE�ⲿʱ��Դ,������Դ����,������·
	RCC_HSEConfig(RCC_HSE_ON);
	//3.һ��HSE׼�������Ϳ�����������ʱ��
	if(RCC_WaitForHSEStartUp() == SUCCESS){
		//4.����AHB����ʱ��HCLK,1��Ƶ,HCLK=SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//5.����APB1����ʱ��PCLK1,2��Ƶ,PCLK1=HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);
		//6.����APB2����ʱ��PCLK2,1��Ƶ,PCLK2=HCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//7.����PLL��ʱ��ԴΪHSE/2,��������PLL��Ƶϵ��Ϊ9,16...
		RCC_PLLConfig(div,pllm);
		//8.����PLL,�����ʱʱ��·��:8MHz->PLL*9=PLLCLK=72Mz
		RCC_PLLCmd(ENABLE);
		//9.�ж�PLL�Ƿ�׼������,û��׼����������
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		//10.ѡ��PLLCLK��ΪSYSCLKʱ��Դ:ʱ��·��:����8MHz->PLL*9=PLLCLK=72MHz->SYSCLK
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//11.�ж�ȷ��SYSCLKһ����PLLCLK
		while(RCC_GetSYSCLKSource()!=0x08);	
	}
}*/

int main(void){
	/*//��ʼ��HSE,PLL,PLLCLK,SYSCLK,HCLK,PCLK1,PCLK2
	RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);//SYSCLK=72MHz,CPU��ʱ��=FLCK=72MHz
  //RCC_HSE_Config(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9);//SYSCLK=36MHz,CPU��ʱ��=FLCK=36MHz
	//RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_16);//SYSCLK=128MHz,CPU��ʱ��=FLCK=128MHz*/
	
	//��ʼ��Ӳ��
	DEVICE_Init();
	//����NVIC�ж����ȼ�����,������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//������ѭ������λ�������ַ���
	while(1){
		//����λ������һ����ʾ��Ϣ
		UART_Puts("\n please input command \n");
		//��ȡ��λ�����͹��������ݱ���
		UART_Gets(buf,BUF_LEN);//buf="led on"/"led off"/"beep on"/"beep off"
		//�����û�����λ�������������ʵ����λ����Ӳ������
		//����һ�����������������,һ���ҵ�����,��pcmd��������Ľṹ���׵�ַ
		pcmd = find_cmd((char *)buf);
		if(pcmd != 0)
			pcmd->callback();
		else
			UART_Puts("invalid command\n");
		UART_Puts("\n");
			}
		}


