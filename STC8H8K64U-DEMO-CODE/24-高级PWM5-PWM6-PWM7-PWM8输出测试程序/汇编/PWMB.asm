;/*---------------------------------------------------------------------*/
;/* --- STC MCU Limited ------------------------------------------------*/
;/* --- STC 1T Series MCU Demo Programme -------------------------------*/
;/* --- Mobile: (86)13922805190 ----------------------------------------*/
;/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
;/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
;/* --- Web: www.STCAI.com ---------------------------------------------*/
;/* --- Web: www.STCMCUDATA.com ----------------------------------------*/
;/* --- BBS: www.STCAIMCU.com ------------------------------------------*/
;/* --- QQ:  800003751 -------------------------------------------------*/
;/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
;/*---------------------------------------------------------------------*/


;/************* ����˵��    **************

;�����̻���STC8H8K64UΪ����оƬ��ʵ����9���б�д���ԣ�STC8Hϵ��оƬ��ͨ�òο�.

;�߼�PWM��ʱ�� PWM5,PWM6,PWM7,PWM8 ÿ��ͨ�����ɶ���ʵ��PWM���.

;4��ͨ��PWM������Ҫ���ö�Ӧ����ڣ���ͨ��ʾ�����۲�������ź�.

;PWM���ں�ռ�ձȿ��Ը�����Ҫ�������ã���߿ɴ�65535.

;����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

;******************************************/

$include (../../comm/STC8H.INC)

;/****************************** �û������ ***********************************/

Fosc_KHZ    EQU 24000   ;24000KHZ

STACK_POIRTER   EQU     0D0H    ;��ջ��ʼ��ַ

Timer0_Reload   EQU     (65536 - Fosc_KHZ)  ; Timer 0 �ж�Ƶ��, 1000��/��

;*******************************************************************
;*******************************************************************


;*******************************************************************
;*******************************************************************

;*************  ���ر�������    **************/
PWM5_Flag       BIT     20H.0
PWM6_Flag       BIT     20H.1
PWM7_Flag       BIT     20H.2
PWM8_Flag       BIT     20H.3

PWM5_Duty_H     DATA    30H
PWM5_Duty_L     DATA    31H
PWM6_Duty_H     DATA    32H
PWM6_Duty_L     DATA    33H
PWM7_Duty_H     DATA    34H
PWM7_Duty_L     DATA    35H
PWM8_Duty_H     DATA    36H
PWM8_Duty_L     DATA    37H

;*******************************************************************
;*******************************************************************
        ORG     0000H               ;reset
        LJMP    F_Main

        ORG     000BH               ;1  Timer0 interrupt
        LJMP    F_Timer0_Interrupt

;******************** ������ **************************/
        ORG     0100H       ;reset
F_Main:
    ORL     P_SW2, #080H    ;��չ�Ĵ���(XFR)����ʹ��

    MOV     P0M1, #30H     ;����P0.4��P0.5Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P0M0, #30H
    MOV     P1M1, #30H     ;����P1.4��P1.5Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P1M0, #30H
    MOV     P2M1, #3cH     ;����P2.2~P2.5Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P2M0, #3cH
    MOV     P3M1, #50H     ;����P3.4��P3.6Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P3M0, #50H
    MOV     P4M1, #3cH     ;����P4.2~P4.5Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P4M0, #3cH
    MOV     P5M1, #0cH     ;����P5.2��P5.3Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P5M0, #0cH
    MOV     P6M1, #0ffH    ;����Ϊ©����·(ʵ��������������赽3.3V)
    MOV     P6M0, #0ffH
    MOV     P7M1, #00H     ;����Ϊ׼˫���
    MOV     P7M0, #00H
    
    MOV     SP, #STACK_POIRTER
    MOV     PSW, #0
    USING   0       ;ѡ���0��R0~R7

;================= �û���ʼ������ ====================================
    CLR     PWM5_Flag
    CLR     PWM6_Flag
    CLR     PWM7_Flag
    CLR     PWM8_Flag
    MOV     PWM5_Duty_L, #0
    MOV     PWM5_Duty_H, #0
    MOV     PWM6_Duty_L, #LOW 256
    MOV     PWM6_Duty_H, #HIGH 256
    MOV     PWM7_Duty_L, #LOW 512
    MOV     PWM7_Duty_H, #HIGH 512
    MOV     PWM8_Duty_L, #LOW 1024
    MOV     PWM8_Duty_H, #HIGH 1024

    CLR     TR0
    ORL     AUXR, #(1 SHL 7)    ; Timer0_1T();
    ANL     TMOD, #NOT 04H      ; Timer0_AsTimer();
    ANL     TMOD, #NOT 03H      ; Timer0_16bitAutoReload();
    MOV     TH0, #Timer0_Reload / 256   ;Timer0_Load(Timer0_Reload);
    MOV     TL0, #Timer0_Reload MOD 256
    SETB    ET0         ; Timer0_InterruptEnable();
    SETB    TR0         ; Timer0_Run();
    SETB    EA          ; �����ж�
    
    LCALL   F_PWM_Init          ; PWM��ʼ��

;=================== ��ѭ�� ==================================
L_Main_Loop:

    LJMP    L_Main_Loop

;========================================================================
; ����: F_PWM_Init
; ����: PWM��ʼ������.
; ����: none
; ����: none.
; �汾: V1.0, 2021-3-3
;========================================================================
F_PWM_Init:
    CLR     A                   ;д CCMRx ǰ���������� CCxE �ر�ͨ��
    MOV     DPTR,#PWMB_CCER1
    MOVX    @DPTR,A
    MOV     DPTR,#PWMB_CCER2
    MOVX    @DPTR,A
    MOV     A,#068H             ;���� PWMx ģʽ1 ���
    MOV     DPTR,#PWMB_CCMR1
    MOVX    @DPTR,A
    MOV     DPTR,#PWMB_CCMR2
    MOVX    @DPTR,A
    MOV     DPTR,#PWMB_CCMR3
    MOVX    @DPTR,A
    MOV     DPTR,#PWMB_CCMR4
    MOVX    @DPTR,A
    MOV     A,#033H             ;����ͨ�����ʹ�ܺͼ���
    MOV     DPTR,#PWMB_CCER1
    MOVX    @DPTR,A
    MOV     DPTR,#PWMB_CCER2
    MOVX    @DPTR,A

    MOV     A,#3                ;��������ʱ��
    MOV     DPTR,#PWMB_ARRH
    MOVX    @DPTR,A
    MOV     A,#0FFH
    MOV     DPTR,#PWMB_ARRL
    MOVX    @DPTR,A

    MOV     A,#055H             ;ʹ�� PWM5~8 ���
    MOV     DPTR,#PWMB_ENO
    MOVX    @DPTR,A
    MOV     A,#00H              ;�߼� PWM ͨ�������ѡ��λ, P2
    MOV     DPTR,#PWMB_PS
    MOVX    @DPTR,A
    MOV     A,#080H             ;ʹ�������
    MOV     DPTR,#PWMB_BKR
    MOVX    @DPTR,A

    MOV     DPTR,#PWMB_CR1
    MOVX    A,@DPTR
    ORL     A,#01H              ;��ʼ��ʱ
    MOVX    @DPTR,A
    RET

;========================================================================
; ����: F_UpdatePwm
; ����: ����PWMռ�ձ�ֵ. 
; ����: [PWMn_Duty_H PWMn_Duty_L]: pwmռ�ձ�ֵ.
; ����: none.
; �汾: V1.0, 2021-3-3
;========================================================================
F_UpdatePwm:
    MOV     A, PWM5_Duty_H      ;����ռ�ձ�ʱ��
    MOV     DPTR, #PWMB_CCR5H
    MOVX    @DPTR, A
    MOV     A, PWM5_Duty_L
    MOV     DPTR, #PWMB_CCR5L
    MOVX    @DPTR, A

    MOV     A, PWM6_Duty_H      ;����ռ�ձ�ʱ��
    MOV     DPTR, #PWMB_CCR6H
    MOVX    @DPTR, A
    MOV     A, PWM6_Duty_L
    MOV     DPTR, #PWMB_CCR6L
    MOVX    @DPTR, A

    MOV     A, PWM7_Duty_H      ;����ռ�ձ�ʱ��
    MOV     DPTR, #PWMB_CCR7H
    MOVX    @DPTR, A
    MOV     A, PWM7_Duty_L
    MOV     DPTR, #PWMB_CCR7L
    MOVX    @DPTR, A

    MOV     A, PWM8_Duty_H      ;����ռ�ձ�ʱ��
    MOV     DPTR, #PWMB_CCR8H
    MOVX    @DPTR, A
    MOV     A, PWM8_Duty_L
    MOV     DPTR, #PWMB_CCR8L
    MOVX    @DPTR, A
    RET

;**************** �жϺ��� ***************************************************
F_Timer0_Interrupt: ;Timer0 1ms�жϺ���
    PUSH    PSW     ;PSW��ջ
    PUSH    ACC     ;ACC��ջ

    JB      PWM5_Flag, T0_PWM5_SUB
    INC     PWM5_Duty_L       ;PWM5_Duty + 1
    MOV     A, PWM5_Duty_L
    JNZ     $+4
    INC     PWM5_Duty_H
    
    CLR     C
    MOV     A, PWM5_Duty_L
    SUBB    A, #LOW 1023
    MOV     A, PWM5_Duty_H
    SUBB    A, #HIGH 1023
    JC      T0_PWM6_Start
    SETB    PWM5_Flag
    SJMP    T0_PWM6_Start
T0_PWM5_SUB:
    MOV     A, PWM5_Duty_L
    DEC     PWM5_Duty_L       ;PWM5_Duty - 1
    JNZ     $+4
    DEC     PWM5_Duty_H
    
    MOV     A, PWM5_Duty_L
    JNZ     T0_PWM6_Start
    MOV     A, PWM5_Duty_H
    JNZ     T0_PWM6_Start
    CLR     PWM5_Flag

T0_PWM6_Start:
    JB      PWM6_Flag, T0_PWM6_SUB
    INC     PWM6_Duty_L       ;PWM6_Duty + 1
    MOV     A, PWM6_Duty_L
    JNZ     $+4
    INC     PWM6_Duty_H
    
    CLR     C
    MOV     A, PWM6_Duty_L
    SUBB    A, #LOW 1023
    MOV     A, PWM6_Duty_H
    SUBB    A, #HIGH 1023
    JC      T0_PWM7_Start
    SETB    PWM6_Flag
    SJMP    T0_PWM7_Start
T0_PWM6_SUB:
    MOV     A, PWM6_Duty_L
    DEC     PWM6_Duty_L       ;PWM6_Duty - 1
    JNZ     $+4
    DEC     PWM6_Duty_H
    
    MOV     A, PWM6_Duty_L
    JNZ     T0_PWM7_Start
    MOV     A, PWM6_Duty_H
    JNZ     T0_PWM7_Start
    CLR     PWM6_Flag
    
T0_PWM7_Start:
    JB      PWM7_Flag, T0_PWM7_SUB
    INC     PWM7_Duty_L       ;PWM7_Duty + 1
    MOV     A, PWM7_Duty_L
    JNZ     $+4
    INC     PWM7_Duty_H
    
    CLR     C
    MOV     A, PWM7_Duty_L
    SUBB    A, #LOW 1023
    MOV     A, PWM7_Duty_H
    SUBB    A, #HIGH 1023
    JC      T0_PWM8_Start
    SETB    PWM7_Flag
    SJMP    T0_PWM8_Start
T0_PWM7_SUB:
    MOV     A, PWM7_Duty_L
    DEC     PWM7_Duty_L       ;PWM7_Duty - 1
    JNZ     $+4
    DEC     PWM7_Duty_H
    
    MOV     A, PWM7_Duty_L
    JNZ     T0_PWM8_Start
    MOV     A, PWM7_Duty_H
    JNZ     T0_PWM8_Start
    CLR     PWM7_Flag
    
T0_PWM8_Start:
    JB      PWM8_Flag, T0_PWM8_SUB
    INC     PWM8_Duty_L       ;PWM8_Duty + 1
    MOV     A, PWM8_Duty_L
    JNZ     $+4
    INC     PWM8_Duty_H
    
    CLR     C
    MOV     A, PWM8_Duty_L
    SUBB    A, #LOW 1023
    MOV     A, PWM8_Duty_H
    SUBB    A, #HIGH 1023
    JC      F_QuitTimer0
    SETB    PWM8_Flag
    SJMP    F_QuitTimer0
T0_PWM8_SUB:
    MOV     A, PWM8_Duty_L
    DEC     PWM8_Duty_L       ;PWM8_Duty - 1
    JNZ     $+4
    DEC     PWM8_Duty_H
    
    MOV     A, PWM8_Duty_L
    JNZ     F_QuitTimer0
    MOV     A, PWM8_Duty_H
    JNZ     F_QuitTimer0
    CLR     PWM8_Flag
        
F_QuitTimer0:
    LCALL   F_UpdatePwm

    POP     ACC     ;ACC��ջ
    POP     PSW     ;PSW��ջ
    RETI

;======================================================================

    END

