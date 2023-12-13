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
//#define PRINTF_HID              //printf���ֱ���ض���USB HID�ӿڣ�����"usb.h"ͷ�ļ�֮ǰ

#include "../comm/STC8h.h"  //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "../comm/usb.h"     //USB���Լ���λ����ͷ�ļ�
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include "spi.h"
#include "middle.h"
#include "set.h"
#include "menu.h"


char  *USER_DEVICEDESC = NULL;
char  *USER_PRODUCTDESC = NULL;
char  *USER_STCISPCMD = "@STCISP#";                      //�����Զ���λ��ISP�����û��ӿ�����

//P3.2�ڰ�����λ�������
u8 xdata  Key_Flag;
u16 xdata Key_cnt;

void sys_init();
void KeyResetScan(void);


void main()
{
    static u8 xdata Init_flag=0;
    u8 xdata Key_Num=0;    
    P_SW2 |= 0x80;  //XFR����ʹ��
    
    P0M1 = 0x00;   P0M0 = 0x00;   //����Ϊ׼˫���
    P1M1 = 0x00;   P1M0 = 0x00;   //����Ϊ׼˫���
    P2M1 = 0x00;   P2M0 = 0x00;   //����Ϊ׼˫���
    P3M1 = 0x00;   P3M0 = 0x00;   //����Ϊ׼˫���
    P4M1 = 0x00;   P4M0 = 0x00;   //����Ϊ׼˫���
    P5M1 = 0x00;   P5M0 = 0x00;   //����Ϊ׼˫���
    P6M1 = 0x00;   P6M0 = 0x00;   //����Ϊ׼˫���
    P7M1 = 0x00;   P7M0 = 0x00;   //����Ϊ׼˫���   

    P3M0 &= ~0x03;
    P3M1 |= 0x03;
 
    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));
    USBCLK = 0x00;
    USBCON = 0x90;

    usb_init();
    Timer0_init();
    Menu_Init();    
    
    /* �����ж� */
    IE2 |= 0x80;   //IE2��ص��ж�λ����ʹ�ܺ���Ҫ��������EUSB
    EA = 1;
  

    while (1)
    {
        delay_ms(1);
        if(DeviceState != DEVSTATE_CONFIGURED)  //�ж�USB�豸�Ƿ��������
            continue;
        if (bUsbOutReady)
        {
            if ((UsbOutBuffer[0] == 'K') &&(UsbOutBuffer[1] == 'E') &&(UsbOutBuffer[2] == 'Y') &&(UsbOutBuffer[3] == 'P'))
            {
                if( Init_flag==0 )
                {
                    Init_flag = 1;
                    OLED_LightSet(255);
                    OLED12864_ScrollStop();
                    OLED_DisplayOn();
                    Menu_Display();
                    Screen_Clear();
                } 
                
                Key_Num = CDC_KeyRead( UsbOutBuffer[5] );
            }
            else
            {
                memcpy(UsbInBuffer, UsbOutBuffer, OutNumber);      //ԭ·����, ���ڲ���
                usb_IN(OutNumber);
            }
            usb_OUT_done();
        }                  
        delay_ms(9);            
        Menu_Deal(&Key_Num);
        Key_Num = 0;
    }
}