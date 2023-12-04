#include "main.h"
#include "Gpio.h"
#include "Timer.h"
#include "DHT.h"
#include "oled.h"

//������
sbit Buzzer = P3^7;
//ˮλ�������
sbit Water_test = P3^6;


sbit KEY1 = P3^2;
sbit KEY2 = P3^3;
sbit KEY3 = P3^4;
sbit KEY4 = P3^5;

//DHT11��ѯ����
void DHT_Read(void);
//��������
void Key_Proc(void);
//ˮλ
void Alertor(void);


uchar i = 0;
//����
struct keys key[4] = {0,0,0};
uchar Key_T = 0;
//�����Ľṹ�� �ṹ����Timer.h
extern struct keys key[];

//��ʱ��1ns
int T_Tick;//һ�����ۼ�

void main(void)
{ 
	Gpio_init();//GPIO��ʼ��
	Timer2_init();//��ʱ����ʼ��
	DHT_Start();
	//OLED��ʼ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear()  	; 
	
	//��ؿ���
	EA = 1;     //�����ж�
	

	while(1)
	{
		Buzzer = 1;//���Է�����
		Key_Proc();
		DHT_Read();
		Alertor();
		
	}
}


//ÿ500ms��ѯ��ʪ��
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

//��ʱ���ж�
void timer2_int (void) interrupt 12
{
	T_Tick ++;
	if(T_Tick>10000) T_Tick = 0;
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
						if(key[i].key_time<=70)
							{
							key[i].single_flag = 1;
							}
						
					}
						else
					{
						key[i].key_time++;
						//�ж��������ʱ�����70ms������־λ��Ϊ1
						if(key[i].key_time>70)
							key[i].longkey_falg = 1;
					}
				}
				break;
									
			}				
		}
}

//��������
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

//����������
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

//��ˮλ����



