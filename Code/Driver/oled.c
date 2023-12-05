#include "oled.h"

/*�����oled����ָ��ĺ���*/
void oled_IIC_SendCommand(unsigned char IIC_Command)
{
	iic_Start();//IICЭ�鿪ʼ�ź�
	iic_SendData(0x78);//�����豸��ַ
	iic_Wait_Ack();//�ȴ�Ӧ������Ӧ����Բ��ô���һ����һ��Ӧ���ź�
	iic_SendData(0x00);//����D/CΪ0��Ϊָ��ģʽ
	iic_Wait_Ack();//�ȴ�Ӧ��
	iic_SendData(IIC_Command);//����ָ��
	iic_Wait_Ack();//�ȴ�Ӧ��
	iic_Stop();//IICЭ������ź�
}

/*�����oled�������ݵĺ���*/
void oled_IIC_SendData(unsigned char IIC_Data)
{
	iic_Start();//IICЭ�鿪ʼ�ź�
	iic_SendData(0x78);//�����豸��ַ
	iic_Wait_Ack();//�ȴ�Ӧ������Ӧ����Բ��ô���һ����һ��Ӧ���ź�
	iic_SendData(0x40);//����D/CΪ1��Ϊ����ģʽ
	iic_Wait_Ack();//�ȴ�Ӧ��
	iic_SendData(IIC_Data);//��������
	iic_Wait_Ack();//�ȴ�Ӧ��
	iic_Stop();//IICЭ������ź�
}

/*�����oled��������*/
void oled_clear(void)
{
	unsigned char i,j;//����2������������ʵ��ѭ��
	for(i = 0;i < 8;i++)//����������SSD1306����8ҳ��0-7
	{
		oled_IIC_SendCommand(0xb0+i);//�����ǰ�ҳ�����ܹ�8ҳ��0xb0-0xb7
		oled_IIC_SendCommand(0x00);//���õ�4λ��ַ�������������ûᱻ��Ϊ0000
		oled_IIC_SendCommand(0x10);//���ø�4λ��ַ�������������ûᱻ��Ϊ0000
		for(j = 0;j < 128;j++)//ÿһ�еĳ�����128bit
		{
			oled_IIC_SendData(0x00);//����ʱÿ�ζ�д0x00
		}
	}
}

/*�����oled��ʼ������*/
void oled_Init(void)
{
	iic_Stop();//IICЭ���ʼ��
	Delay_ms(200);//�������ϵ���ӳ٣��ȴ�oled��λ��
	oled_IIC_SendCommand(0xAE);//.�ر���ʾ
	
	oled_IIC_SendCommand(0xD5);//.����ʱ�ӷ�Ƶ���ӣ���Ƶ��
	oled_IIC_SendCommand(0x80);//.��4λ���÷�Ƶ���ӣ���4λ������Ƶ��
	
	oled_IIC_SendCommand(0xA8);//.��������·��
	oled_IIC_SendCommand(0x3F);//.Ĭ��0x3F��1/64��
	
	oled_IIC_SendCommand(0xD3);//.������ʾƫ��
	oled_IIC_SendCommand(0x00);//.Ĭ��Ϊ0
	
	oled_IIC_SendCommand(0x00);//.������ʾλ��-�е͵�ַ
	oled_IIC_SendCommand(0x10);//.������ʾλ��-�иߵ�ַ
	oled_IIC_SendCommand(0x40);//.������ʾ��ʼ��[5:0]������
	
	oled_IIC_SendCommand(0x8D);//.��ɱ�����
	oled_IIC_SendCommand(0x14);//.bit2������/�ر�
	
	oled_IIC_SendCommand(0x20);//�����ڴ�Ѱַģʽ
	oled_IIC_SendCommand(0x02);//���ó�Ϊҳ��Ѱַģʽ
	
	oled_IIC_SendCommand(0xA1);//.���ض������ã�bit0��0��0->1;1:0->127;���������ó�1���ǽ�127ӳ�䵽SEG0
	
	oled_IIC_SendCommand(0xC8);//.����COMɨ�跽��bit3��0����ͨģʽ��1���ض���ģʽ��COM[N-1]->COM0,N:����·����;
	oled_IIC_SendCommand(0xDA);//.����COM���ŵ�Ӳ������
	oled_IIC_SendCommand(0x12);//.A[5:4]������ֻ�����˵�5λ��������COM������ӳ�䣬˳��COM��������
	
	oled_IIC_SendCommand(0x81);//.���öԱȶ�
	oled_IIC_SendCommand(0xEF);//.�������ó�EF��Ĭ����7F������Խ��Աȶ�Խ��
	
	oled_IIC_SendCommand(0xD9);//.����Ԥ�������
	oled_IIC_SendCommand(0xF1);//.��һ�׶�Ϊ1��ʱ�����ڣ��ڶ��׶�Ϊ15��ʱ������
	
	oled_IIC_SendCommand(0xDB);//.����VCOMH��ѹ����
	oled_IIC_SendCommand(0x30);//.[6:4]000��0.65*vcc��001��0.77*vcc��011��0.83*vcc��
	
	oled_IIC_SendCommand(0xA4);//�ָ���RAM������ʾ
	oled_IIC_SendCommand(0xA6);//.������ʾ��ʽ��bit0��1������ʾ��0������ʾ��
	oled_IIC_SendCommand(0xAF);//.������ʾ
	oled_clear();
}

/*�����oled����ʾ����*/
void oled_Display_ON(void)
{
	oled_IIC_SendCommand(0x8D);//��ɱ�����ָ��
	oled_IIC_SendCommand(0x14);//�򿪵�ɱ�
	oled_IIC_SendCommand(0xAF);//����ʾ
}

/*�����oled����ʾ����*/
void oled_Display_OFF(void)
{
	oled_IIC_SendCommand(0x8D);//��ɱ�����ָ��
	oled_IIC_SendCommand(0x10);//�رյ�ɱ�
	oled_IIC_SendCommand(0xAE);//�ر���ʾ
}


/*�����oledȫ����亯��*/
void oled_Allfill(unsigned char fill_Data)
{
	unsigned char i,j;//����2������������ʵ��ѭ��
	for(i = 0;i < 8;i++)//����������SSD1306����8ҳ��0-7
	{
		oled_IIC_SendCommand(0xb0+i);//�����ǰ�ҳ�����ܹ�8ҳ��0xb0-0xb7
		oled_IIC_SendCommand(0x00);//���õ�4λ��ַ�������������ûᱻ��Ϊ0000
		oled_IIC_SendCommand(0x10);//���ø�4λ��ַ�������������ûᱻ��Ϊ0000
		for(j = 0;j < 128;j++)//ÿһ�еĳ�����128bit
		{
			oled_IIC_SendData(fill_Data);//����ʱÿ�ζ�дfill_Data���ֵ
		}
	}
}

/*�����oled���ù�꺯��*/
void oled_SetPos(unsigned char x,unsigned char y)
{
	oled_IIC_SendCommand(0XB0+y);//������ȷ�����ĸ�ҳ�濪ʼ�Ĺ��
	oled_IIC_SendCommand((x&0xf0)>>4|0x10);//���������ø�4λ����
	oled_IIC_SendCommand((x&0x0f));//���������õ�4λ����
}


/*����m^n�ĺ���*/
unsigned int oled_Pow(unsigned char m,unsigned char n)
{
	unsigned int	result = 1;//���ñ���Ϊ��nΪ0ʱ������1
	if(n!=0){while(n--)result *= m;}//����ʱ�ж�n�Ƿ�Ϊ0�������ֱ�����1���ɣ��������������
	return result;
}

/*�����oled��ʾ���ֺ���*/
void oled_ShowNum(unsigned char x,unsigned char y,int num,unsigned char len,unsigned char size)
{
	unsigned char t,temp;
	
	if(num<0)//�������ж���������Ǹ�������
	{
		num *= (-1);//�Ǹ�����תΪ
		oled_ShowChar(x-(size/2),y,'-',16);//��xλ�õ�ǰһ��sizeλ������ʾ����
	}
	for(t=0;t<len;t++)//�������ֳ���ѭ��
	{
		temp = (num/oled_Pow(10,len-t-1))%10;//ȡ������λ������
		oled_ShowChar(x+(size/2)*t,y,temp+'0',size);//��ʾÿһ��λ������
	}
	
}

/*�����oled��ʾһ���ַ�����*/
void oled_ShowChar(unsigned char x,unsigned char y,unsigned char ch,unsigned char size)
{
	unsigned char c=0,i=0;
	c = ch - ' ';//��ȡ�ַ���ƫ����
	if(x+size/2>127){x = 0; y = y+2;}//�������ж�xλ���Ƿ��Ѿ�������ʾ��ȣ���������͵�2ҳ��
	
	if(size == 8)//�ж���8*6���ַ�
	{
		oled_SetPos(x,y);//���ÿ�ʼλ��Ϊx��y����һҳ��
		for(i=0;i<6;i++)//ѭ��6�������ݣ���Ϊֻ��Ҫһҳ������д��һҳ����
			oled_IIC_SendData(F6X8[c][i]);
	}
	if(size == 16)//�ж���16*8���ַ�
	{
		oled_SetPos(x,y);//���ÿ�ʼλ��Ϊx��y����һҳ��
		for(i=0;i<8;i++)//ѭ��8��������
			oled_IIC_SendData(F8X16[c*16+i]);//�����C��ƫ������Ȼ��c*16��Ϊ�����������ҵ�����Ҫ���ַ���i�������0-7������
		oled_SetPos(x,y+1);	//��Ϊ�����16*8���ַ���Ҫ2ҳ�����õڶ�ҳΪ��ʼλ��
		for(i=0;i<8;i++)//�����ǵڶ�ҳ��������ѭ��
			oled_IIC_SendData(F8X16[c*16+i+8]);//���������+8����Ϊ��������ĵ�8-15������
	}
}

/*�����oled��ʾ�ַ�������*/
void oled_ShowStr(unsigned char x,unsigned char y,const unsigned char *p,unsigned char size)
{
	while((*p <= '~') && (*p >= ' '))//��������ж��Ƿ���ASCLL������ַ������С�ڻ��ߴ��ھͲ���ӡ
	{
		if(x>(128-(size/2)))//�������ж��Ƿ񳬹�ÿ�еĿ��128bit
		{
			x = 0;//��������Ͱ�x��Ϊ��һλ
			y += size;//Ȼ���y�ӵ���һ��
		}
		if(y > (64-size))//�������ж��Ƿ񳬹����������64bit
		{
			y = x = 0;//���������»ص�0��0�е�λ��
			oled_clear();//Ȼ������
		}
		oled_ShowChar(x,y,*p,size);//����������õ�������ʾһ���ַ��ĺ�������Ϊ����ַ����Կ����ɶ���ַ���ɵģ�
		x += size/2;//������ÿ��дһ���ַ���Ҫ��x���У�����ƫ���ַ���صĿ��
		p++;//�ַ���ָ�����ӣ�Ҳ���ǵ���һ���ַ�
	}
}

/*
	@brief			��ʾ����
	@param	x����ʼ�У�һ������ռ16��
					y����ʼҳ��һ������ռ��ҳ
	@retval			��
 */
void oled_ShowCN(unsigned char x,unsigned char y,unsigned char bit_temp)
{
	unsigned char i;
	oled_SetPos(x,y);//���ÿ�ʼλ��x��y����һҳ��
	for(i = 0;i < 16;i++)//ѭ��16�η������ݣ���Ϊ����һ��������ռ��2ҳ�����ȿ�ȶ���16
	{
		oled_IIC_SendData(Hzk[2*bit_temp][i]);
		/*
		д���һҳ�������������Ƕ�ά����Ȼ��bit_temp�Ƕ�λ�����Զ��������ֿ���
		��λ����Ӧ�ĺ��֣�2*bit_temp����һ�����ֵ�size
		*/
	}
	oled_SetPos(x,y+1);//���õڶ�ҳλ��
	for(i = 0;i < 16;i++)//Ȼ����д��ڶ�ҳ����
	{
		oled_IIC_SendData(Hzk[2*bit_temp+1][i]);//���������+1�����������һҳ����������
	}
}

/*�����oled��ʾͼƬ����*/
void oled_ShowBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	int j=0;
	unsigned char x,y;
	if(y1%8 == 0)y=y1/8;//�ж��Ƿ�պ�һҳ
	else y=y1/8+1;//���ǵĻ����ټ�һҳ
	
	for(y = y0;y < y1;y++)//ѭ��ҳ��
	{
		oled_SetPos(x0,y);//���ÿ�ʼλ��x0��y
		for(x = x0;x < x1; x++)//ѭ������
		{
			oled_IIC_SendData(BMP[j++]);//����ͼƬ����
		}
	}
	
}
