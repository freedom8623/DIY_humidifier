#ifndef __TIMER_H_
#define __TIMER_H_
//ͷ�ļ�
#include "stc8h.h"
#include "main.h"

//��ʱ����Ϊ�ж�
void    Timer2_init(void);

//�����ṹ��
struct keys
{
	uchar judge_sta;//�жϽ��е���һ��
	int key_sta;//���¼�¼Ϊ0
	uchar single_flag;//ȷ�ϰ�������Ϊ1
	int key_time;
	int longkey_falg;//������־λ
	
};
#endif