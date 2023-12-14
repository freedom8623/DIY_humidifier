
#include "Pwm.h"

/*************  本地变量声明    **************/

extern unsigned char PWM1_Duty1;
void Pwm_init(void)
{
	
	 P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能
		PWM1_Duty1 = 222;
	 //设置初始占空比
		PWM1_Duty = PWM1_on;
   // PWM2_Duty = 500;
	 
	 
	  PWMA_CCER1 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    
    PWMA_CCMR1 = 0x60; //通道模式配置

  
	
		PWMA_ETRPS |= 11;
    PWMA_CCER1 = 0x05; //配置通道输出使能和极性  1PN 


    PWMA_ARRH = (u8)(PWM_PERIOD >> 8); //设置周期时间 N = （T目标*时钟频率）/2 =111  占空比为50%  108khz=9.026us
    PWMA_ARRL = (u8)PWM_PERIOD;

    PWMA_ENO = 0x00;
   
    PWMA_ENO |= ENO1N; //使能输出

		
		
		PWMA_PS = 0x00;  //高级 PWM 通道输出脚选择位
    PWMA_PS |= PWM1_1; //选择 PWM1_3 通道P:P1.0  N:P1.1(雾化器)

		PWMA_BKR = 0x80; //使能主输出
    PWMA_CR1 |= 0x01; //开始计时
	



	
 }
 
 //========================================================================
// 函数: UpdatePwm(void)
// 描述: 更新PWM占空比. 
// 参数: none.
// 返回: none.
//========================================================================
void UpdatePwm(void)
{
    PWMA_CCR1H = (u8)(PWM1_Duty >> 8); //设置占空比时间
    PWMA_CCR1L = (u8)(PWM1_Duty);
   // PWMA_CCR2H = (u8)(PWM2_Duty >> 8); //设置占空比时间
  //  PWMA_CCR2L = (u8)(PWM2_Duty);

}

void Setting_Pwm(u16 Duty1)
{
	
		PWM1_Duty = Duty1;
		UpdatePwm();
}


 