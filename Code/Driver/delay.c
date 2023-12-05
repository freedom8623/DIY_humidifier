#include "delay.h"
#include "intrins.h"
void Delay_ms(unsigned int xms)		//@24.000MHz
{
	unsigned char i, j;
	while(xms--)
	{
		

	_nop_();
	i = 32;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}
}


	
