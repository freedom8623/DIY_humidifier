#ifndef __KEY_H
#define __KEY_H

#include "../comm/STC8h.h"  //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "../comm/usb.h"     //USB���Լ���λ����ͷ�ļ�
sbit BEEP = P1^0;

unsigned char CDC_KeyRead(unsigned char dat);
unsigned char keyscan(void);

#endif 



