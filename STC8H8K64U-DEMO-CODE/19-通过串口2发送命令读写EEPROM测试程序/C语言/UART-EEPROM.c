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
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/


/*************  ��������˵��  **************

�����̻���STC8H8K64UΪ����оƬ��ʵ����9���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

ͨ������2(P4.6 P4.7)��STC�ڲ��Դ���EEPROM(FLASH)���ж�д���ԡ�

��FLASH������������д�롢�����Ĳ���������ָ����ַ��

Ĭ�ϲ�����:  115200,8,N,1. 
Ĭ����ʱ��:  22.1184MHz.

������������: (������ĸ�����ִ�Сд)
    W 0x0040 1234567890  --> ��0x0040��ַд���ַ�1234567890.
    R 0x0040 10          --> ��0x0040��ַ����10���ֽ�����. 

ע�⣺����ʱ�����ؽ���"Ӳ��ѡ��"�������û�EEPROM��С��

��ȷ�����������еĵ�ַ��EEPROM���õĴ�С��Χ֮�ڡ�

******************************************/

#include "stc8h.h"       //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "intrins.h"

#define     MAIN_Fosc       22118400L   //������ʱ�ӣ���ȷ����115200�����ʣ�

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;


#define     Baudrate2           115200L
#define     Tmp_Length          100      //��дEEPROM���峤��

#define     UART2_BUF_LENGTH    (Tmp_Length+9)  //���ڻ��峤��

u8  RX2_TimeOut;
u8  TX2_Cnt;    //���ͼ���
u8  RX2_Cnt;    //���ռ���
bit B_TX2_Busy; //����æ��־

u8  xdata   RX2_Buffer[UART2_BUF_LENGTH];   //���ջ���
u8  xdata   tmp[Tmp_Length];        //EEPROM��������


void    UART2_config(u8 brt);   // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
void    PrintString2(u8 *puts);
void    UART2_TxByte(u8 dat);
void    delay_ms(u8 ms);
u8      CheckData(u8 dat);
u16     GetAddress(void);
u8      GetDataLength(void);
void    EEPROM_SectorErase(u16 EE_address);
void    EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 length);
u8      EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length);


/********************* ������ *************************/
void main(void)
{
    u8  i,j;
    u16 addr;
    u8  status;

    P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��

    P0M1 = 0x30;   P0M0 = 0x30;   //����P0.4��P0.5Ϊ©����·(ʵ��������������赽3.3V)
    P1M1 = 0x30;   P1M0 = 0x30;   //����P1.4��P1.5Ϊ©����·(ʵ��������������赽3.3V)
    P2M1 = 0x3c;   P2M0 = 0x3c;   //����P2.2~P2.5Ϊ©����·(ʵ��������������赽3.3V)
    P3M1 = 0x50;   P3M0 = 0x50;   //����P3.4��P3.6Ϊ©����·(ʵ��������������赽3.3V)
    P4M1 = 0x3c;   P4M0 = 0x3c;   //����P4.2~P4.5Ϊ©����·(ʵ��������������赽3.3V)
    P5M1 = 0x0c;   P5M0 = 0x0c;   //����P5.2��P5.3Ϊ©����·(ʵ��������������赽3.3V)
    P6M1 = 0xff;   P6M0 = 0xff;   //����Ϊ©����·(ʵ��������������赽3.3V)
    P7M1 = 0x00;   P7M0 = 0x00;   //����Ϊ׼˫���

    UART2_config(2);    // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
    EA = 1; //�������ж�

    PrintString2("STC8H8K64Uϵ�е�Ƭ��EEPROM���Գ��򣬴���������������:\r\n");    //UART2����һ���ַ���
    PrintString2("W 0x0040 1234567890  --> ��0x0040��ַд���ַ�1234567890.\r\n");   //UART2����һ���ַ���
    PrintString2("R 0x0040 10          --> ��0x0040��ַ����10���ֽ�����.\r\n"); //UART2����һ���ַ���

    while(1)
    {
        delay_ms(1);
        if(RX2_TimeOut > 0)     //��ʱ����
        {
            if(--RX2_TimeOut == 0)
            {
              for(i=0; i<RX2_Cnt; i++)    UART2_TxByte(RX2_Buffer[i]);    //���յ�������ԭ������,���ڲ���

                status = 0xff;  //״̬��һ����0ֵ
                if((RX2_Cnt >= 10) && (RX2_Buffer[1] == ' ') && (RX2_Buffer[8] == ' ')) //�������Ϊ10���ֽ�
                {
                    for(i=0; i<8; i++)
                    {
                        if((RX2_Buffer[i] >= 'a') && (RX2_Buffer[i] <= 'z'))    RX2_Buffer[i] = RX2_Buffer[i] - 'a' + 'A';  //Сдת��д
                    }
                    addr = GetAddress();
                    if(addr < 63488)    //������0~123����
                    {
                        if(RX2_Buffer[0] == 'W')    //д��N���ֽ�
                        {
                            j = RX2_Cnt - 9;
                            if(j > Tmp_Length)  j = Tmp_Length; //Խ����
                            EEPROM_SectorErase(addr);           //��������
                            i = EEPROM_write_n(addr,&RX2_Buffer[9],j);      //дN���ֽ�
                            if(i == 0)
                            {
                                PrintString2("��д��");
                                if(j >= 100)    {UART2_TxByte(j/100+'0');   j = j % 100;}
                                if(j >= 10)     {UART2_TxByte(j/10+'0');    j = j % 10;}
                                UART2_TxByte(j%10+'0');
                                PrintString2("�ֽڣ�\r\n");
                            }
                            else    PrintString2("д�����\r\n");
                            status = 0; //������ȷ
                        }

                        else if(RX2_Buffer[0] == 'R')   //PC���󷵻�N�ֽ�EEPROM����
                        {
                            j = GetDataLength();
                            if(j > Tmp_Length)  j = Tmp_Length; //Խ����
                            if(j > 0)
                            {
                                PrintString2("����");
                                UART2_TxByte(j/10+'0');
                                UART2_TxByte(j%10+'0');
                                PrintString2("���ֽ���������:\r\n");
                                EEPROM_read_n(addr,tmp,j);
                                for(i=0; i<j; i++)  UART2_TxByte(tmp[i]);
                                UART2_TxByte(0x0d);
                                UART2_TxByte(0x0a);
                                status = 0; //������ȷ
                            }
                        }
                    }
                }
                if(status != 0) PrintString2("�������\r\n");
                RX2_Cnt  = 0;   //����ֽ���
            }
        }
    }
}
//========================================================================


//========================================================================
// ����: void delay_ms(u8 ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// �汾: VER1.0
// ����: 2021-3-9
// ��ע: 
//========================================================================
void delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 10000;
          while(--i);   //10T per loop
     }while(--ms);
}

//========================================================================
// ����: u8 CheckData(u8 dat)
// ����: ���ַ�"0~9,A~F��a~f"ת��ʮ������.
// ����: dat: Ҫ�����ַ�.
// ����: 0x00~0x0FΪ��ȷ. 0xFFΪ����.
// �汾: V1.0, 2012-10-22
//========================================================================
u8 CheckData(u8 dat)
{
    if((dat >= '0') && (dat <= '9'))        return (dat-'0');
    if((dat >= 'A') && (dat <= 'F'))        return (dat-'A'+10);
    return 0xff;
}

//========================================================================
// ����: u16    GetAddress(void)
// ����: ����������뷽ʽ�ĵ�ַ.
// ����: ��.
// ����: 16λEEPROM��ַ.
// �汾: V1.0, 2013-6-6
//========================================================================
u16 GetAddress(void)
{
    u16 address;
    u8  i,j;
    
    address = 0;
    if((RX2_Buffer[2] == '0') && (RX2_Buffer[3] == 'X'))
    {
        for(i=4; i<8; i++)
        {
            j = CheckData(RX2_Buffer[i]);
            if(j >= 0x10)   return 65535;   //error
            address = (address << 4) + j;
        }
        return (address);
    }
    return  65535;  //error
}

/**************** ��ȡҪ�������ݵ��ֽ��� ****************************/
u8 GetDataLength(void)
{
    u8  i;
    u8  length;
    
    length = 0;
    for(i=9; i<RX2_Cnt; i++)
    {
        if(CheckData(RX2_Buffer[i]) >= 10)  break;
        length = length * 10 + CheckData(RX2_Buffer[i]);
    }
    return (length);
}


//========================================================================
// ����: void UART2_TxByte(u8 dat)
// ����: ����һ���ֽ�.
// ����: ��.
// ����: ��.
// �汾: V1.0, 2014-6-30
//========================================================================
void UART2_TxByte(u8 dat)
{
    S2BUF = dat;
    B_TX2_Busy = 1;
    while(B_TX2_Busy);
}


//========================================================================
// ����: void PrintString2(u8 *puts)
// ����: ����2�����ַ���������
// ����: puts:  �ַ���ָ��.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void PrintString2(u8 *puts) //����һ���ַ���
{
    for (; *puts != 0;  puts++) UART2_TxByte(*puts);    //����ֹͣ��0����
}

//========================================================================
// ����: void SetTimer2Baudraye(u16 dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void SetTimer2Baudraye(u16 dat)  // ѡ������, 2: ʹ��Timer2��������, ����ֵ: ��Ч.
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
        IE2   |= 1;         //�����ж�
        S2CON |= (1<<4);    //�������
        P_SW2 &= ~0x01; 
        P_SW2 |= 1;         //UART2 switch to: 0: P1.0 P1.1,  1: P4.6 P4.7

        RX2_TimeOut = 0;
        B_TX2_Busy = 0;
        TX2_Cnt = 0;
        RX2_Cnt = 0;
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
void UART2_int (void) interrupt 8
{
    if((S2CON & 1) != 0)
    {
        S2CON &= ~1;    //Clear Rx flag
        RX2_Buffer[RX2_Cnt] = S2BUF;
        if(++RX2_Cnt >= UART2_BUF_LENGTH)   RX2_Cnt = 0;
        RX2_TimeOut = 5;
    }

    if((S2CON & 2) != 0)
    {
        S2CON &= ~2;    //Clear Tx flag
        B_TX2_Busy = 0;
    }
}


#define     IAP_STANDBY()   IAP_CMD = 0     //IAP���������ֹ��
#define     IAP_READ()      IAP_CMD = 1     //IAP��������
#define     IAP_WRITE()     IAP_CMD = 2     //IAPд������
#define     IAP_ERASE()     IAP_CMD = 3     //IAP��������

#define     IAP_ENABLE()    IAP_CONTR = IAP_EN; IAP_TPS = MAIN_Fosc / 1000000
#define     IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)


//========================================================================
// ����: void DisableEEPROM(void)
// ����: ��ֹEEPROM.
// ����: none.
// ����: none.
// �汾: V1.0, 2014-6-30
//========================================================================
void DisableEEPROM(void)        //��ֹ����EEPROM
{
    IAP_CONTR = 0;          //�ر� IAP ����
    IAP_CMD = 0;            //�������Ĵ���
    IAP_TRIG = 0;           //��������Ĵ���
    IAP_ADDRH = 0xff;       //����ַ���õ��� IAP ����
    IAP_ADDRL = 0xff;
}

//========================================================================
// ����: void EEPROM_Trig(void)
// ����: ����EEPROM����.
// ����: none.
// ����: none.
// �汾: V1.0, 2014-6-30
//========================================================================
void EEPROM_Trig(void)
{
    F0 = EA;    //����ȫ���ж�
    EA = 0;     //��ֹ�ж�, ���ⴥ��������Ч
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;                    //����5AH������A5H��IAP�����Ĵ�����ÿ�ζ���Ҫ���
                                        //����A5H��IAP������������������
                                        //CPU�ȴ�IAP��ɺ󣬲Ż����ִ�г���
    _nop_();
    _nop_();
    EA = F0;    //�ָ�ȫ���ж�
}

//========================================================================
// ����: void EEPROM_SectorErase(u16 EE_address)
// ����: ����һ������.
// ����: EE_address:  Ҫ������EEPROM�������е�һ���ֽڵ�ַ.
// ����: none.
// �汾: V1.0, 2014-6-30
//========================================================================
void EEPROM_SectorErase(u16 EE_address)
{
    IAP_ENABLE();                       //���õȴ�ʱ�䣬����IAP��������һ�ξ͹�
    IAP_ERASE();                        //�����, ������������������ı�ʱ����������������
                                        //ֻ������������û���ֽڲ�����512�ֽ�/������
                                        //����������һ���ֽڵ�ַ����������ַ��
    IAP_ADDRH = EE_address / 256;       //��������ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
    IAP_ADDRL = EE_address % 256;       //��������ַ���ֽ�
    EEPROM_Trig();                      //����EEPROM����
    DisableEEPROM();                    //��ֹEEPROM����
}

//========================================================================
// ����: void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 lenth)
// ����: ��N���ֽں���.
// ����: EE_address:  Ҫ������EEPROM���׵�ַ.
//       DataAddress: Ҫ�������ݵ�ָ��.
//       length:      Ҫ�����ĳ���
// ����: 0: д����ȷ.  1: д�볤��Ϊ0����.  2: д�����ݴ���.
// �汾: V1.0, 2014-6-30
//========================================================================
void EEPROM_read_n(u16 EE_address,u8 *DataAddress,u8 length)
{
    IAP_ENABLE();                           //���õȴ�ʱ�䣬����IAP��������һ�ξ͹�
    IAP_READ();                             //���ֽڶ���������ı�ʱ����������������
    do
    {
        IAP_ADDRH = EE_address / 256;       //�͵�ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
        IAP_ADDRL = EE_address % 256;       //�͵�ַ���ֽ�
        EEPROM_Trig();                      //����EEPROM����
        *DataAddress = IAP_DATA;            //��������������
        EE_address++;
        DataAddress++;
    }while(--length);

    DisableEEPROM();
}


//========================================================================
// ����: u8 EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length)
// ����: дN���ֽں���.
// ����: EE_address:  Ҫд���EEPROM���׵�ַ.
//       DataAddress: Ҫд�����ݵ�ָ��.
//       length:      Ҫд��ĳ���
// ����: 0: д����ȷ.  1: д�볤��Ϊ0����.  2: д�����ݴ���.
// �汾: V1.0, 2014-6-30
//========================================================================
u8 EEPROM_write_n(u16 EE_address,u8 *DataAddress,u8 length)
{
    u8  i;
    u16 j;
    u8  *p;
    
    if(length == 0) return 1;   //����Ϊ0����

    IAP_ENABLE();                       //���õȴ�ʱ�䣬����IAP��������һ�ξ͹�
    i = length;
    j = EE_address;
    p = DataAddress;
    IAP_WRITE();                            //�����, ���ֽ�д����
    do
    {
        IAP_ADDRH = EE_address / 256;       //�͵�ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
        IAP_ADDRL = EE_address % 256;       //�͵�ַ���ֽ�
        IAP_DATA  = *DataAddress;           //�����ݵ�IAP_DATA��ֻ�����ݸı�ʱ����������
        EEPROM_Trig();                      //����EEPROM����
        EE_address++;                       //��һ����ַ
        DataAddress++;                      //��һ������
    }while(--length);                       //ֱ������

    EE_address = j;
    length = i;
    DataAddress = p;
    i = 0;
    IAP_READ();                             //��N���ֽڲ��Ƚ�
    do
    {
        IAP_ADDRH = EE_address / 256;       //�͵�ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
        IAP_ADDRL = EE_address % 256;       //�͵�ַ���ֽ�
        EEPROM_Trig();                      //����EEPROM����
        if(*DataAddress != IAP_DATA)        //������������Դ���ݱȽ�
        {
            i = 2;
            break;
        }
        EE_address++;
        DataAddress++;
    }while(--length);

    DisableEEPROM();
    return i;
}

