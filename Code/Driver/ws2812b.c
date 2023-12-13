#include "ws2812b.h"


void Delayus(int a)		//@24.000MHz
{
	unsigned char i;
	while(a--)
		{
	i = 6;
	while (--i);
	}
}

void WS_SendData(uchar *_data)
{
    uchar i = 0;
    uchar j = 0;
		uchar *p = (uchar*)_data;
	
		EA = 0;
    for (i = 0; i < 3; i++)
    {
        uchar tmpData;
				tmpData = *(p++);
        for (j = 0; j < 8; j++)
        {
            if (((tmpData>>(7-j)) & 0x01) == 0)
            {
                LED = 1;
                _nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_(); _nop_();
                LED = 0;
                Delayus(1);      
            }
            else
            {
                LED = 1;
                Delayus(1);	
                LED = 0;
                _nop_();_nop_();_nop_(); _nop_();_nop_();_nop_();_nop_(); _nop_();
            }
        }
    }
		EA = 1;

		
}
void Delay60us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 220;
	do
	{
		while (--j);
	} while (--i);
}
void Delay280us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 9;
	j = 183;
	do
	{
		while (--j);
	} while (--i);
}

void Send_offled(void)
{
	char OFFValue = {0,0,0};
	WS_SendData(&OFFValue);	

	LED = 0;
	
	Delay280us();
}
