#ifndef __DHT_H_
#define __DHT_H_

//ͷ�ļ�
#include "main.h"
//����DHT���ź��� P1^7
sbit DHT = P1^7;


//��ʱ����
void Delay20ms();
void Delay40us();

//��ʼ��ģ�飨���ģ���Ƿ���ڣ�ÿ�δ������ݶ�Ҫ��ʼ��
void DHT_Start();
void DHT11_Read();
#endif