#include "cmd.h"
#include "led.h"
#include "beep.h"
#include "string.h"

//定义初始化函数硬件的命令结构体数组,每个成员保存着命令的信息
//将来咱们只需要维护此数组即可,main函数一个字都不用动
cmd_t cmd_tbl[]={
		{"led on",LED_On},    //开灯命令的信息
		{"led off",LED_Off},	//关灯命令的信息
		{"beep on",BEEP_On},  //开蜂鸣器命令的信息
		{"beep off",BEEP_Off},//关蜂鸣器命令的信息
};

//记录结构体数组元素个数
int cmd_num =sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);

//定义命令的查找函数,根据上位机发送来的命令名称在上面得数组中cmd_tbl找对应的
//命令结构体的首地址,并且返回命令的结构体首地址
cmd_t *find_cmd(char *name){
	int i;
	for(i = 0;i < cmd_num ; i++){
		if(!strcmp(name,cmd_tbl[i].name))
			return &cmd_tbl[i];
	}
	return 0;
}