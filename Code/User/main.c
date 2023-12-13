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

//============��������===================

char  leddata[] = {000,000,000};
//============��������===================

void main(void)
{ 
	Buzzer = 0;//�رշ�����
	//LED = 1;
	
	Gpio_init();//GPIO��ʼ��
	
	Timer2_init();//��ʱ����ʼ��
	Timer3Init();

	//Pwm_init();//����pwm;ռ�ձ�50%
//	UpdatePwm();//����ռ�ձ�   //��PWM.C�и���ռ�ձ�ʹ�ò���Ƶ��Ϊ108khz
	
	//OLED��ʼ��
	OLED_Init();			//��ʼ��OLED 
	OLED_Clear();
	
	
	
	
	WS_SendData(&leddata);
	//Send_offled();
	//Send_offled();
	//��ؿ���
	EA = 1;     //�����ж�

	while(1)
	{
		//Send_offled();

		//LED = 0;

		DHT11_receive();//����ʵʱ�¶�
		//Display_Screen();
		Key_Proc();
			
		
		
	}
}





