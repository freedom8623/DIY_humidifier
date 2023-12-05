#include "iic.h"

/*初始化函数，把2条信号线拉高（状态为释放）*/
void iic_Init(void)
{
	P2M1 = 0x00;
	P2M0 = 0x00;
	IIC_SDA_H;
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();
}

/*产生一个开始信号的函数*/
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

/*产生一个结束信号的函数*/
void iic_Stop(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_H;
	IIC_SDA_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}

/*产生一个应答信号的函数*/
void iic_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_L;
	_nop_();_nop_();
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_L;
}

/*产生一个非应答信号的函数*/
void iic_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_H;
	_nop_();_nop_();
	IIC_SCL_H;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	IIC_SCL_L;
}

/*等待从机发送的应答信号的函数*/
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

/*发送一个数据的函数*/
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

/*读取一个数据的函数*/
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





