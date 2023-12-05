#ifndef _IIC_H
#define _IIC_H

#include "stc8h.h"       //包含此头文件后，不需要再包含"reg51.h"头文件
#include "intrins.h"

/*这里通过宏定义更能体现IIC协议的相关线的状态变化*/
#define IIC_SDA_H P14=1
#define IIC_SDA_L P14=0
#define IIC_SCL_H P15=1
#define IIC_SCL_L P15=0
#define IIC_SDA_READ	P32

void iic_Init(void);//IO端口初始化
void iic_Start(void);//IIC的开始信号函数
void iic_Stop(void);//IIC的结束信号函数
void iic_Ack(void);//IIC的应答信号函数
void iic_NAck(void);//IIC的非应答信号函数
unsigned char iic_Wait_Ack(void);//IIC的等待应答信号函数
void iic_SendData(unsigned char dat);//IIC的发送字节函数
unsigned char iic_ReadData(void);//IIC的读取字节函数

#endif