//led.c
#include "led.h"

//定义函数
void LED_Init(void){
	GPIO_InitTypeDef GPIO_Config;
	//1.打开GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	//2.配置GPIOB为推挽输出,50MHz
	GPIO_Config.GPIO_Pin =GPIO_Pin_5;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Config.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_Config);
	GPIO_Init(GPIOE, &GPIO_Config);
	//输出高电平,默认关灯
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

//开灯函数
void LED_On(void){
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}

//关灯函数
void LED_Off(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

//延时函数
void Delay(int n){
	while(n--);
}


