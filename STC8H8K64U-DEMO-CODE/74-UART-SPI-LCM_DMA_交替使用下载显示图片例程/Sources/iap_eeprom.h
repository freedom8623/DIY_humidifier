/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#ifndef	__IAP_EEPROM_H
#define	__IAP_EEPROM_H

#define EE_ADDRESS  0x0000  //�����EEPROM��ʼ��ַ
//========================================================================
//                               IAP����
//========================================================================

//sfr IAP_CMD   = 0xC5;
#define		IAP_STANDBY()	IAP_CMD = 0		//IAP���������ֹ��
#define		IAP_READ()		IAP_CMD = 1		//IAP��������
#define		IAP_WRITE()		IAP_CMD = 2		//IAPд������
#define		IAP_ERASE()		IAP_CMD = 3		//IAP��������

//sfr IAP_TRIG  = 0xC6;
#define 	IAP_TRIG()	IAP_TRIG = 0x5A,	IAP_TRIG = 0xA5		/* IAP�������� */

//							            7    6    5      4    3   2  1   0   Reset Value
//sfr IAP_CONTR = 0xC7;		IAPEN SWBS SWRST CFAIL  -   -  -   -   0000,x000	//IAP Control Register
#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)

#define	IAP_ENABLE()		IAP_CONTR = IAP_EN; IAP_TPS = MAIN_Fosc / 1000000
#define	IAP_DISABLE()		IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff


void	DisableEEPROM(void);
void 	EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
void 	EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);
void	EEPROM_SectorErase(u16 EE_address);

#endif
