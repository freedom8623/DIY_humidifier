#include "interrupt.h"
#include "ws2812b.h"
#include "Menu.h"
//��ʱ��2�ж���Ҫ����ϵͳʱ��
//��ʱ��1ns
//��ʱ��1ns
unsigned int new_light_mode;
int T_Tick;
char  leddata[] = {000,256,000};
char  leddata2[] = {256,000,10};
int water_T = 0;
extern unsigned int DHT_T;
void timer2_int (void) interrupt 12
{
//	T_Tick ++;
//	
//	if(++water_T == 500) water_T = 0;
//	if(++DHT_T == 200) DHT_T = 0;
//	
//	//WS_SendData(&leddata2);


}


extern unsigned int Water_Flag;


void Alertor(void)
{

	
			if(Water_test == 1)
		{
			
//			leddata2[1] = new_light_mode;
			Water_Flag=1;
			WS_SendData(&leddata2);		
		}
		if(Water_test == 0)
		{
			Water_Flag=0;
			WS_SendData(&leddata);		
		}
}

//��ʱ��3�ж���Ҫ���ڰ����ж�
struct keys key[4] = {0,0,0};


//�������Ŷ���
sbit KEY1 = P3^2;
sbit KEY2 = P3^3;
sbit KEY3 = P3^4;
sbit KEY4 = P3^5;

void timer3_int(void) interrupt 19
{
	uchar i;
	
	    	//��һ����ȡ����״̬
			key[0].key_sta = KEY1;
			key[1].key_sta = KEY2;
			key[2].key_sta = KEY3;
			key[3].key_sta = KEY4;
	
		//����
		for(i = 0;i <4; i++)
		{
			switch(key[i].judge_sta)
			{
				case 0 :
				{
					//��һ����Ϊ������
				if(key[i].key_sta == 0)
					{
					key[i].judge_sta = 1;
					key[i].key_time = 0;
					
					}
				}
					break;
					
				case 1 :
				{
				//���key_sta == 0֤������ȷʵ������
				if(key[i].key_sta == 0)
					{
						key[i].judge_sta = 2;
						key[i].key_time++;
					}
				else
					{
					key[i].judge_sta = 0;
					}
				}
				break;
									
				case 2 :
				{
					//֤�����º�����
						if(key[i].key_sta == 1)
					{
						key[i].judge_sta = 0;
								//ȷ���Ƿ�Ϊ�̰�
						if(key[i].key_time<=100)
							{
							key[i].single_flag = 0;
							}else
							{
							key[i].longkey_flag = 1;
							}
						}
				break;
				}
									
			}				
	
	}
}