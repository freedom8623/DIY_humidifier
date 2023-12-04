#ifndef __TIMER_H_
#define __TIMER_H_
//头文件
#include "stc8h.h"
#include "main.h"

//定时器作为中断
void    Timer2_init(void);

//按键结构体
struct keys
{
	uchar judge_sta;//判断进行到哪一步
	int key_sta;//按下记录为0
	uchar single_flag;//确认按键按下为1
	int key_time;
	int longkey_falg;//长按标志位
	
};
#endif