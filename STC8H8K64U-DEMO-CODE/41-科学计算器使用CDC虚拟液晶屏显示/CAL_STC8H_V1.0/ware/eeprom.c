#include "eeprom.h"


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


void IapIdle()
{

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

char IapRead(unsigned long addr)
{
    u8 xdata dat;
    EEPROM_read_n(addr,&dat,1);
    return dat;
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
    u8 xdata i;
    u16 xdata j;
    u8 xdata *p;
    
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



void IapProgram(unsigned long addr, char dat)
{
    u8 xdata dataq[1] ;
    dataq[0] = dat;
    EEPROM_write_n(addr,dataq,1);
}
void IapErase(unsigned long addr)
{
    IAP_ENABLE();                       //���õȴ�ʱ�䣬����IAP��������һ�ξ͹�
    IAP_ERASE();                        //�����, ������������������ı�ʱ����������������
                                        //ֻ������������û���ֽڲ�����512�ֽ�/������
                                        //����������һ���ֽڵ�ַ����������ַ��
    IAP_ADDRH = addr / 256;       //��������ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
    IAP_ADDRL = addr % 256;       //��������ַ���ֽ�
    EEPROM_Trig();                      //����EEPROM����
    DisableEEPROM();                    //��ֹEEPROM����
}


//IapErase(0x0400);
//P0 = IapRead(0x0400); //P0=0xff
//IapProgram(0x0400, 0x12);
//P1 = IapRead(0x0400); //P1=0x12
