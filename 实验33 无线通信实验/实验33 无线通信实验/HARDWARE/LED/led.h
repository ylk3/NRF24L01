#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�SSTM32F103ZET6������								  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PFout(6)// PF6
#define LED1 PFout(7)// PF7	
#define LED2 PFout(8)// PF8
#define LED3 PFout(9)// PF9	
#define LED4 PFout(10)// PF10

void LED_Init(void);//��ʼ��

		 				    
#endif
