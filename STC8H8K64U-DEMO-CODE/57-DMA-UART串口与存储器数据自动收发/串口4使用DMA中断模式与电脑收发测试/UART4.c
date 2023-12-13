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

����4ȫ˫���жϷ�ʽ�շ�ͨѶ����

ͨ��PC��MCU��������, MCU���յ��������Զ�����DMA�ռ�.

��DMA�ռ�������ô�С�����ݺ�ͨ������4��DMA�Զ����͹��ܰѴ洢�ռ������ԭ������.

�ö�ʱ���������ʷ�����������ʹ��1Tģʽ(���ǵͲ�������12T)����ѡ��ɱ�������������ʱ��Ƶ�ʣ�����߾��ȡ�

����ʱ, ѡ��ʱ�� 22.1184MHz (�û��������޸�Ƶ��).

******************************************/

#include "..\..\comm\STC8H.h"

#include "stdio.h"
#include "intrins.h"

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

#define MAIN_Fosc   22118400L   //������ʱ�ӣ���ȷ����115200�����ʣ�
#define Baudrate4   115200L

bit	DmaTxFlag;
bit	DmaRxFlag;

u8 xdata DmaBuffer[256];

void UART4_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
void DMA_Config(void);


void UartPutc(unsigned char dat)
{
    S4BUF = dat; 
	while(!(S4CON & 0x02)); 
	S4CON &= ~0x02;
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
		DmaBuffer[i] = i;
	}

	UART4_config(0);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
	printf("STC8H UART4 Test Programme!\r\n");  //UART4����һ���ַ���

	DMA_Config();
	EA = 1; //����ȫ���ж�

	DmaTxFlag = 0;
	DmaRxFlag = 0;
	
	while (1)
	{
		if((DmaTxFlag) && (DmaRxFlag))
		{
			DmaTxFlag = 0;
			DMA_UR4T_CR = 0xc0;			//bit7 1:ʹ�� UART4_DMA, bit6 1:��ʼ UART4_DMA �Զ�����
			DmaRxFlag = 0;
			DMA_UR4R_CR = 0xa1;			//bit7 1:ʹ�� UART4_DMA, bit5 1:��ʼ UART4_DMA �Զ�����, bit0 1:��� FIFO
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
	DMA_UR4T_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR4T_STA = 0x00;
	DMA_UR4T_AMT = 0xff;		//���ô������ֽ�����n+1
	DMA_UR4T_TXAH = (u8)((u16)&DmaBuffer >> 8);
	DMA_UR4T_TXAL = (u8)((u16)&DmaBuffer);
	DMA_UR4T_CR = 0xc0;			//bit7 1:ʹ�� UART4_DMA, bit6 1:��ʼ UART4_DMA �Զ�����

	DMA_UR4R_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR4R_STA = 0x00;
	DMA_UR4R_AMT = 0xff;		//���ô������ֽ�����n+1
	DMA_UR4R_RXAH = (u8)((u16)&DmaBuffer >> 8);
	DMA_UR4R_RXAL = (u8)((u16)&DmaBuffer);
	DMA_UR4R_CR = 0xa1;			//bit7 1:ʹ�� UART4_DMA, bit5 1:��ʼ UART4_DMA �Զ�����, bit0 1:��� FIFO
}

//========================================================================
// ����: SetTimer2Baudraye(u16 dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void SetTimer2Baudraye(u16 dat)  // ʹ��Timer2��������.
{
	AUXR &= ~(1<<4);    //Timer stop
	AUXR &= ~(1<<3);    //Timer2 set As Timer
	AUXR |=  (1<<2);    //Timer2 set as 1T mode
	T2H = dat / 256;
	T2L = dat % 256;
	IE2  &= ~(1<<2);    //��ֹT2�ж�
	AUXR |=  (1<<4);    //Timer run enable
}

//========================================================================
// ����: void UART4_config(u8 brt)
// ����: UART4��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART4_config(u8 brt)    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
{
	if(brt == 2)
	{
		SetTimer2Baudraye((u16)(65536UL - (MAIN_Fosc / 4) / Baudrate4));
		S4CON = 0x10;       //8λ����, ʹ��Timer2�������ʷ�����, �������
	}
	else
	{
		S4CON = 0x50;       //8λ����, ʹ��Timer4�������ʷ�����, �������
		T4H = (65536UL - (MAIN_Fosc / 4) / Baudrate4) / 256;
		T4L = (65536UL - (MAIN_Fosc / 4) / Baudrate4) % 256;
		T4T3M = 0xa0;
	}
	//IE2 |= 0x10;          //����UART4�ж�
	P_SW2 &= ~0x04;       //UART4 switch bit2 to: 0: P0.2 P0.3
	//P_SW2 |= 0x04;      //UART4 switch bit2 to: 1: P5.2 P5.3
}


//========================================================================
// ����: void UART4_int (void) interrupt UART4_VECTOR
// ����: UART4�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
//void UART4_int (void) interrupt 18
//{
//    if((S4CON & 0x01) != 0)
//    {
//        S4CON &= ~0x01;    //Clear Rx flag
//        RX4_Buffer[RX4_Cnt] = S4BUF;
//        if(++RX4_Cnt >= UART4_BUF_LENGTH)   RX4_Cnt = 0;
//    }

//    if((S4CON & 0x02) != 0)
//    {
//        S4CON &= ~0x02;    //Clear Tx flag
//        B_TX4_Busy = 0;
//    }
//}

//========================================================================
// ����: void UART4_DMA_Interrupt (void) interrupt 56/57
// ����: UART4 DMA�жϺ���
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2021-5-8
// ��ע: 
//========================================================================
void UART4_DMA_Interrupt(void) interrupt 13
{
	if (DMA_UR4T_STA & 0x01)	//�������
	{
		DMA_UR4T_STA &= ~0x01;
		DmaTxFlag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//���ݸ���
	{
		DMA_UR4T_STA &= ~0x04;
	}
	
	if (DMA_UR4R_STA & 0x01)	//�������
	{
		DMA_UR4R_STA &= ~0x01;
		DmaRxFlag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//���ݶ���
	{
		DMA_UR4R_STA &= ~0x02;
	}
}
