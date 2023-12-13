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

;�߼�PWM��ʱ��ʵ�ָ���PWM�������.

;����/ռ�ձȿɵ�, ͨ���Ƚ�/�����жϽ��������������.

;ͨ��P6����ʾ���,ÿ��10ms���һ��PWM,����10�������ֹͣ���.

;��ʱ��ÿ1ms����PWM����.

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
PWM1_Flag       BIT     20H.0
B_1ms           BIT     20H.1
;PWM2_Flag       BIT     20H.1
;PWM3_Flag       BIT     20H.2
;PWM4_Flag       BIT     20H.3

Period_H         DATA    30H
Period_L         DATA    31H

msecond          DATA    32H
Counter          DATA    33H

;*******************************************************************
;*******************************************************************
        ORG     0000H               ;reset
        LJMP    F_Main

        ORG     000BH               ;1  Timer0 interrupt
        LJMP    F_Timer0_Interrupt

        ORG     00D3H               ;26  PWMA interrupt
        LJMP    F_PWMA_Interrupt

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
    CLR     PWM1_Flag
    MOV     Period_L, #LOW 01000H
    MOV     Period_H, #HIGH 01000H

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
    LCALL   F_UpdatePwm
    CLR     P4.0

;=================== ��ѭ�� ==================================
L_Main_Loop:
    JNB     B_1ms,  L_Main_Loop     ;1msδ��
    CLR     B_1ms

    INC     msecond       ;msecond + 1
    CLR     C
    MOV     A, msecond    ;msecond - 10
    SUBB    A, #10
    JC      L_Main_Loop     ;if(msecond < 10), jmp
    MOV     msecond, #0   ;if(msecond >= 10)

    LCALL   F_TxPulse
    LJMP    L_Main_Loop

;========================================================================
; ����: F_TxPulse
; ����: �������庯��.
; ����: none.
; ����: none.
; �汾: V1.0, 2013-11-22
;========================================================================
F_TxPulse:
    MOV     A,#00                 ;д CCMRx ǰ���������� CCxE �ر�ͨ��
    MOV     DPTR,#PWMA_CCER1
    MOVX    @DPTR,A
    MOV     A,#068H               ;���� PWM1 ģʽ1 ���
    MOV     DPTR,#PWMA_CCMR1
    MOVX    @DPTR,A
    MOV     A,#01H                ;ʹ�� CC1E ͨ��, �ߵ�ƽ��Ч
    MOV     DPTR,#PWMA_CCER1
    MOVX    @DPTR,A
    MOV     A,#00                 ;���־λ
    MOV     DPTR,#PWMA_SR1
    MOVX    @DPTR,A
    MOV     A,#00                 ;�������
    MOV     DPTR,#PWMA_CNTRH
    MOVX    @DPTR,A
    MOV     A,#00                 ;�������
    MOV     DPTR,#PWMA_CNTRL
    MOVX    @DPTR,A
    MOV     A,#02H                ;ʹ�ܲ���/�Ƚ� 1 �ж�
    MOV     DPTR,#PWMA_IER
    MOVX    @DPTR,A
    RET

;========================================================================
; ����: F_PWM_Init
; ����: PWM��ʼ������.
; ����: none
; ����: none.
; �汾: V1.0, 2021-3-3
;========================================================================
F_PWM_Init:
    MOV     A,#01H              ;ʹ�� PWM1 ���
    MOV     DPTR,#PWMA_ENO
    MOVX    @DPTR,A
    MOV     A,#02H              ;�߼� PWM ͨ�������ѡ��λ, P6
    MOV     DPTR,#PWMA_PS
    MOVX    @DPTR,A
    MOV     A,#080H             ;ʹ�������
    MOV     DPTR,#PWMA_BKR
    MOVX    @DPTR,A

    MOV     DPTR,#PWMA_CR1
    MOVX    A,@DPTR
    ORL     A,#081H             ;ʹ��ARRԤװ�أ���ʼ��ʱ
    MOVX    @DPTR,A
    RET

;========================================================================
; ����: F_UpdatePwm
; ����: PWM����ռ�ձ�.
; ����: [Period_H Period_H]: pwm����ֵ.
; ����: none.
; �汾: V1.0, 2021-8-24
;========================================================================
F_UpdatePwm:
    MOV     A, Period_H         ;��������ʱ��
    MOV     DPTR, #PWMA_ARRH
    MOVX    @DPTR, A
    MOV     A, Period_L
    MOV     DPTR, #PWMA_ARRL
    MOVX    @DPTR, A

    MOV     A, Period_H         ;����ռ�ձ�ʱ��: Period/2
	CLR     C
	RRC     A
    MOV     DPTR, #PWMA_CCR1H
    MOVX    @DPTR, A
    MOV     A, Period_L
	RRC     A
    MOV     DPTR, #PWMA_CCR1L
    MOVX    @DPTR, A
    RET

;**************** �жϺ��� ***************************************************
F_Timer0_Interrupt: ;Timer0 1ms�жϺ���
    PUSH    PSW     ;PSW��ջ
    PUSH    ACC     ;ACC��ջ

    SETB    B_1ms           ; 1ms��־
    JNB     PWM1_Flag, T0_PWM1_SUB
    INC     Period_L       ;Period + 1
    MOV     A, Period_L
    JNZ     $+4
    INC     Period_H
    
    CLR     C
    MOV     A, Period_L
    SUBB    A, #LOW 01000H
    MOV     A, Period_H
    SUBB    A, #HIGH 01000H
    JC      F_QuitTimer0
    CLR     PWM1_Flag
    SJMP    F_QuitTimer0
T0_PWM1_SUB:
    MOV     A, Period_L
    DEC     Period_L       ;Period - 1
    JNZ     $+4
    DEC     Period_H

    CLR     C
    MOV     A, Period_L
    SUBB    A, #LOW 0100H
    MOV     A, Period_H
    SUBB    A, #HIGH 0100H
    JNC     F_QuitTimer0
    SETB    PWM1_Flag

F_QuitTimer0:
    LCALL   F_UpdatePwm

    POP     ACC     ;ACC��ջ
    POP     PSW     ;PSW��ջ
    RETI

;========================================================================
; ����: F_PWMA_Interrupt
; ����: PWMA�жϴ������.
; ����: None
; ����: none.
; �汾: V1.0, 2021-08-23
;========================================================================
F_PWMA_Interrupt:
    PUSH    PSW
    PUSH    ACC

    MOV     DPTR,#PWMA_SR1        ;���ӻ�״̬
    MOVX    A,@DPTR
    JNB     ACC.1,F_PWMA_QuitInt
    CLR     A
    MOVX    @DPTR,A

    INC     Counter               ;Counter + 1
    CLR     C
    MOV     A, Counter            ;Counter - 10
    SUBB    A, #10
    JC      F_PWMA_QuitInt        ;if(Counter < 10), jmp
    MOV     Counter, #0           ;if(Counter >= 10)

    MOV     A,#00                 ;д CCMRx ǰ���������� CCxE �ر�ͨ��
    MOV     DPTR,#PWMA_CCER1
    MOVX    @DPTR,A
    MOV     A,#040H               ;���� PWM1 ǿ��Ϊ��Ч��ƽ
    MOV     DPTR,#PWMA_CCMR1
    MOVX    @DPTR,A
    MOV     A,#01H                ;ʹ�� CC1E ͨ��, �ߵ�ƽ��Ч
    MOV     DPTR,#PWMA_CCER1
    MOVX    @DPTR,A
    MOV     A,#00H                ;�ر��ж�
    MOV     DPTR,#PWMA_IER
    MOVX    @DPTR,A

F_PWMA_QuitInt:
    POP     ACC
    POP     PSW
    RETI

;======================================================================

    END

