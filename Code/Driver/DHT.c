#include "DHT.h"


//�����ߴ���
//��ʱ����


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




char datas[5]; 		//����ֱ����ʪ�ȣ�ʪ��С�����¶ȣ��¶�С����У��
//��ʼ��ģ�飨���ģ���Ƿ���ڣ�ÿ�δ������ݶ�Ҫ��ʼ��
void DHT_Start()
{
	
    DHT = 1;		//��Ӧ��ʼ��ʱ��start
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
	for(j = 0;j<5;j++)//�ֱ��ȡ��������
	{			
		for(i=0;i<8;i++)//ÿ���λ�ֱ���
		{		
			while(!DHT);		//�ߵ�ƽ��ʼ��ʱ
			Delay40us();
			if(DHT == 1)  //�����Ϊ�����ǡ�1��
			{		
				flag = 1;
				while(DHT);
			}
			 else       //����0��
			{				
				flag = 0;
			}
			value = value << 1;		//��λ
			value |= flag; 			//��ֵ
		}
		datas[j] = value;			//��ֵ
	}

}


