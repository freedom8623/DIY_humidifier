#include "interrupt.h"
#include "Menu.h"
//定时器2中断主要用于系统时钟
//定时器1ns


void timer2_int (void) interrupt 12
{
	uchar i = 0;
	T_Tick ++;
	if(T_Tick>10000) T_Tick = 0;


}

//定时器3中断主要用于按键中断


struct keys key[4] = {0,0,0};
uchar Key_T = 0;

//按键引脚定义
sbit KEY1 = P3^2;
sbit KEY2 = P3^3;
sbit KEY3 = P3^4;
sbit KEY4 = P3^5;

void timer3_int(void) interrupt 19
{
	uchar i;
	Key_T++;
	if(Key_T>=10)
	{
    Key_T = 0;
	    	//第一步读取按键状态
			key[0].key_sta = KEY1;
			key[1].key_sta = KEY2;
			key[2].key_sta = KEY3;
			key[3].key_sta = KEY4;
	
		//遍历
		for(i = 0;i <4; i++)
		{
			switch(key[i].judge_sta)
			{
				case 0 :
				{
					//第一步是为了消抖
				if(key[i].key_sta == 0)
					{
					key[i].judge_sta = 1;
					key[i].key_time = 0;
					
					}
				}
					break;
					
				case 1 :
				{
				//如果key_sta == 0证明按键确实被按下
				if(key[i].key_sta == 0)
					{
						key[i].judge_sta = 2;

					}
				else
					{
					key[i].judge_sta = 0;
					}
				}
				break;
									
				case 2 :
				{
					//证明按下后松手
						if(key[i].key_sta == 1)
					{
						key[i].judge_sta = 0;
								//确定是否为短按
						if(key[i].key_time<=70)
							{
							key[i].single_flag = 1;
							}
						
					}
						else
					{
						key[i].key_time++;
						//判断如果按下时间大于70ms长按标志位置为1
						if(key[i].key_time>70)
							key[i].longkey_flag = 1;
					}
				}
				break;
									
			}				
		}
	
	}
}