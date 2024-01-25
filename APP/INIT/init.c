#include "init.h"
#include "led.h"
#include "beep.h"
#include "system.h"
#include "systick.h"//��ʱ��������
#include "key.h"
#include "exti.h"
#include "uart.h"

//�����ʼ������ָ�����鱣�����Ӳ���ĳ�ʼ������
//�Ժ�ά��Ӳ���ĳ�ʼ������ֻ��������鼴��,������mainһ���ֶ�����
//���:int init_func[] ...
static PINIT_T init_func[]={
	SysTick_Init, //�δ�ʱ����ʼ��
	LED_Init,     //LED��ʼ��
	BEEP_Init,		//��������ʼ��
	UART_Init,		//����1��ʼ��
	KEY_Init,			//������ʼ��
	My_Exti_Init,	//�ⲿ�жϳ�ʼ��
	0							//Ϊ���˳������forѭ��
};

//����Ӳ����ʼ������ں���
void DEVICE_Init(void){
	//���庯��ָ��������溯��ָ��������׵�ַ
	//���:int *pfunc = init_func
	PINIT_T *pfunc = init_func;


	//����������������Ӳ����ʼ��������������
	for(; *pfunc;pfunc++)
		(*pfunc)();//ע��:*��������ȼ����ں����Բ����,����ǰ����Ҫ��()
	}