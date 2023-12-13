#ifndef __MENU_H
#define __MENU_H	 
#include "main.h"  
#include "interrupt.h"
#include "oled.h"
#include "DHT.h"
#include "stdio.h"


typedef struct
{
    u8 current;//��ǰ״̬������
	
    u8 enter; //ȷ��  ��������˵�   ��������
    u8 next;  //+
    u8 last; //-
    u8 back; //һ���ر�����
	
    void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���
} Menu_table;


//���溯������
void Page0(void);
void Key_Proc(void);
void Page1(void);
void Page2(void);
void Page3(void);
void Page4(void);
void Page5(void);	
void Page6(void);
#endif	
