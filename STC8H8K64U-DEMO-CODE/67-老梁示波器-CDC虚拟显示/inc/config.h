
#ifndef		_CONFIG_H
#define		_CONFIG_H	1

/*********************************************************/

#define MAIN_Fosc		40000000L	//������ʱ��  ע�⴮�ڲ����ʲ��ܵ�115200

#include	"STC8H.h"

/**************************************************************************/
/**************************************************************************/

#define EN_EP1IN
#define EN_EP2IN
//#define EN_EP3IN
//#define EN_EP4IN
//#define EN_EP5IN
#define EN_EP1OUT
//#define EN_EP2OUT
//#define EN_EP3OUT
//#define EN_EP4OUT
//#define EN_EP5OUT

#define EP0_SIZE                64

#ifdef EN_EP1IN
#define EP1IN_SIZE              64
#endif
#ifdef EN_EP2IN
#define EP2IN_SIZE              64
#endif
#ifdef EN_EP3IN
#define EP3IN_SIZE              64
#endif
#ifdef EN_EP4IN
#define EP4IN_SIZE              64
#endif
#ifdef EN_EP5IN
#define EP5IN_SIZE              64
#endif
#ifdef EN_EP1OUT
#define EP1OUT_SIZE             64
#endif
#ifdef EN_EP2OUT
#define EP2OUT_SIZE             64
#endif
#ifdef EN_EP3OUT
#define EP3OUT_SIZE             64
#endif
#ifdef EN_EP4OUT
#define EP4OUT_SIZE             64
#endif
#ifdef EN_EP5OUT
#define EP5OUT_SIZE             64
#endif


#endif
