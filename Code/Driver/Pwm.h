#ifndef __PWM_H_
#define __PWM_H_
//头文件
#include "stc8h.h"
#include "main.h"

	
extern int PWM1_Duty;
extern int PWM2_Duty;

#define PWM1_1      0x00	//P:P1.0  N:P1.1定义pwm输出引脚1.1雾化器
#define PWM2_2      0x04	//P:P2.2  N:P2.3定义PWM输出引脚P 2.3 三色灯

#define ENO1P       0x01
#define ENO1N       0x02

#define ENO2P       0x04
#define ENO2N       0x08


//占空比


void Pwm_init(void);
//更新PWM
void UpdatePwm(void);
//设置PWM1占空比
void Setting_Pwm(u16 Duty1);


#endif