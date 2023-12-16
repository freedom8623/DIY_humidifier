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
                _nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();_nop_();
                LED = 0;
                Delayus(1);      
            }
            if(((tmpData>>(7-j)) & 0x01) == 1)
            {
                LED = 1;
                Delayus(1);	
                LED = 0;
                _nop_();_nop_();_nop_(); _nop_();_nop_();_nop_();_nop_();_nop_();
            }
        }
    }
		EA = 1;

		
}

void Delay300us()		//@24.000MHz
{
	unsigned char i, j;

	i = 10;
	j = 87;
	do
	{
		while (--j);
	} while (--i);
}


//void lightmode(unsigned int *new_light_mode)
//{
//	switch(*new_light_mode){
//		case 0:
//		WS_SendData(colorcode[0]);
//		break;
//	
//		case 1:
//		WS_SendData(colorcode[1]);
//		break;
//	
//		case 2:
//		WS_SendData(colorcode[2]);
//		break;
//	
//		case 3:
//		WS_SendData(colorcode[3]);
//		break;
//	
//		case 4:
//		WS_SendData(colorcode[4]);
//		break;
//	
//		case 5:
//		WS_SendData(colorcode[5]);
//		break;
//	}
//}
