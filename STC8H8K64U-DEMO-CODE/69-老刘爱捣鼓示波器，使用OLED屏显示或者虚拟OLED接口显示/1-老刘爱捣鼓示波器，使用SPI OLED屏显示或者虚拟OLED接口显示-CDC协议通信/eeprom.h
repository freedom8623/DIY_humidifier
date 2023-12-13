#ifndef EEPROM_H
#define EEPROM_H

#include "intrins.h"

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

#define IAP_STANDBY()   IAP_CMD = 0     //IAP���������ֹ��
#define IAP_READ()      IAP_CMD = 1     //IAP��������
#define IAP_WRITE()     IAP_CMD = 2     //IAPд������
#define IAP_ERASE()     IAP_CMD = 3     //IAP��������

#define IAP_ENABLE()    IAP_CONTR = IAP_EN
#define IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)
/*�����׵�ַ
Start Address of Sector
Each Sector contains 512 bytes*/
#define IAP_ADDRESS 0x0000

bit EEPROM_Save(uint8 *s, char para_num);
//void EEPROM_Read(uint8 *s, char para_num);
void EEPROM_read_n(uint16 EE_address,uint8 *DataAddress,uint8 length);

#endif
