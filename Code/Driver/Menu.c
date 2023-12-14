#include "Menu.h"
#include "interrupt.h"
#include "pwm.h"
//����
struct keys key[];


void (*current_operation_index)(); //��������ָ��
unsigned int  func_index = 0;//��ȡ����ֵ
unsigned int Water_Flag;

//�¶�
unsigned char rec_dat[9] = {'0','0','0','0','0','0','0','0','0'}; //��������
//=====================================
int limit_humit = 80;
char light_mode =0;
extern unsigned char new_light_mode;
extern unsigned int new_limit_humit;

int setting_duty =1;
//========�˵�========================
uchar showtext[16];
uchar showtext2[16];
//current����  enterȷ�� ��������˵� next��һ�� +   last��һ�� -  back���� �����ر�����
int humit = 0;

Menu_table  table[29]=
{
////һ��
//{0, 1, 0, 0,  0,(*Page0)},//	����һ���˵�

//{1, 3, 2, 2,  0,(*Page1)},//һ�����棨���ã���һ������ѡ���һ��
//{2, 4, 1, 1,  0,(*Page2)},//һ������ѡ��ڶ���

//{3, 5, 3, 3,  1,(*Page3)},//��������
//{4, 6, 4, 4,  2,(*Page4)},//��������

//{5, 0, 3, 3,  3,(*Page5)},//�ɹ���ʾ
//{6, 0, 4, 4,  4,(*Page6)},//�ɹ���ʾ

	//һ��
  {0, 0, 0, 0,  1,(*Page0)},//	����һ���˵�
	
	{1, 0, 2, 2,  3,(*Page1)},//һ�����棨���ã���һ������ѡ���һ��
	{2, 0, 1, 1,  4,(*Page2)},//һ������ѡ��ڶ���
	
	{3, 1, 3, 3,  5,(*Page3)},//��������
	{4, 2, 4, 4,  6,(*Page4)},//��������
	
	{5, 3, 3, 3,  0,(*Page5)},//�ɹ���ʾ
	{6, 4, 4, 4,  0,(*Page6)},//�ɹ���ʾ
	
};

void Page0(void)
{
		OLED_ShowString(0,0,"=======0^0======",16);  /*��һ��������X��������λ������Ϊ8/λ���ڶ���������Y����2/λ*/
		OLED_ShowString(0,2,"||",16);OLED_ShowString(112,2,"||",16);
		OLED_ShowString(0,2,"||",16);OLED_ShowString(112,2,"||",16);
		OLED_ShowString(0,4,"||",16);OLED_ShowString(112,4,"||",16);
		OLED_ShowString(0,4,"||",16);OLED_ShowString(112,4,"||",16);
		OLED_ShowString(0,6,"||",16);OLED_ShowString(112,6,"||",16);
		OLED_ShowString(0,6,"||",16);OLED_ShowString(112,6,"||",16);
	
	
		OLED_ShowChinese(32,2,4,16);/*ʪ��*/
		OLED_ShowChinese(48,2,5,16);
		sprintf(showtext,":%c%c%",rec_dat[0],rec_dat[1]);
		humit = rec_dat[0] -'0'+ rec_dat[1] -'0';
		OLED_ShowString(64,2,showtext,16);
		
		OLED_ShowChinese(32,4,8,16);/*ˮλ*/
		OLED_ShowChinese(48,4,9,16);
		OLED_ShowString(64,4,":",16);
		if(Water_Flag == 1){
			
			OLED_ShowChinese(80,4,13,16);/*��*/
		}
		if(Water_Flag == 0){
			
			OLED_ShowChinese(80,4,12,16);/*��*/
		}
	
		OLED_ShowChinese(32,6,10,16);/*��*/
		OLED_ShowChinese(48,6,11,16);
		OLED_ShowString(64,6,":",16);
		
		if(setting_duty == 1){
			
			OLED_ShowChinese(80,6,12,16);/*��*/
		}
		if(setting_duty == 0){
			
			OLED_ShowChinese(80,6,13,16);/*��*/
		}

}

void Page1(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		OLED_ShowString(0,2,">",16);
		OLED_ShowChinese(16,2,6,16); /*����*/
		OLED_ShowChinese(32,2,7,16); 
		OLED_ShowChinese(48,2,4,16);/*ʪ��*/
		OLED_ShowChinese(64,2,5,16);

		
		OLED_ShowChinese(16,4,6,16); /*����*/
		OLED_ShowChinese(32,4,7,16); 
		OLED_ShowChinese(48,4,0,16);/*ʪ��*/
		OLED_ShowChinese(64,4,1,16);
	
}

void Page2(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		
		OLED_ShowChinese(16,2,6,16); /*����*/
		OLED_ShowChinese(32,2,7,16); 
		OLED_ShowChinese(48,2,4,16);/*ʪ��*/
		OLED_ShowChinese(64,2,5,16);

		OLED_ShowString(0,4,">",16);
		OLED_ShowChinese(16,4,6,16); /*����*/
		OLED_ShowChinese(32,4,7,16); 
		OLED_ShowChinese(48,4,0,16);/*�ƹ�*/
		OLED_ShowChinese(64,4,1,16);
	
}
//int setting_humit = 0;


void Page3(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		
		OLED_ShowChinese(16,2,14,16); /*����*/
		OLED_ShowChinese(32,2,15,16); 
		OLED_ShowChinese(48,2,4,16);/*ʪ��*/
		OLED_ShowChinese(64,2,5,16);
	
			sprintf(showtext,":%03d%",limit_humit);
		OLED_ShowString(80,2,showtext,16);
	

	
	
}

void Page4(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		
		OLED_ShowChinese(16,2,14,16); /*����*/
		OLED_ShowChinese(32,2,15,16); 
		OLED_ShowChinese(48,2,0,16);/*�ɹ�*/
		OLED_ShowChinese(64,2,1,16);
	
		sprintf(showtext,":%03c%",light_mode);
		OLED_ShowString(80,2,showtext,16);

	
	
}


void Page5(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		
		OLED_ShowChinese(16,4,6,16); /*����*/
		OLED_ShowChinese(32,4,7,16); 
		OLED_ShowChinese(48,4,16,16);/*�ɹ�*/
		OLED_ShowChinese(64,4,17,16);

		OLED_ShowString(80,4,"^-^",16);

	
	
	
}


void Page6(void)
{
		OLED_ShowChinese(48,0,6,16); /*����*/
		OLED_ShowChinese(64,0,7,16); /*����*/
		OLED_ShowString(0,0,"======",16);OLED_ShowString(80,0,"=====",16);
	
		
		OLED_ShowChinese(16,4,6,16); /*����*/
		OLED_ShowChinese(32,4,7,16); 
		OLED_ShowChinese(48,4,16,16);/*�ɹ�*/
		OLED_ShowChinese(64,4,17,16);
	
		
		OLED_ShowString(80,4,"^-^",16);

	
	
}



//��������
void Key_Proc(void)
{
		if(key[0].single_flag == 1)//����SW1 �̰�
	{	
		func_index=table[func_index].enter;//��ȡenter������
		OLED_Clear();
		key[0].single_flag = 0;
	}

//==============================================			
	 if(key[1].single_flag == 1)//����
	{
			func_index=table[func_index].next;//��ȡnext������
			if(func_index == 3)
			{
				limit_humit++;
				if(limit_humit >= 100)limit_humit =0;
				
					
			}
			if(func_index == 4)
			{
				light_mode++;
				if(light_mode >= 7)light_mode =0;
			}
			new_limit_humit=limit_humit;
			new_light_mode = light_mode;
			OLED_Clear();
			
			key[1].single_flag = 0;
	
	}
//==============================================	
	 if(key[2].single_flag == 1)//����
	 {
		func_index=table[func_index].last;//��ȡlast������
			if(func_index == 3)
			{
				limit_humit--;
				if(limit_humit <= 0)limit_humit =100;
			}
			if(func_index == 4)
			{
				
				light_mode--;
				if(light_mode <= 0)light_mode =7;
			}
			new_limit_humit=limit_humit;
			new_light_mode = light_mode;
		 
		OLED_Clear();
		key[2].single_flag = 0;
	
	}
//==============================================		
	if(key[3].single_flag == 1)//�ر�
	{
		func_index=table[func_index].back;//��ȡlast������
		OLED_Clear();
		
		key[3].single_flag = 0;
	
	}
 
		if(key[3].longkey_flag == 1)//�����ر�����;
	{
		  if(func_index==0)//��ȡlast������
	{
				setting_duty ^= 1;
			
				if(setting_duty == 0)
				{
				
				PWMA_CCR1H = (u8)(PWM1_off >> 8); //����ռ�ձ�ʱ��
				PWMA_CCR1L = (u8)(PWM1_off);
				
				}
				if(setting_duty == 1 )
				{
				PWMA_CCR1H = (u8)(PWM1_on >> 8); //����ռ�ձ�ʱ��
				PWMA_CCR1L = (u8)(PWM1_on);
				}
				key[3].longkey_flag = 0;
		}
	}
	
	if(new_limit_humit < humit)
	{
				PWMA_CCR1H = (u8)(PWM1_off >> 8); //����ռ�ձ�ʱ��
				PWMA_CCR1L = (u8)(PWM1_off);
	}
	current_operation_index=table[func_index].current_operation;//ִ�е�ǰ����������Ӧ�Ĺ��ܺ�����
  (*current_operation_index)();
}








