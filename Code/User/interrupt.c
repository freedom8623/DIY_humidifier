#include "interrupt.h"
#include "Menu.h"
//��ʱ��2�ж���Ҫ����ϵͳʱ��
//��ʱ��1ns


void timer2_int (void) interrupt 12
{
	uchar i = 0;
	T_Tick ++;
	if(T_Tick>10000) T_Tick = 0;


}

//��ʱ��3�ж���Ҫ���ڰ����ж�


struct keys key[4] = {0,0,0};
uchar Key_T = 0;

//�������Ŷ���
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
							key[i].longkey_flag = 1;
					}
				}
				break;
									
			}				
		}
	
	}
}