#ifndef __RTC_H
#define __RTC_H

#include "../comm/STC8h.h"  //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "../comm/usb.h"     //USB���Լ���λ����ͷ�ļ�
#include "intrins.h"
#include "stdio.h"


extern xdata u8 B1S_Flag;

void RTC_config(void);


#endif


