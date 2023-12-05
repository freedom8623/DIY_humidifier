#ifndef _OLED_H
#define _OLED_H

#include "iic.h"
#include "delay.h"
#include "font.h"
#include "stc8h.h"       //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�


void oled_IIC_SendCommand(unsigned char IIC_Command);//д����
void oled_IIC_SendData(unsigned char IIC_Data);//д����
void oled_Init(void);//OLED��ʼ��
void oled_Display_ON(void);//����ʾ
void oled_Display_OFF(void);//����ʾ
void oled_Allfill(unsigned char fill_Data);//���ȫ������
void oled_clear(void);//�����ʾ
void oled_SetPos(unsigned char x,unsigned char y);//������ʼ������

unsigned int oled_Pow(unsigned char m,unsigned char n);//����m^n
void oled_ShowNum(unsigned char x,unsigned char y,int num,unsigned char len,unsigned char size);//��ʾ����
void oled_ShowChar(unsigned char x,unsigned char y,unsigned char ch,unsigned char size);//��ʾ�ַ�
void oled_ShowStr(unsigned char x,unsigned char y,const unsigned char *p,unsigned char size);//��ʾ�ַ���
void oled_ShowCN(unsigned char x,unsigned char y,unsigned char bit_temp);//��ʾ����
void oled_ShowBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//��ʾͼƬ

#endif
