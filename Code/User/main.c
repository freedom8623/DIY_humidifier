#include "main.h"
#include "Gpio.h"
#include "Timer.h"
#include "DHT.h"
#include "Pwm.h"
#include "oled.h"

//������
sbit Buzzer = P3^7;
//ˮλ�������
sbit test = P2^4;
sbit Water_test = P1^1;



sbit test2 =P2^3 ;

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
//OLED ��ʾ����
void Display_Screen(void);
void Setting_Pwm(u16 Duty1,u16 Duty2);
//pwmռ�ձ�
extern u16 PWM1_Duty;
extern u16 PWM2_Duty;

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
//	Timer2_init();//��ʱ����ʼ��
	
	//Pwm_init();//����pwm;ռ�ձ�50%
	//UpdatePwm();//����ռ�ձ�   //��PWM.C�и���ռ�ձ�ʹ�ò���Ƶ��Ϊ108khz
	//DHT_Start();//��ʪ��
	
	
	//OLED��ʼ��
	oled_Init();			//��ʼ��OLED  
	oled_clear()  	; 
	oled_ShowStr(0,0,"1124'xiaolala",16);
	
	//��ؿ���
	EA = 1;     //�����ж�

	//Buzzer = 1;
	while(1)
	{
		
		P11  = 1;
		//test = 0;
		Buzzer = 0;//���Է�����
		
		test2 = 0;
//		Key_Proc();
		//DHT_Read();
		//Alertor();
		//Display_Screen();
		
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
	uchar i = 0;
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


char Show_Flag = 0;
void Display_Screen(void)
{
	if(T_Tick%100==0) Show_Flag = 1;
	else return;
	
}

//��������
void Key_Proc(void)
{
	if(key[0].single_flag == 1)
	{
		Buzzer ^= 1; 
		key[0].single_flag = 0;
	
	}
	
	 if(key[1].single_flag == 1)
	{
		test2 ^= 1;
		
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

//ˮλ/��������������������
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

void Setting_Pwm(u16 Duty1,u16 Duty2)
{
		PWM1_Duty = Duty1;
		PWM2_Duty = Duty2;
	
		UpdatePwm();
}



