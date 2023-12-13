#ifndef __EEPROM_H
#define __EEPROM_H

#include "../comm/STC8h.h"  //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "../comm/usb.h"     //USB���Լ���λ����ͷ�ļ�
#include "intrins.h"

void IapIdle();
char IapRead(unsigned long addr); 
void IapProgram(unsigned long addr, char dat);
void IapErase(unsigned long addr);


#endif

