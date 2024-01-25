#include "init.h"
#include "string.h"
#include "cmd.h"
#include "uart.h"
#include "interrupt.h"

#define BUF_LEN 128
static u8 buf[BUF_LEN];//定义字符数组来存储从上位机读取到的字符串
static cmd_t *pcmd;

/*//定义时钟配置函数
//第一个参数:指定HSE分频系数:
//RCC_PLLSource_HSE_Div1:采用8MHz作为HSE时钟大小
//RCC_PLLSourse_HSE_DIV2:采用8/2=4MHz作为HSE时钟大小
//第二个参数:指定PLL倍频系数
//如果是9倍:RCC_PLLMul_9
void RCC_HSE_Config(u32 div,u32 pllm){
	//1.将RCC寄存器的值设置为默认值
	RCC_DeInit();
	//2.使用HSE外部时钟源,采用无源晶振,不用旁路
	RCC_HSEConfig(RCC_HSE_ON);
	//3.一旦HSE准备就绪就可以配置其他时钟
	if(RCC_WaitForHSEStartUp() == SUCCESS){
		//4.配置AHB总线时钟HCLK,1分频,HCLK=SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		//5.配置APB1总线时钟PCLK1,2分频,PCLK1=HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);
		//6.配置APB2总线时钟PCLK2,1分频,PCLK2=HCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//7.配置PLL的时钟源为HSE/2,并且配置PLL倍频系数为9,16...
		RCC_PLLConfig(div,pllm);
		//8.启动PLL,结果此时时钟路线:8MHz->PLL*9=PLLCLK=72Mz
		RCC_PLLCmd(ENABLE);
		//9.判断PLL是否准备继续,没有准备就绪死等
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		//10.选择PLLCLK作为SYSCLK时钟源:时钟路线:晶振8MHz->PLL*9=PLLCLK=72MHz->SYSCLK
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//11.判断确保SYSCLK一定是PLLCLK
		while(RCC_GetSYSCLKSource()!=0x08);	
	}
}*/

int main(void){
	/*//初始化HSE,PLL,PLLCLK,SYSCLK,HCLK,PCLK1,PCLK2
	RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);//SYSCLK=72MHz,CPU核时钟=FLCK=72MHz
  //RCC_HSE_Config(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9);//SYSCLK=36MHz,CPU核时钟=FLCK=36MHz
	//RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_16);//SYSCLK=128MHz,CPU核时钟=FLCK=128MHz*/
	
	//初始化硬件
	DEVICE_Init();
	//设置NVIC中断优先级分组,分两组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//主程序循环给上位机发送字符串
	while(1){
		//给上位机发送一个提示信息
		UART_Puts("\n please input command \n");
		//获取上位机发送过来的数据保存
		UART_Gets(buf,BUF_LEN);//buf="led on"/"led off"/"beep on"/"beep off"
		//根据用户从上位机输入的命令来实现下位机的硬件操作
		//给定一个命令的名称找命令,一旦找到命令,用pcmd保存命令的结构体首地址
		pcmd = find_cmd((char *)buf);
		if(pcmd != 0)
			pcmd->callback();
		else
			UART_Puts("invalid command\n");
		UART_Puts("\n");
			}
		}


