#ifndef __PWM_H_
#define __PWM_H_
//ͷ�ļ�
#include "stc8h.h"
#include "main.h"

	
extern int PWM1_Duty;
extern int PWM2_Duty;

#define PWM1_1      0x00	//P:P1.0  N:P1.1����pwm�������1.1����

#define ENO1P       0x01
#define ENO1N       0x02

#define ENO2P       0x04
#define ENO2N       0x08


//ռ�ձ�
#define PWM_PERIOD  222    //��������ֵ

#define PWM1_off     222
#define PWM1_on     150
void Pwm_init(void);
//����PWM
void UpdatePwm(void);



#endif