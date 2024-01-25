#include "cmd.h"
#include "led.h"
#include "beep.h"
#include "string.h"

//�����ʼ������Ӳ��������ṹ������,ÿ����Ա�������������Ϣ
//��������ֻ��Ҫά�������鼴��,main����һ���ֶ����ö�
cmd_t cmd_tbl[]={
		{"led on",LED_On},    //�����������Ϣ
		{"led off",LED_Off},	//�ص��������Ϣ
		{"beep on",BEEP_On},  //���������������Ϣ
		{"beep off",BEEP_Off},//�ط������������Ϣ
};

//��¼�ṹ������Ԫ�ظ���
int cmd_num =sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);

//��������Ĳ��Һ���,������λ�������������������������������cmd_tbl�Ҷ�Ӧ��
//����ṹ����׵�ַ,���ҷ�������Ľṹ���׵�ַ
cmd_t *find_cmd(char *name){
	int i;
	for(i = 0;i < cmd_num ; i++){
		if(!strcmp(name,cmd_tbl[i].name))
			return &cmd_tbl[i];
	}
	return 0;
}