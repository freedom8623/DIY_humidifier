#include "Buzzer.h"
//水位/蜂鸣器（报警器）进程
char Water_Flag = 0;
//定时器1ns
int T_Tick;
void Alertor(void)
{
	if(T_Tick%500==0) Water_Flag = 1;
	else return;
	
	if(Water_Flag == 1)
	{	
			Water_Flag = 0;
			if(Water_test == 1)
		{
			if(T_Tick%500==0) Buzzer ^= 1;
		}
	
		}else
		{
				Buzzer = 0;
		}
}