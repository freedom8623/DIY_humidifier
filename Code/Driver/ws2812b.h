#ifndef __WS2812B_H
#define __WS2812B_H

#include "intrins.h"
#include "main.h"
#include "stc8h.h"
sbit LED = P2^3;

void WS_SendData(char *_data);
void Send_offled(void);

#endif