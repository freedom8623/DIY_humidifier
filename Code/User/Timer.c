#include "Timer.h"




//定时器2初始化,用于按键
#define ET2 0x04
void    Timer2_init(void) //1ns @24Mhz
{
	P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能
	
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0x40;		//设置定时初始值
	T2H = 0xA2;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	
	IE2  |=  ET2;       //允许中断
	EA = 1;//使能中断
} 



