#ifndef __DHT_H_
#define __DHT_H_

//头文件
#include "main.h"
//定义DHT的信号线 P1^7
sbit DHT = P1^7;


//延时函数
void Delay20ms();
void Delay40us();

//初始化模块（检测模块是否存在）每次传输数据都要初始化
void DHT_Start();
void DHT11_Read();
#endif