#include "key.h"
#include "systick.h"

void KEY_Init(void){
	GPIO_InitTypeDef GPIO_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_Config.GPIO_Pin = KEY0_PIN|KEY1_PIN|KEY2_PIN;
	GPIO_Config.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PORT,&GPIO_Config);

	GPIO_InitTypeDef GPIO_Config1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Config1.GPIO_Pin = KEYUP_PIN;
	GPIO_Config1.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEYUP_PORT,&GPIO_Config1);
} 
//定义按键扫描函数
u8 KEY_Scan(void){  
	//ispressed=0按键没按下
	//ispressed=1按键按下
	static u8 ispressed = 0;
	if(((KEY0==0)||(KEYUP==1)||(KEY1==0)||(KEY2==0))&&(ispressed==0)){
		delay_ms(10);//消除抖动  
		ispressed=1;
		if(KEY0==0)
			return KEY0_PRESS;//返回KEY0按键的键值1
		else if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
		else if(KEYUP==1)
			return KEYUP_PRESS;
	}else if(KEY0==1||KEY1==1||KEY2==1||KEYUP==0){//表示按键松开
		ispressed=0;
	}
	return 0;
}