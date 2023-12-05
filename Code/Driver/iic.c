#include "iic.h"

/*��ʼ����������2���ź������ߣ�״̬Ϊ�ͷţ�*/
void iic_Init(void)
{
	P2M1 = 0x00;
	P2M0 = 0x00;
	IIC_SDA_H;
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();
}

/*����һ����ʼ�źŵĺ���*/
void iic_Start(void)
{
	IIC_SDA_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SDA_L;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_L;
}

/*����һ�������źŵĺ���*/
void iic_Stop(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_H;
	IIC_SDA_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}

/*����һ��Ӧ���źŵĺ���*/
void iic_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	_nop_();_nop_();
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_L;
}

/*����һ����Ӧ���źŵĺ���*/
void iic_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	_nop_();_nop_();
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_L;
}

/*�ȴ��ӻ����͵�Ӧ���źŵĺ���*/
unsigned char iic_Wait_Ack(void)
{
	unsigned char ACK = 0;
	IIC_SDA_H;
	_nop_();
	IIC_SCL_H;
	_nop_();
	if(IIC_SDA_READ)
	{
		ACK = 1;
	}
	else
	{
		ACK = 0;
	}
	IIC_SCL_L;
	_nop_();_nop_();
	return ACK;
}

/*����һ�����ݵĺ���*/
void iic_SendData(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		if(dat & 0x80)
		{
			IIC_SDA_H;
		}
		else
		{
			IIC_SDA_L;
		}
		dat<<=1;
		_nop_();_nop_();
		IIC_SCL_H;
		_nop_();_nop_();
		IIC_SCL_L;
		_nop_();_nop_();
	}
}

/*��ȡһ�����ݵĺ���*/
unsigned char iic_ReadData(void)
{
	unsigned char i,receive = 0;
	for(i=0;i<8;i++)
	{
		IIC_SCL_L;
		_nop_();_nop_();
		IIC_SCL_H;
		receive<<=1;
		if(IIC_SDA_READ)receive++;
		_nop_();
	}
	_nop_();_nop_();_nop_();
	IIC_SCL_L;
	return receive;
}





