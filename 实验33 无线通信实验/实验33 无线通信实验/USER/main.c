#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "24l01.h" 	 
 
 
//////////////////////////////////////////////////////////////////////////////////	 
//�SSTM32F103ZET6������								  
////////////////////////////////////////////////////////////////////////////////// 
 void paomadeng(unsigned char zhiding)
 {
	 switch(zhiding){
		 case 0:
			 LED0 = 0; LED1 = 1; LED2 = 1; 
		   break;
     case 1:
			 LED0 = 1; LED1 = 0; LED2 = 1; 
		   break;
     case 2:
			 LED0 = 1; LED1 = 1; LED2 = 0;  
       break;		 
		 default:
			 LED0 = 0; LED1 = 0; LED2 = 0; 
	 }   	 
 }
 int main(void)
 {	 
	u8 key;//,mode;
	u16 t=0;			 
	u8 tmp_buf[33];
  u8 temp[]="wrong number-";	
  u16 len;	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	//KEY_Init();					//��ʼ������
 
 	NRF24L01_Init();    		//��ʼ��NRF24L01 //��ʼ��24L01��IO�� SPI2 CS CE IQR

	while(NRF24L01_Check())
	{
		delay_ms(200);
		LED3=0; LED4=0;
 		delay_ms(200);
		LED3=1;LED4=1;
	}
	NRF24L01_TX_Mode();//����Ϊ����ģʽ
 	while(1)
	{	
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
				USART_SendData(USART2, USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			if(len != 32){
				for(t=0;t<13;t++){
		      USART_SendData(USART2, temp[t]);//�򴮿�1��������
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		    }
			}else{
				if(NRF24L01_TxPacket(USART_RX_BUF)==TX_OK){
					 LED3=0; 		   
			   }else{										   	
		       LED4=0;		
           key='a'-1;
				    for(t=0;t<32;t++)
				    {
					    key++;
					    if(key>('~'))key=' ';
					    tmp_buf[t]=key;	
				    }
				    tmp_buf[32]=0;//���������					 
			   };	
			}
			USART_RX_STA=0;
			
			
		}else{
		
				delay_ms(200);
				paomadeng(0);
				delay_ms(200);
				paomadeng(1);
				delay_ms(200);
				paomadeng(2);
			
		}
	} 
}


