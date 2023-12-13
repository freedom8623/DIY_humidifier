#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_
//定义主时钟
extern int T_Tick;//一毫米累加
//添加头文件
#include "stc8h.h"                 //STC8A8K单片机头文件
#include "main.h"
//按键结构体

//按键的结构体 结构体在mian.h
extern struct keys key[];

//按键结构体
struct keys
{
	uchar judge_sta;//判断进行到哪一步
	int key_sta;//按下记录为0
	uchar single_flag;//确认按键按下为1
	int key_time;
	int longkey_flag;//长按标志位
	
};
#endif
