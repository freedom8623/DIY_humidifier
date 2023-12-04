#include "Pwm.h"

/*************  本地变量声明    **************/
bit B_1ms;          //1ms标志

bit PWM1_Flag;
bit PWM2_Flag;

u16 PWM1_Duty;
u16 PWM2_Duty;

void Pwm_init(void)
{
	
	 P_SW2 |= 0x80;  //扩展寄存器(XFR)访问使能
	 
	 PWM1_Flag = 0;
   PWM2_Flag = 0;
	 //设置初始占空比
	  PWM1_Duty = 500;
    PWM2_Duty = 500;
	 
	 
	  PWMA_CCER1 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWMA_CCER2 = 0x00;
    PWMA_CCMR1 = 0x68; //通道模式配置
    PWMA_CCMR2 = 0x68;
  
    PWMA_CCER1 = 0x55; //配置通道输出使能和极性  1PN  /2 PN


    PWMA_ARRH = (u8)(PWM_PERIOD >> 8); //设置周期时间
    PWMA_ARRL = (u8)PWM_PERIOD;

    PWMA_ENO = 0x00;
    PWMA_ENO |= ENO1P; //使能输出
    PWMA_ENO |= ENO1N; //使能输出
    PWMA_ENO |= ENO2P; //使能输出
    PWMA_ENO |= ENO2N; //使能输出
		
		PWMA_PS = 0x00;  //高级 PWM 通道输出脚选择位
    PWMA_PS |= PWM1_1; //选择 PWM1_3 通道
    PWMA_PS |= PWM2_2; //选择 PWM2_3 通道
		
		 PWMA_BKR = 0x80; //使能主输出
    PWMA_CR1 |= 0x01; //开始计时



	
 }
 
 //========================================================================
// 函数: UpdatePwm(void)
// 描述: 更新PWM占空比. 
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void UpdatePwm(void)
{
    PWMA_CCR1H = (u8)(PWM1_Duty >> 8); //设置占空比时间
    PWMA_CCR1L = (u8)(PWM1_Duty);
    PWMA_CCR2H = (u8)(PWM2_Duty >> 8); //设置占空比时间
    PWMA_CCR2L = (u8)(PWM2_Duty);

}


 