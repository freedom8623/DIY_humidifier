#include "DHT.H"
#include "Intrins.H"
#include "oled.H"


void Delay25ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 4;
	j = 12;
	k = 50;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void DHT11_delay_us(uchar n)
{

	unsigned char i;

	while(n--)
	{
	i = 6;
	while (--i);
		
	}

}
void DHT11_delay_ms(uint z)
{
   unsigned char i, j;
	
	while(z--)
	{

		_nop_();
	i = 32;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
	
	}
}

/*
��������Ƭ����������ʼ�źţ�
1.����������data��
2.����data�ӳ�18ms��
3.����data���ӳٵȴ���ͨ���˲�������Ƭ����������Ϊ���룩��
*/
void DHT11_start()
{
   DHT=1;
   DHT11_delay_us(2);
   DHT=0;
   DHT11_delay_ms(25);   //������ʱ18ms����;
   DHT=1;
   DHT11_delay_us(30);   //���� ��ʱ 20~40us��ȡ�м�ֵ 30us
}

/*------------------------------------------------
              ���հ�λ������
------------------------------------------------*/
uchar DHT11_rec_byte()      //����һ���ֽ�
{
  unsigned char i,dat=0;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {          
      while(DHT);   //�ȴ�����͵�ƽ
      while(!DHT);   //�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(32);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;//��λ����λ���㣩ʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(DHT==1)    //����Ϊ1ʱ��ʹdat��1����������1
        dat+=1;
      while(DHT);  //�ȴ�����������    
   }  
    return dat;
}


/*------------------------------------------------
              ����40bit���ݣ��������ʪ�ȣ�
1.�����Ȱ�data�����ߣ�io����Ϊ���룩��
2.�ӻ���data�����ͣ�������ȡdata�ߵ�ƽ��ֱ���͵�ƽ��������Լ50us��
  �ӻ�����data�ߺ��ӳ�40us���ң�28~70us֮�䣩�����ٴζ�ȡdata�ߵ�ƽ�����Ϊ�͵�ƽ����Ϊ��0�������Ϊ�ߵ�ƽ����Ϊ��1����
3.�����ظ�����1,2�����ۼ�40�Ρ�
------------------------------------------------*/
unsigned int humit;
uchar T_H;

void DHT11_receive()      //����40λ������
{
		uchar R_H,R_L,T_L,RH,RL,TH,TL,revise; 
//		if(DHT_T) return;
//		DHT_T = 1;
	
   
    DHT11_start();//������ʼ�źţ�
	
	
    if(DHT==0)
    {
        while(DHT==0);   //�ȴ�����     
        DHT11_delay_us(40);  //���ߺ���ʱ80us
			
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //���һ�ֽ�ΪУ��λ��У���Ƿ���ȷ
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
				
				humit = RH;
        /*���ݴ���ת��Ϊ�ַ���������ʾ*/
			  //ʪ��
				rec_dat[0]='0'+(RH/10);
        rec_dat[1]='0'+(RH%10);
				rec_dat[2]=' ';
				rec_dat[3]=' ';
				
				//�¶�
        rec_dat[4]='0'+(TH/10);
        rec_dat[5]='0'+(TH%10); 
		    rec_dat[6]=' ';
				
			
			
    }

}