#include "Pwm.h"

/*************  ���ر�������    **************/
bit B_1ms;          //1ms��־

bit PWM1_Flag;
bit PWM2_Flag;

u16 PWM1_Duty;
u16 PWM2_Duty;

void Pwm_init(void)
{
	
	 P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��
	 
	 PWM1_Flag = 0;
   PWM2_Flag = 0;
	 //���ó�ʼռ�ձ�
	  PWM1_Duty = 500;
    PWM2_Duty = 500;
	 
	 
	  PWMA_CCER1 = 0x00; //д CCMRx ǰ���������� CCxE �ر�ͨ��
    PWMA_CCER2 = 0x00;
    PWMA_CCMR1 = 0x68; //ͨ��ģʽ����
    PWMA_CCMR2 = 0x68;
  
    PWMA_CCER1 = 0x55; //����ͨ�����ʹ�ܺͼ���  1PN  /2 PN


    PWMA_ARRH = (u8)(PWM_PERIOD >> 8); //��������ʱ��
    PWMA_ARRL = (u8)PWM_PERIOD;

    PWMA_ENO = 0x00;
    PWMA_ENO |= ENO1P; //ʹ�����
    PWMA_ENO |= ENO1N; //ʹ�����
    PWMA_ENO |= ENO2P; //ʹ�����
    PWMA_ENO |= ENO2N; //ʹ�����
		
		PWMA_PS = 0x00;  //�߼� PWM ͨ�������ѡ��λ
    PWMA_PS |= PWM1_1; //ѡ�� PWM1_3 ͨ��
    PWMA_PS |= PWM2_2; //ѡ�� PWM2_3 ͨ��
		
		 PWMA_BKR = 0x80; //ʹ�������
    PWMA_CR1 |= 0x01; //��ʼ��ʱ



	
 }
 
 //========================================================================
// ����: UpdatePwm(void)
// ����: ����PWMռ�ձ�. 
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(void)
{
    PWMA_CCR1H = (u8)(PWM1_Duty >> 8); //����ռ�ձ�ʱ��
    PWMA_CCR1L = (u8)(PWM1_Duty);
    PWMA_CCR2H = (u8)(PWM2_Duty >> 8); //����ռ�ձ�ʱ��
    PWMA_CCR2L = (u8)(PWM2_Duty);

}


 