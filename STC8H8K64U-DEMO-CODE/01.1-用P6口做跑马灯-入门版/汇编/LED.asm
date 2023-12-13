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


;*************  ����˵��    **************

; �����̻���STC8H8K64UΪ����оƬ��ʵ����9���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

; ����ʹ��P6������ʾ����ƣ������������

; ���û�ʹ��Ӳ�� USB �� STC8H8K64U ϵ�н��� ISP ����ʱ���ܵ����ڲ� IRC ��Ƶ�ʣ�
; ���û�����ѡ���ڲ�Ԥ�õ� 16 ��Ƶ��
; ���ֱ��� 5.5296M�� 6M�� 11.0592M�� 12M�� 18.432M�� 20M�� 22.1184M�� 
; 24M��27M�� 30M�� 33.1776M�� 35M�� 36.864M�� 40M�� 44.2368M �� 48M����
; ����ʱ�û�ֻ�ܴ�Ƶ�������б��н���ѡ������֮һ���������ֶ���������Ƶ�ʡ�
; ��ʹ�ô���������������� 4M��48M ֮�������Ƶ�ʣ���

; ����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

;******************************************

$include (../../comm/STC8H.INC)

;*******************************************************************
;*******************************************************************

Fosc_KHZ    EQU 24000   ;24000KHZ

STACK_POIRTER   EQU     0D0H    ;��ջ��ʼ��ַ

;*******************************************************************
;*******************************************************************
        ORG     0000H               ;reset
        LJMP    F_Main

        ORG     0003H               ;0 INT0 interrupt
        RETI
        LJMP    F_INT0_Interrupt      

        ORG     000BH               ;1  Timer0 interrupt
        LJMP    F_Timer0_Interrupt

        ORG     0013H               ;2  INT1 interrupt
        LJMP    F_INT1_Interrupt      

        ORG     001BH               ;3  Timer1 interrupt
        LJMP    F_Timer1_Interrupt

        ORG     0023H               ;4  UART1 interrupt
        LJMP    F_UART1_Interrupt

        ORG     002BH               ;5  ADC and SPI interrupt
        LJMP    F_ADC_Interrupt

        ORG     0033H               ;6  Low Voltage Detect interrupt
        LJMP    F_LVD_Interrupt

        ORG     003BH               ;7  PCA interrupt
        LJMP    F_PCA_Interrupt

        ORG     0043H               ;8  UART2 interrupt
        LJMP    F_UART2_Interrupt

        ORG     004BH               ;9  SPI interrupt
        LJMP    F_SPI_Interrupt

        ORG     0053H               ;10  INT2 interrupt
        LJMP    F_INT2_Interrupt

        ORG     005BH               ;11  INT3 interrupt
        LJMP    F_INT3_Interrupt

        ORG     0063H               ;12  Timer2 interrupt
        LJMP    F_Timer2_Interrupt

        ORG     0083H               ;16  INT4 interrupt
        LJMP    F_INT4_Interrupt


;******************** ������ **************************/
        ORG     0100H       ;reset
F_Main:
    ORL     P_SW2, #080H    ;ʹ�ܷ���XFR

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
    MOV     PSW, #0     ;ѡ���0��R0~R7

    CLR     P4.0        ;LED Power On
L_MainLoop:
    CLR     P6.0
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.0

    CLR     P6.1
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.1

    CLR     P6.2
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.2

    CLR     P6.3
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.3

    CLR     P6.4
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.4

    CLR     P6.5
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.5

    CLR     P6.6
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.6

    CLR     P6.7
    LCALL   F_delay_ms      ;��ʱ250ms
    SETB    P6.7

    SJMP    L_MainLoop

;*******************************************************************
;*******************************************************************



;========================================================================
; ����: F_delay_ms
; ����: ��ʱ�ӳ���
; ����: ACC: ��ʱms��.
; ����: none.
; �汾: VER1.0
; ����: 2013-4-1
; ��ע: ����ACCC��PSW��, ���õ���ͨ�üĴ�������ջ
;========================================================================
F_delay_ms:
    PUSH    02H     ;��ջR2
    PUSH    03H     ;��ջR3
    PUSH    04H     ;��ջR4

    MOV     R2,#250

L_delay_ms_1:
    MOV     R3, #HIGH (Fosc_KHZ / 10)
    MOV     R4, #LOW (Fosc_KHZ / 10)
    
L_delay_ms_2:
    MOV     A, R4           ;1T     Total 10T/loop
    DEC     R4              ;1T
    JNZ     L_delay_ms_3    ;3T
    DEC     R3
L_delay_ms_3:
    DEC     A               ;1T
    ORL     A, R3           ;1T
    JNZ     L_delay_ms_2    ;3T
    
    DJNZ    R2, L_delay_ms_1

    POP     04H     ;��ջR2
    POP     03H     ;��ջR3
    POP     02H     ;��ջR4
    RET


;**************** �жϺ��� ***************************************************

F_Timer0_Interrupt: ;Timer0 1ms�жϺ���
    RETI
    
F_Timer1_Interrupt:
    RETI

F_Timer2_Interrupt:
    RETI

F_INT0_Interrupt:
    RETI
    
F_INT1_Interrupt:
    RETI

F_INT2_Interrupt:
    RETI

F_INT3_Interrupt:
    RETI

F_INT4_Interrupt:
    RETI

F_UART1_Interrupt:
    RETI

F_UART2_Interrupt:
    RETI

F_ADC_Interrupt:
    RETI

F_LVD_Interrupt:
    RETI

F_PCA_Interrupt:
    RETI

F_SPI_Interrupt:
    RETI


    END

