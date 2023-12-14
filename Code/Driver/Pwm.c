
#include "Pwm.h"

/*************  ���ر�������    **************/

extern unsigned char PWM1_Duty1;
void Pwm_init(void)
{
	
	 P_SW2 |= 0x80;  //��չ�Ĵ���(XFR)����ʹ��
		PWM1_Duty1 = 222;
	 //���ó�ʼռ�ձ�
		PWM1_Duty = PWM1_on;
   // PWM2_Duty = 500;
	 
	 
	  PWMA_CCER1 = 0x00; //д CCMRx ǰ���������� CCxE �ر�ͨ��
    
    PWMA_CCMR1 = 0x60; //ͨ��ģʽ����

  
	
		PWMA_ETRPS |= 11;
    PWMA_CCER1 = 0x05; //����ͨ�����ʹ�ܺͼ���  1PN 


    PWMA_ARRH = (u8)(PWM_PERIOD >> 8); //��������ʱ�� N = ��TĿ��*ʱ��Ƶ�ʣ�/2 =111  ռ�ձ�Ϊ50%  108khz=9.026us
    PWMA_ARRL = (u8)PWM_PERIOD;

    PWMA_ENO = 0x00;
   
    PWMA_ENO |= ENO1N; //ʹ�����

		
		
		PWMA_PS = 0x00;  //�߼� PWM ͨ�������ѡ��λ
    PWMA_PS |= PWM1_1; //ѡ�� PWM1_3 ͨ��P:P1.0  N:P1.1(����)

		PWMA_BKR = 0x80; //ʹ�������
    PWMA_CR1 |= 0x01; //��ʼ��ʱ
	



	
 }
 
 //========================================================================
// ����: UpdatePwm(void)
// ����: ����PWMռ�ձ�. 
// ����: none.
// ����: none.
//========================================================================
void UpdatePwm(void)
{
    PWMA_CCR1H = (u8)(PWM1_Duty >> 8); //����ռ�ձ�ʱ��
    PWMA_CCR1L = (u8)(PWM1_Duty);
   // PWMA_CCR2H = (u8)(PWM2_Duty >> 8); //����ռ�ձ�ʱ��
  //  PWMA_CCR2L = (u8)(PWM2_Duty);

}

void Setting_Pwm(u16 Duty1)
{
	
		PWM1_Duty = Duty1;
		UpdatePwm();
}


 