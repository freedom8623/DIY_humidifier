#ifndef _IIC_H
#define _IIC_H

#include "stc8h.h"       //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "intrins.h"

/*����ͨ���궨���������IICЭ�������ߵ�״̬�仯*/
#define IIC_SDA_H P14=1
#define IIC_SDA_L P14=0
#define IIC_SCL_H P15=1
#define IIC_SCL_L P15=0
#define IIC_SDA_READ	P32

void iic_Init(void);//IO�˿ڳ�ʼ��
void iic_Start(void);//IIC�Ŀ�ʼ�źź���
void iic_Stop(void);//IIC�Ľ����źź���
void iic_Ack(void);//IIC��Ӧ���źź���
void iic_NAck(void);//IIC�ķ�Ӧ���źź���
unsigned char iic_Wait_Ack(void);//IIC�ĵȴ�Ӧ���źź���
void iic_SendData(unsigned char dat);//IIC�ķ����ֽں���
unsigned char iic_ReadData(void);//IIC�Ķ�ȡ�ֽں���

#endif