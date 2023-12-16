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


 

//============变量定义===================
unsigned int new_light_mode;
void main(void)
{ 
	Buzzer = 0;//关闭蜂鸣器
	
	Gpio_init();//GPIO初始化
	Timer2_init();//定时器初始化
	Timer3Init();

	Pwm_init();//产生pwm;占空比50%
  UpdatePwm();//更新占空比   //在PWM.C中更改占空比使得产生频率为108khz
	
	//OLED初始化
	OLED_Init();			//初始化OLED 
	OLED_Clear();

	//相关开关
	EA = 1;     //打开总中断

	while(1)
	{
		Key_Proc();
		Alertor(new_light_mode);
		DHT11_receive();//接收实时温度
		
		
	}
	
}





