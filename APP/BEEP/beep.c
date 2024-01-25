//beef.c
#include "beep.h"

void BEEP_Init(void){
	GPIO_InitTypeDef GPIO_Config; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_Config.GPIO_Pin = GPIO_Pin_8;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Config.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_Config);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}
void BEEP_On(void){
	GPIO_SetBits (GPIOB,GPIO_Pin_8);
}
void BEEP_Off(void){
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

