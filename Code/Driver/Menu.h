#ifndef __MENU_H
#define __MENU_H	 
#include "main.h"  
#include "interrupt.h"
#include "oled.h"
#include "DHT.h"
#include "stdio.h"


typedef struct
{
    u8 current;//当前状态索引号
	
    u8 enter; //确定  长按进入菜单   长按返回
    u8 next;  //+
    u8 last; //-
    u8 back; //一键关闭喷雾
	
    void (*current_operation)(void); //当前状态应该执行的操作
} Menu_table;


//界面函数定义
void Page0(void);
void Key_Proc(void);
void Page1(void);
void Page2(void);
void Page3(void);
void Page4(void);
void Page5(void);	
void Page6(void);
#endif	
