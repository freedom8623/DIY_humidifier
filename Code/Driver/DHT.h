#ifndef _DHT11_H
#define _DHT11_H

#include <STC8H.H>      //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�

#define uchar unsigned char
#define uint unsigned int

sbit DHT=P1^7; //������
extern uchar rec_dat[9]; //��������


void DHT11_start();
uchar DHT11_rec_byte();      //����һ���ֽ�
void DHT11_receive();      //����40λ������

#endif