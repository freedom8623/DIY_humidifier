#include "DHT.h"


//单总线传输
//延时函数


void Delay20ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 211;
	k = 231;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay40us()		//@24.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 237;
	while (--i);
}




char datas[5]; 		//数组分别代表，湿度，湿度小数，温度，温度小数，校验
//初始化模块（检测模块是否存在）每次传输数据都要初始化
void DHT_Start()
{
	
    DHT = 1;		//对应初始化时序start
    DHT = 0;
    Delay20ms();
	  DHT=1;
		while(DHT);
		while(!DHT);
		while(DHT);

}

void DHT11_Read()
{
	char value = 0;
	char flag;
	char i = 0;
	char j = 0;
	DHT_Start();
	for(j = 0;j<5;j++)//分别读取五组数据
	{			
		for(i=0;i<8;i++)//每组八位分别处理
		{		
			while(!DHT);		//高电平开始计时
			Delay40us();
			if(DHT == 1)  //如果还为高则是“1”
			{		
				flag = 1;
				while(DHT);
			}
			 else       //否则“0”
			{				
				flag = 0;
			}
			value = value << 1;		//移位
			value |= flag; 			//赋值
		}
		datas[j] = value;			//赋值
	}

}


