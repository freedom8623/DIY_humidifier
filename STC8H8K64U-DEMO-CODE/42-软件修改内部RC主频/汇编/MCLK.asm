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

;�����̻���STC8H8K64UΪ����оƬ��ʵ����9���б�д���ԣ�STC8G��STC8Hϵ��оƬ��ͨ�òο�.

;����ʹ��P6��������ƣ���ʾϵͳʱ��Դ�л�Ч����

;�����ÿ��һ���л�һ��ʱ��Դ���ֱ���Ĭ��IRC��Ƶ����Ƶ48��Ƶ���ڲ�32K IRC��

;����ʱ, ѡ��ʱ�� 24MHZ (�û��������޸�Ƶ��).

;******************************************/

$include (../../comm/STC8H.INC)

;/****************************** �û������ ***********************************/

Fosc_KHZ    EQU 24000   ;24000KHZ

STACK_POIRTER   EQU     0D0H    ;��ջ��ʼ��ַ

;*******************************************************************
;*******************************************************************

;*******************************************************************

Mode        DATA    21H

;*******************************************************************
            ORG     0000H
            LJMP    MAIN

            ORG     0100H
MAIN:
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
    MOV     PSW, #0     ;ѡ���0��R0~R7

    CLR     P4.0        ;LED Power On
    MOV     Mode, #0
    MOV     R0, #0XFE
L_MainLoop:
    MOV     P6,R0
    
    MOV     A,R0
	RL      A
    MOV     R0,A

    JB      ACC.0,L_MainDelay
    LCALL   F_MCLK_Sel

L_MainDelay:
    MOV     A, #10
    LCALL   F_delay_ms      ;��ʱ10ms
    SJMP    L_MainLoop

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

    MOV     R2,A

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

;========================================================================
; ����: F_MCLK_Sel
; ����: ��Ƶ���ó���
; ����: none.
; ����: none.
; �汾: VER1.0
; ����: 2013-4-1
;========================================================================
F_MCLK_Sel:
    MOV     A,Mode
	JNZ     F_MCLK_1
F_MCLK_0:
    MOV     A,#080H                    ;�����ڲ� IRC
    MOV     DPTR,#HIRCCR
    MOVX    @DPTR,A
    MOVX    A,@DPTR
    JNB     ACC.0,$-1                  ;�ȴ�ʱ���ȶ�

    MOV     A,#00H                     ;ʱ�Ӳ���Ƶ
    MOV     DPTR,#CLKDIV
    MOVX    @DPTR,A
    MOV     A,#00H                     ;ѡ���ڲ�IRC(Ĭ��)
    MOV     DPTR,#CLKSEL
    MOVX    @DPTR,A
	INC     Mode
    RET

F_MCLK_1:
    MOV     A,Mode
    XRL     A,#1
	JNZ     F_MCLK_2
    MOV     A,#080H                    ;�����ڲ� IRC
    MOV     DPTR,#HIRCCR
    MOVX    @DPTR,A
    MOVX    A,@DPTR
    JNB     ACC.0,$-1                  ;�ȴ�ʱ���ȶ�

    MOV     A,#48                      ;ʱ��48��Ƶ
    MOV     DPTR,#CLKDIV
    MOVX    @DPTR,A
    MOV     A,#00H                     ;ѡ���ڲ�IRC(Ĭ��)
    MOV     DPTR,#CLKSEL
    MOVX    @DPTR,A
	INC     Mode
    RET

F_MCLK_2:
    MOV     A,Mode
    XRL     A,#2
	JNZ     F_MCLK_CLR
    MOV     A,#080H                    ;�����ڲ� 32K IRC
    MOV     DPTR,#IRC32KCR
    MOVX    @DPTR,A
    MOVX    A,@DPTR
    JNB     ACC.0,$-1                  ;�ȴ�ʱ���ȶ�

    MOV     A,#00H                     ;ʱ�Ӳ���Ƶ
    MOV     DPTR,#CLKDIV
    MOVX    @DPTR,A
    MOV     A,#03H                     ;ѡ���ڲ� 32K
    MOV     DPTR,#CLKSEL
    MOVX    @DPTR,A
F_MCLK_CLR:
    MOV     Mode, #0
    RET

;F_MCLK_3:
    ;MOV     A,Mode
    ;XRL     A,#3
	;JNZ     F_MCLK_CLR
    ;MOV     A,#0C0H                    ;�����ⲿ����
    ;MOV     DPTR,#XOSCCR
    ;MOVX    @DPTR,A
    ;MOVX    A,@DPTR
    ;JNB     ACC.0,$-1                  ;�ȴ�ʱ���ȶ�

    ;MOV     A,#00H                     ;ʱ�Ӳ���Ƶ
    ;MOV     DPTR,#CLKDIV
    ;MOVX    @DPTR,A
    ;MOV     A,#01H                     ;ѡ���ⲿ����
    ;MOV     DPTR,#CLKSEL
    ;MOVX    @DPTR,A
    ;MOV     Mode, #0
    ;RET

    END

