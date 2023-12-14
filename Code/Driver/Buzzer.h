#ifndef __BEZZER_H_
#define __BEEZER_H_

#include "main.h"
#include "ws2812b.h"
//============引脚定义===================
//蜂鸣器引脚定义
sbit Buzzer = P3^7;

//水位检测引脚定义
sbit Water_test = P3^6;



void Alertor(void);//水位检测
	
#endif