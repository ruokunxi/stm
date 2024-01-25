#ifndef _CMD_H
#define _CMD_H

//包含总头文件
#include "stm32f10x.h"
#include "system.h"

//声明函数指针数据类型并且取别名叫cb_t
typedef void (*cb_t)(void);

//声明描述命令属性的结构体数据类型并且取别名叫cmd_t
typedef struct _cmd {
	char *name;//描述命令的名称,例如:"led on"
	cb_t callback;//描述命令对应的处理函数,例如:LED_On()
}cmd_t;

//声明根据命令名称找对应命令结构体变量的函数,一旦找到返回命令对应的结构体变量的首地址
extern cmd_t *find_cmd(char *name);

#endif
