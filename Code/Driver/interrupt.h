#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_
//������ʱ��
extern int T_Tick;//һ�����ۼ�
//���ͷ�ļ�
#include "stc8h.h"                 //STC8A8K��Ƭ��ͷ�ļ�
#include "main.h"
//�����ṹ��

//�����Ľṹ�� �ṹ����mian.h
extern struct keys key[];

//�����ṹ��
struct keys
{
	uchar judge_sta;//�жϽ��е���һ��
	int key_sta;//���¼�¼Ϊ0
	uchar single_flag;//ȷ�ϰ�������Ϊ1
	int key_time;
	int longkey_flag;//������־λ
	
};
#endif
