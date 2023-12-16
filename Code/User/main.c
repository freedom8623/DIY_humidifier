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


 

//============��������===================
unsigned int new_light_mode;
void main(void)
{ 
	Buzzer = 0;//�رշ�����
	
	Gpio_init();//GPIO��ʼ��
	Timer2_init();//��ʱ����ʼ��
	Timer3Init();

	Pwm_init();//����pwm;ռ�ձ�50%
  UpdatePwm();//����ռ�ձ�   //��PWM.C�и���ռ�ձ�ʹ�ò���Ƶ��Ϊ108khz
	
	//OLED��ʼ��
	OLED_Init();			//��ʼ��OLED 
	OLED_Clear();

	//��ؿ���
	EA = 1;     //�����ж�

	while(1)
	{
		Key_Proc();
		Alertor(new_light_mode);
		DHT11_receive();//����ʵʱ�¶�
		
		
	}
	
}





