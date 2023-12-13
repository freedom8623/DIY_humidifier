#include "Timer.h"




//定时器2初始化,
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

#define ET3 0x20
//定时器3初始化用于按键
void Timer3Init(void)		//1毫秒@24.000MHz
{
	T4T3M |= 0x02;		//定时器时钟1T模式
	T3L = 0x40;		//设置定时初始值
	T3H = 0xA2;		//设置定时初始值
	IE2  |=  ET3;       //允许中断
	T4T3M |= 0x08;		//定时器3开始计时
}


