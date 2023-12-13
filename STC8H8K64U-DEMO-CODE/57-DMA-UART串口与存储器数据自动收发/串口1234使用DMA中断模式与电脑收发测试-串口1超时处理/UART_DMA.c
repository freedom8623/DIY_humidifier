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

����1,2,3,4ȫ˫���жϷ�ʽ�շ�ͨѶ����

ͨ��PC��MCU��������, MCU���յ��������Զ�����DMA�ռ�.

��DMA�ռ�������ô�С�����ݺ�ͨ�����ڵ�DMA�Զ����͹��ܰѴ洢�ռ������ԭ������.

���ô��ڽ����жϽ��г�ʱ�жϣ���ʱû���յ��µ����ݣ���ʾһ�������Ѿ��������.

�ö�ʱ���������ʷ�����������ʹ��1Tģʽ(���ǵͲ�������12T)����ѡ��ɱ�������������ʱ��Ƶ�ʣ�����߾��ȡ�

����ʱ, ѡ��ʱ�� 22.1184MHz (�û��������޸�Ƶ��).

******************************************/

#include "stdio.h"
#include "stc8h.h"

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

#define MAIN_Fosc       22118400L   //������ʱ�ӣ���ȷ����115200�����ʣ�
#define Baudrate1       115200L
#define Baudrate2       115200L
#define Baudrate3       115200L
#define Baudrate4       115200L
#define Timer0_Reload   (65536UL -(MAIN_Fosc / 1000))       //Timer 0 �ж�Ƶ��, 1000��/��

#define DMA_TX_LEN      255  //���ô������ֽ�����n+1
#define DMA_RX_LEN      255  //���ô������ֽ�����n+1

bit B_1ms;          //1ms��־
bit	DmaTx1Flag;
bit	DmaRx1Flag;
bit	DmaTx2Flag;
bit	DmaRx2Flag;
bit	DmaTx3Flag;
bit	DmaRx3Flag;
bit	DmaTx4Flag;
bit	DmaRx4Flag;

bit	Tx1SendFlag;
u8  RX1_TimeOut;
u16 RX1_Cnt;    //���ռ���

u8 xdata DmaBuffer1[256];
u8 xdata DmaBuffer2[256];
u8 xdata DmaBuffer3[256];
u8 xdata DmaBuffer4[256];

void UART1_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
void UART2_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
void UART3_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
void UART4_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
void UART1_DMA_Config(void);
void UART2_DMA_Config(void);
void UART3_DMA_Config(void);
void UART4_DMA_Config(void);

void UART1_DMA_Transmit(u8 *pData, u16 Size);
void UART1_DMA_Receive(u8 *pData, u16 Size);

void UartPutc(unsigned char dat)
{
    Tx1SendFlag = 1;
	SBUF = dat; 
	while(Tx1SendFlag); 
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
		DmaBuffer1[i] = i;
		DmaBuffer2[i] = 255-i;
		DmaBuffer3[i] = 0;
		DmaBuffer4[i] = 255;
	}

	AUXR = 0x80;    //Timer0 set as 1T, 16 bits timer auto-reload, 
	TH0 = (u8)(Timer0_Reload / 256);
	TL0 = (u8)(Timer0_Reload % 256);
	ET0 = 1;    //Timer0 interrupt enable
	TR0 = 1;    //Tiner0 run
	
	UART1_config(1);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
	UART2_config(2);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
	UART3_config(0);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
	UART4_config(0);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.

	UART1_DMA_Config();
	UART2_DMA_Config();
	UART3_DMA_Config();
	UART4_DMA_Config();
	EA = 1; //�������ж�

	DmaTx1Flag = 0;
	DmaRx1Flag = 0;
	DmaTx2Flag = 0;
	DmaRx2Flag = 0;
	DmaTx3Flag = 0;
	DmaRx3Flag = 0;
	DmaTx4Flag = 0;
	DmaRx4Flag = 0;

//	printf("STC8H UART DMA Test Programme!\r\n");  //UART1����һ���ַ���
	while (1)
	{
		if(B_1ms)   //1ms��
		{
			B_1ms = 0;
			if(RX1_TimeOut > 0)     //��ʱ����
			{
				if(--RX1_TimeOut == 0)
				{
                    //�رս���DMA���´ν��յ��������´������ʼ��ַλ�ã������´ν������ݼ����������š�
					DMA_UR1R_CR = 0x00;			//bit7 1:ʹ�� UART1_DMA, bit5 1:��ʼ UART1_DMA �Զ�����, bit0 1:��� FIFO

					printf("\r\nUART1 Timeout!\r\n");  //UART1����һ���ַ���
                    UART1_DMA_Transmit(DmaBuffer1,RX1_Cnt);  //����DMA���ͻ����������ݳ��ȣ�����������
                    RX1_Cnt = 0;
                    DmaTx1Flag = 0;
                    DmaRx1Flag = 0;
                    UART1_DMA_Receive(DmaBuffer1,DMA_RX_LEN+1);  //����DMA���ջ����������ݳ��ȣ�����������
				}
			}
		}

		if((DmaTx1Flag) && (DmaRx1Flag))
		{
			RX1_TimeOut = 0;
			printf("\r\nUART1 DMA FULL!\r\n");  //UART1����һ���ַ���
			UART1_DMA_Transmit(DmaBuffer1,RX1_Cnt);  //����DMA���ͻ����������ݳ��ȣ�����������
			RX1_Cnt = 0;
			DmaTx1Flag = 0;
			DmaRx1Flag = 0;
			UART1_DMA_Receive(DmaBuffer1,DMA_RX_LEN+1);  //����DMA���ջ����������ݳ��ȣ�����������
		}

		if((DmaTx2Flag) && (DmaRx2Flag))
		{
			DmaTx2Flag = 0;
			DMA_UR2T_CR = 0xc0;			//bit7 1:ʹ�� UART2_DMA, bit6 1:��ʼ UART2_DMA �Զ�����
			DmaRx2Flag = 0;
			DMA_UR2R_CR = 0xa1;			//bit7 1:ʹ�� UART2_DMA, bit5 1:��ʼ UART2_DMA �Զ�����, bit0 1:��� FIFO
		}

		if((DmaTx3Flag) && (DmaRx3Flag))
		{
			DmaTx3Flag = 0;
			DMA_UR3T_CR = 0xc0;			//bit7 1:ʹ�� UART3_DMA, bit6 1:��ʼ UART3_DMA �Զ�����
			DmaRx3Flag = 0;
			DMA_UR3R_CR = 0xa1;			//bit7 1:ʹ�� UART3_DMA, bit5 1:��ʼ UART3_DMA �Զ�����, bit0 1:��� FIFO
		}

		if((DmaTx4Flag) && (DmaRx4Flag))
		{
			DmaTx4Flag = 0;
			DMA_UR4T_CR = 0xc0;			//bit7 1:ʹ�� UART4_DMA, bit6 1:��ʼ UART4_DMA �Զ�����
			DmaRx4Flag = 0;
			DMA_UR4R_CR = 0xa1;			//bit7 1:ʹ�� UART4_DMA, bit5 1:��ʼ UART4_DMA �Զ�����, bit0 1:��� FIFO
		}
	}
}

//========================================================================
// ����: void UART1_DMA_Config(void)
// ����: UART1 DMA ��������.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-5-6
//========================================================================
void UART1_DMA_Config(void)
{
	DMA_UR1T_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR1T_STA = 0x00;
	DMA_UR1T_AMT = DMA_TX_LEN;		//���ô������ֽ�����n+1
	DMA_UR1T_TXA = DmaBuffer1;
	DMA_UR1T_CR = 0xc0;			//bit7 1:ʹ�� UART1_DMA, bit6 1:��ʼ UART1_DMA �Զ�����

	DMA_UR1R_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR1R_STA = 0x00;
	DMA_UR1R_AMT = DMA_RX_LEN;		//���ô������ֽ�����n+1
	DMA_UR1R_RXA = DmaBuffer1;
	DMA_UR1R_CR = 0xa1;			//bit7 1:ʹ�� UART1_DMA, bit5 1:��ʼ UART1_DMA �Զ�����, bit0 1:��� FIFO
}

void UART1_DMA_Transmit(u8 *pData, u16 Size)
{
    if(Size == 0) return;
    Size -= 1;
    DMA_UR1T_AMT = (u8)Size;        //���ô������ֽ�����n+1
    DMA_UR1T_TXA = (u16)pData;
    DMA_UR1T_CR = 0xc0;     //bit7 1:ʹ�� UART4_DMA, bit6 1:��ʼ UART1_DMA �Զ�����
}

void UART1_DMA_Receive(u8 *pData, u16 Size)
{
    if(Size == 0) return;
    Size -= 1;
    DMA_UR1R_AMT = (u8)Size;        //���ô������ֽ�����n+1
    DMA_UR1R_RXA = (u16)pData;
    DMA_UR1R_CR = 0xa1;     //bit7 1:ʹ�� UART4_DMA, bit5 1:��ʼ UART4_DMA �Զ�����, bit0 1:��� FIFO
}

//========================================================================
// ����: void UART2_DMA_Config(void)
// ����: UART2 DMA ��������.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-5-6
//========================================================================
void UART2_DMA_Config(void)
{
	DMA_UR2T_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR2T_STA = 0x00;
	DMA_UR2T_AMT = DMA_TX_LEN;		//���ô������ֽ�����n+1
	DMA_UR2T_TXA = DmaBuffer2;
	DMA_UR2T_CR = 0xc0;			//bit7 1:ʹ�� UART2_DMA, bit6 1:��ʼ UART2_DMA �Զ�����

	DMA_UR2R_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR2R_STA = 0x00;
	DMA_UR2R_AMT = DMA_RX_LEN;		//���ô������ֽ�����n+1
	DMA_UR2R_RXA = DmaBuffer2;
	DMA_UR2R_CR = 0xa1;			//bit7 1:ʹ�� UART2_DMA, bit5 1:��ʼ UART2_DMA �Զ�����, bit0 1:��� FIFO
}

//========================================================================
// ����: void UART3_DMA_Config(void)
// ����: UART3 DMA ��������.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-5-6
//========================================================================
void UART3_DMA_Config(void)
{
	DMA_UR3T_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR3T_STA = 0x00;
	DMA_UR3T_AMT = DMA_TX_LEN;		//���ô������ֽ�����n+1
	DMA_UR3T_TXA = DmaBuffer3;
	DMA_UR3T_CR = 0xc0;			//bit7 1:ʹ�� UART3_DMA, bit6 1:��ʼ UART3_DMA �Զ�����

	DMA_UR3R_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR3R_STA = 0x00;
	DMA_UR3R_AMT = DMA_RX_LEN;		//���ô������ֽ�����n+1
	DMA_UR3R_RXA = DmaBuffer3;
	DMA_UR3R_CR = 0xa1;			//bit7 1:ʹ�� UART3_DMA, bit5 1:��ʼ UART3_DMA �Զ�����, bit0 1:��� FIFO
}

//========================================================================
// ����: void UART4_DMA_Config(void)
// ����: UART4 DMA ��������.
// ����: none.
// ����: none.
// �汾: V1.0, 2021-5-6
//========================================================================
void UART4_DMA_Config(void)
{
	DMA_UR4T_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR4T_STA = 0x00;
	DMA_UR4T_AMT = DMA_TX_LEN;		//���ô������ֽ�����n+1
	DMA_UR4T_TXA = DmaBuffer4;
	DMA_UR4T_CR = 0xc0;			//bit7 1:ʹ�� UART4_DMA, bit6 1:��ʼ UART4_DMA �Զ�����

	DMA_UR4R_CFG = 0x80;		//bit7 1:Enable Interrupt
	DMA_UR4R_STA = 0x00;
	DMA_UR4R_AMT = DMA_RX_LEN;		//���ô������ֽ�����n+1
	DMA_UR4R_RXA = DmaBuffer4;
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
void SetTimer2Baudraye(u16 dat)  // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
{
	AUXR &= ~(1<<4);    //Timer stop
	AUXR &= ~(1<<3);    //Timer2 set As Timer
	AUXR |=  (1<<2);    //Timer2 set as 1T mode
	T2H = dat / 256;
	T2L = dat % 256;
	IE2  &= ~(1<<2);    //��ֹ�ж�
	AUXR |=  (1<<4);    //Timer run enable
}

//========================================================================
// ����: void UART1_config(u8 brt)
// ����: UART1��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_config(u8 brt)    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
{
	/*********** ������ʹ�ö�ʱ��2 *****************/
	if(brt == 2)
	{
		AUXR |= 0x01;       //S1 BRT Use Timer2;
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate1);
	}

	/*********** ������ʹ�ö�ʱ��1 *****************/
	else
	{
		TR1 = 0;
		AUXR &= ~0x01;      //S1 BRT Use Timer1;
		AUXR |=  (1<<6);    //Timer1 set as 1T mode
		TMOD &= ~(1<<6);    //Timer1 set As Timer
		TMOD &= ~0x30;      //Timer1_16bitAutoReload;
		TH1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) / 256);
		TL1 = (u8)((65536UL - (MAIN_Fosc / 4) / Baudrate1) % 256);
		ET1 = 0;    //��ֹ�ж�
		TR1  = 1;
	}
	/*************************************************/

	SCON = (SCON & 0x3f) | 0x40;    //UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����
//  PS  = 1;    //�����ȼ��ж�
	ES  = 1;    //�����ж�
	REN = 1;    //�������
	P_SW1 &= 0x3f;
	P_SW1 |= 0x00;      //UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4

	RX1_TimeOut = 0;
}

//========================================================================
// ����: void UART2_config(u8 brt)
// ����: UART2��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART2_config(u8 brt)    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
{
    /*********** �����ʹ̶�ʹ�ö�ʱ��2 *****************/
    if(brt == 2)
    {
        SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate2);

        S2CON &= ~(1<<7);   // 8λ����, 1λ��ʼλ, 1λֹͣλ, ��У��
//        IE2   |= 1;         //�����ж�
        S2CON |= (1<<4);    //�������
        P_SW2 &= ~0x01;     //UART2 switch to: 0: P1.0 P1.1
//        P_SW2 |= 1;         //UART2 switch to: 1: P4.6 P4.7
    }
}

//========================================================================
// ����: void UART3_config(u8 brt)
// ����: UART3��ʼ��������
// ����: brt: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART3_config(u8 brt)    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer3��������.
{
	if(brt == 2)
	{
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate3);
		S3CON = 0x10;       //8λ����, ʹ��Timer2�������ʷ�����, �������
	}
	else
	{
		S3CON = 0x50;       //8λ����, ʹ��Timer3�������ʷ�����, �������
		T3H = (65536UL - (MAIN_Fosc / 4) / Baudrate3) / 256;
		T3L = (65536UL - (MAIN_Fosc / 4) / Baudrate3) % 256;
		T4T3M &= 0xf0;
		T4T3M |= 0x0a;
	}
	//IE2 |= 0x08;          //����UART3�ж�
	P_SW2 &= ~0x02;       //UART3 switch bit1 to: 0: P0.0 P0.1
	//P_SW2 |= 0x02;      //UART3 switch bit1 to: 1: P5.0 P5.1
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
		SetTimer2Baudraye(65536UL - (MAIN_Fosc / 4) / Baudrate4);
		S4CON = 0x10;       //8λ����, ʹ��Timer2�������ʷ�����, �������
	}
	else
	{
		S4CON = 0x50;       //8λ����, ʹ��Timer4�������ʷ�����, �������
		T4H = (65536UL - (MAIN_Fosc / 4) / Baudrate4) / 256;
		T4L = (65536UL - (MAIN_Fosc / 4) / Baudrate4) % 256;
		T4T3M &= 0x0f;
		T4T3M |= 0xa0;
	}
	//IE2 |= 0x10;          //����UART4�ж�
	P_SW2 &= ~0x04;       //UART4 switch bit2 to: 0: P0.2 P0.3
	P_SW2 |= 0x04;      //UART4 switch bit2 to: 1: P5.2 P5.3
}


//========================================================================
// ����: void UART1_int (void) interrupt UART1_VECTOR
// ����: UART1�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_int (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
        RX1_Cnt++;
		RX1_TimeOut = 5;    //���5msû�յ��µ����ݣ��ж�һ�����ݽ������
	}

	if(TI)
	{
		TI = 0;
        Tx1SendFlag = 0;
	}
}

//========================================================================
// ����: void UART2_int (void) interrupt UART2_VECTOR
// ����: UART2�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
//void UART2_int (void) interrupt 8
//{
//    if((S2CON & 1) != 0)
//    {
//        S2CON &= ~1;    //Clear Rx flag
//        RX2_Buffer[RX2_Cnt] = S2BUF;
//        if(++RX2_Cnt >= UART2_BUF_LENGTH)   RX2_Cnt = 0;
//    }

//    if((S2CON & 2) != 0)
//    {
//        S2CON &= ~2;    //Clear Tx flag
//        B_TX2_Busy = 0;
//    }

//}

//========================================================================
// ����: void UART3_int (void) interrupt UART3_VECTOR
// ����: UART3�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
//void UART3_int (void) interrupt 17
//{
//    if((S3CON & 0x01) != 0)
//    {
//        S3CON &= ~0x01;    //Clear Rx flag
//        RX3_Buffer[RX3_Cnt] = S3BUF;
//        if(++RX3_Cnt >= UART3_BUF_LENGTH)   RX3_Cnt = 0;
//    }

//    if((S3CON & 0x02) != 0)
//    {
//        S3CON &= ~0x02;    //Clear Tx flag
//        B_TX3_Busy = 0;
//    }
//}

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
// ����: void timer0 (void) interrupt 1
// ����: ��ʱ��0�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void timer0 (void) interrupt 1
{
    B_1ms = 1;      //1ms��־
}

//========================================================================
// ����: void UART_DMA_Interrupt (void)
// ����: UART DMA�жϺ���
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2021-5-8
// ��ע: 
//========================================================================
void UART_DMA_Interrupt(void) interrupt 13
{
	//======= UART1 DMA ================
	if (DMA_UR1T_STA & 0x01)	//�������
	{
		DMA_UR1T_STA &= ~0x01;
		DmaTx1Flag = 1;
	}
	if (DMA_UR1T_STA & 0x04)	//���ݸ���
	{
		DMA_UR1T_STA &= ~0x04;
	}
	
	if (DMA_UR1R_STA & 0x01)	//�������
	{
		DMA_UR1R_STA &= ~0x01;
		DmaRx1Flag = 1;
	}
	if (DMA_UR1R_STA & 0x02)	//���ݶ���
	{
		DMA_UR1R_STA &= ~0x02;
	}
	//======= UART2 DMA ================
	if (DMA_UR2T_STA & 0x01)	//�������
	{
		DMA_UR2T_STA &= ~0x01;
		DmaTx2Flag = 1;
	}
	if (DMA_UR2T_STA & 0x04)	//���ݸ���
	{
		DMA_UR2T_STA &= ~0x04;
	}
	
	if (DMA_UR2R_STA & 0x01)	//�������
	{
		DMA_UR2R_STA &= ~0x01;
		DmaRx2Flag = 1;
	}
	if (DMA_UR2R_STA & 0x02)	//���ݶ���
	{
		DMA_UR2R_STA &= ~0x02;
	}
	//======= UART3 DMA ================
	if (DMA_UR3T_STA & 0x01)	//�������
	{
		DMA_UR3T_STA &= ~0x01;
		DmaTx3Flag = 1;
	}
	if (DMA_UR3T_STA & 0x04)	//���ݸ���
	{
		DMA_UR3T_STA &= ~0x04;
	}
	
	if (DMA_UR3R_STA & 0x01)	//�������
	{
		DMA_UR3R_STA &= ~0x01;
		DmaRx3Flag = 1;
	}
	if (DMA_UR3R_STA & 0x02)	//���ݶ���
	{
		DMA_UR3R_STA &= ~0x02;
	}
	//======= UART4 DMA ================
	if (DMA_UR4T_STA & 0x01)	//�������
	{
		DMA_UR4T_STA &= ~0x01;
		DmaTx4Flag = 1;
	}
	if (DMA_UR4T_STA & 0x04)	//���ݸ���
	{
		DMA_UR4T_STA &= ~0x04;
	}
	
	if (DMA_UR4R_STA & 0x01)	//�������
	{
		DMA_UR4R_STA &= ~0x01;
		DmaRx4Flag = 1;
	}
	if (DMA_UR4R_STA & 0x02)	//���ݶ���
	{
		DMA_UR4R_STA &= ~0x02;
	}
}
