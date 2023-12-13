#ifndef __TIM_H
#define __TIM_H

#include "../comm/STC8h.h"  //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "../comm/usb.h"     //USB���Լ���λ����ͷ�ļ�

extern u32 Sys_Time_10ms ;
#define Timer0_Reload   (MAIN_Fosc / 100)      //Timer 0 �ж�Ƶ��, 10��/�� 100hz���ٶ�
#define Timer1_Reload   (MAIN_Fosc / 100)      //Timer 1 �ж�Ƶ��, 2000��/��

void Timer0_init(void);
    
#endif

