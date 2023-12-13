/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

/*************  ����˵��    **************

�����̻���STC8H8K64UΪ����оƬ��ʵ����9���б�д���ԣ�STC8Hϵ�д�DMAģ���оƬ��ͨ�òο�.

����2���洢���ռ䣬һ������һ�����գ��ֱ��ʼ��2���洢���ռ����ݡ�

����M2M DMA���ϵ���Զ������ʹ洢�������д�뵽���մ洢���ռ�.

���ݲ�ͬ�Ķ�ȡ˳��д��˳�򣬽��յ���ͬ�����ݽ��.

ͨ������2(P4.6 P4.7)��ӡ���մ洢������(�ϵ��ӡһ��).

����ʱ, ѡ��ʱ�� 22.1184MHz (�û��������޸�Ƶ��).

******************************************/

#include "STC8H.h"
#include "intrins.h"
#include "stdio.h"

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

#define MAIN_Fosc     22118400L   //������ʱ�ӣ���ȷ����115200�����ʣ�
#define Baudrate      115200L
#define TM            (65536 -(MAIN_Fosc/Baudrate/4))

bit	DmaFlag;

u8 xdata DmaTxBuffer[256];
u8 xdata DmaRxBuffer[256];

void DMA_Config(void);

/******************** ���ڴ�ӡ���� ********************/
void UartInit(void)
{
	P_SW2 |= 1;         //UART2 switch to: 0: P1.0 P1.1,  1: P4.6 P4.7
	S2CON &= ~(1<<7);   //8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
	T2L  = TM;
	T2H  = TM>>8;
	AUXR |= 0x14;	    //��ʱ��2ʱ��1Tģʽ,��ʼ��ʱ
}

void UartPutc(unsigned char dat)
{
	S2BUF  = dat; 
	while((S2CON & 2) == 0);
	S2CON &= ~2;    //Clear Tx flag
}

char putchar(char c)
{
	UartPutc(c);
	return c;
}

//========================================================================
// ����: void main(void)
// ����: ��������
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void main(void)
{
	u16 i;
	
    P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��

    P0M1 = 0x30;   P0M0 = 0x30;   //����P0.4��P0.5Ϊ©����·(ʵ��������������赽3.3V)
    P1M1 = 0x30;   P1M0 = 0x30;   //����P1.4��P1.5Ϊ©����·(ʵ��������������赽3.3V)
    P2M1 = 0x3c;   P2M0 = 0x3c;   //����P2.2~P2.5Ϊ©����·(ʵ��������������赽3.3V)
    P3M1 = 0x50;   P3M0 = 0x50;   //����P3.4��P3.6Ϊ©����·(ʵ��������������赽3.3V)
    P4M1 = 0x3c;   P4M0 = 0x3c;   //����P4.2~P4.5Ϊ©����·(ʵ��������������赽3.3V)
    P5M1 = 0x0c;   P5M0 = 0x0c;   //����P5.2��P5.3Ϊ©����·(ʵ��������������赽3.3V)
    P6M1 = 0xff;   P6M0 = 0xff;   //����Ϊ©����·(ʵ��������������赽3.3V)
    P7M1 = 0x00;   P7M0 = 0x00;   //����Ϊ׼˫���

	for(i=0; i<256; i++)
	{
		DmaTxBuffer[i] = i;
		DmaRxBuffer[i] = 0;
	}

	UartInit();
	printf("STC8H Memory to Memory DMA Test Programme!\r\n");  //UART����һ���ַ���

	DMA_Config();
	EA = 1; //�������ж�

	DmaFlag = 0;

	while (1)
	{
		if(DmaFlag)
		{
			DmaFlag = 0;

			for(i=0; i<256; i++)
			{
				printf("%02bX ", DmaRxBuffer[i]);
				if((i & 0x0f) == 0x0f)
					printf("\r\n");
			}
		}
	}
}

//========================================================================
// ����: void DMA_Config(void)
// ����: UART DMA ��������.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-5-6
//========================================================================
void DMA_Config(void)
{
//	DMA_M2M_CFG = 0x80;         //r++ = t++
//	DMA_M2M_STA = 0x00;
//	DMA_M2M_AMT = 0x7f;		//���ô������ֽ�����n+1
//	DMA_M2M_TXAH = (u8)((u16)&DmaTxBuffer >> 8);
//	DMA_M2M_TXAL = (u8)((u16)&DmaTxBuffer);
//	DMA_M2M_RXAH = (u8)((u16)&DmaRxBuffer >> 8);
//	DMA_M2M_RXAL = (u8)((u16)&DmaRxBuffer);

//	DMA_M2M_CFG = 0xa0;         //r++ = t--
//	DMA_M2M_STA = 0x00;
//	DMA_M2M_AMT = 0x7f;		//���ô������ֽ�����n+1
//	DMA_M2M_TXAH = (u8)((u16)&DmaTxBuffer[255] >> 8);
//	DMA_M2M_TXAL = (u8)((u16)&DmaTxBuffer[255]);
//	DMA_M2M_RXAH = (u8)((u16)&DmaRxBuffer >> 8);
//	DMA_M2M_RXAL = (u8)((u16)&DmaRxBuffer);

//	DMA_M2M_CFG = 0x90;         //r-- = t++
//	DMA_M2M_STA = 0x00;
//	DMA_M2M_AMT = 0x7f;		//���ô������ֽ�����n+1
//	DMA_M2M_TXAH = (u8)((u16)&DmaTxBuffer >> 8);
//	DMA_M2M_TXAL = (u8)((u16)&DmaTxBuffer);
//	DMA_M2M_RXAH = (u8)((u16)&DmaRxBuffer[255] >> 8);
//	DMA_M2M_RXAL = (u8)((u16)&DmaRxBuffer[255]);

	DMA_M2M_CFG = 0xb0;         //r-- = t--
	DMA_M2M_STA = 0x00;
	DMA_M2M_AMT = 0x7f;		//���ô������ֽ�����n+1
	DMA_M2M_TXAH = (u8)((u16)&DmaTxBuffer[255] >> 8);
	DMA_M2M_TXAL = (u8)((u16)&DmaTxBuffer[255]);
	DMA_M2M_RXAH = (u8)((u16)&DmaRxBuffer[255] >> 8);
	DMA_M2M_RXAL = (u8)((u16)&DmaRxBuffer[255]);
	
//	DMA_M2M_CFG |= 0x0c;
	DMA_M2M_CR = 0xc0;			//bit7 1:ʹ�� M2M_DMA, bit6 1:��ʼ M2M_DMA �Զ�����
}

//========================================================================
// ����: void M2M_DMA_Interrupt (void) interrupt 47
// ����: UART1 DMA�жϺ���
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2021-5-8
// ��ע: 
//========================================================================
void M2M_DMA_Interrupt(void) interrupt 13
{
	if (DMA_M2M_STA & 0x01)	//�������
	{
		DMA_M2M_STA &= ~0x01;
		DmaFlag = 1;
	}
}
