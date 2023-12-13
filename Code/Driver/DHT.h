#ifndef _DHT11_H
#define _DHT11_H

#include <STC8H.H>      //包含此头文件后，不需要再包含"reg51.h"头文件

#define uchar unsigned char
#define uint unsigned int

sbit DHT=P1^7; //数据线
extern uchar rec_dat[9]; //储存数据


void DHT11_start();
uchar DHT11_rec_byte();      //接收一个字节
void DHT11_receive();      //接收40位的数据

#endif