#include "Timer.h"




//��ʱ��2��ʼ��,���ڰ���
#define ET2 0x04
void    Timer2_init(void) //1ns @24Mhz
{
	P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��
	
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0x40;		//���ö�ʱ��ʼֵ
	T2H = 0xA2;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	
	IE2  |=  ET2;       //�����ж�
	EA = 1;//ʹ���ж�
} 



