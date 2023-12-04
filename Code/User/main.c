#include "main.h"
#include "Gpio.h"
#include "Timer.h"
#include "DHT.h"
#include "oled.h"

//蜂鸣器
sbit Buzzer = P3^7;
//水位检测引脚
sbit Water_test = P3^6;


sbit KEY1 = P3^2;
sbit KEY2 = P3^3;
sbit KEY3 = P3^4;
sbit KEY4 = P3^5;

//DHT11查询函数
void DHT_Read(void);
//按键函数
void Key_Proc(void);
//水位
void Alertor(void);


uchar i = 0;
//按键
struct keys key[4] = {0,0,0};
uchar Key_T = 0;
//按键的结构体 结构体在Timer.h
extern struct keys key[];

//定时器1ns
int T_Tick;//一毫米累加

void main(void)
{ 
	Gpio_init();//GPIO初始化
	Timer2_init();//定时器初始化
	DHT_Start();
	//OLED初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear()  	; 
	
	//相关开关
	EA = 1;     //打开总中断
	

	while(1)
	{
		Buzzer = 1;//测试蜂鸣器
		Key_Proc();
		DHT_Read();
		Alertor();
		
	}
}


//每500ms查询温湿度
char DHT_Read_Flag = 0;
void DHT_Read()
{
	if(T_Tick%500==0) DHT_Read_Flag = 1;
	else return;
	
	if(DHT_Read_Flag ==1)
	{
		DHT11_Read();
	}
}

//定时器中断
void timer2_int (void) interrupt 12
{
	T_Tick ++;
	if(T_Tick>10000) T_Tick = 0;
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
							key[i].longkey_falg = 1;
					}
				}
				break;
									
			}				
		}
}

//按键进程
void Key_Proc(void)
{
	if(key[0].single_flag == 1)
	{
		
		key[0].single_flag = 0;
	
	}
	
	 if(key[1].single_flag == 1)
	{
		
		key[1].single_flag = 0;
	
	}
	
	 if(key[2].single_flag == 1)
	{
		
		key[2].single_flag = 0;
	
	}
	
	if(key[3].single_flag == 1)
	{
		
		key[3].single_flag = 0;
	
	}
}

//蜂鸣器进程
char Water_Flag = 0;
void Alertor(void)
{
	if(T_Tick%500==0) Water_Flag = 1;
	else return;
	
	if(Water_test == 1)
	{
		Buzzer = 1;
		Water_Flag = 0;
	}else
	{
		Buzzer = 0;
	}
}

//测水位进程



