#include "main.h"
#include "Gpio.h"
#include "Timer.h"
#include "DHT.h"
#include "Pwm.h"
#include "oled.h"
#include "stdio.h"
#include "interrupt.h"
#include "ws2812b.h"
#include "Menu.h"
#include "Buzzer.h"

 

//=========================================

//============函数定义===================

char  leddata[] = {000,000,000};
//============变量定义===================

void main(void)
{ 
	Buzzer = 0;//关闭蜂鸣器
	//LED = 1;
	
	Gpio_init();//GPIO初始化
	
	Timer2_init();//定时器初始化
	Timer3Init();

	//Pwm_init();//产生pwm;占空比50%
//	UpdatePwm();//更新占空比   //在PWM.C中更改占空比使得产生频率为108khz
	
	//OLED初始化
	OLED_Init();			//初始化OLED 
	OLED_Clear();
	
	
	
	
	WS_SendData(&leddata);
	//Send_offled();
	//Send_offled();
	//相关开关
	EA = 1;     //打开总中断

	while(1)
	{
		//Send_offled();

		//LED = 0;

		DHT11_receive();//接收实时温度
		//Display_Screen();
		Key_Proc();
			
		
		
	}
}





