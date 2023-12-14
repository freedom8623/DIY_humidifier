#include "Timer.h"




//��ʱ��2��ʼ��,
#define ET2 0x04
void    Timer2_init(void) //1ns @24Mhz
{
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0x30;		//���ö�ʱ��ʼֵ
	T2H = 0xF8;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	
	IE2  |=  ET2;       //�����ж�
	EA = 1;//ʹ���ж�
} 

#define ET3 0x20
//��ʱ��3��ʼ�����ڰ���
void Timer3Init(void)		//10����@24.000MHz
{
	T4T3M &= 0xFD;		//��ʱ��ʱ��12Tģʽ
	T3L = 0xE0;		//���ö�ʱ��ʼֵ
	T3H = 0xB1;		//���ö�ʱ��ʼֵ
	IE2  |=  ET3;       //�����ж�
	T4T3M |= 0x08;		//��ʱ��3��ʼ��ʱ
}


