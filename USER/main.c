#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
// #include "usart1.h"
#include "usart2.h"
#include "timer.h"
#include "capture2.h"
#include "capture3re.h"
#include "var_space.h"
#include "dac.h"
#include "ili9325.h"

//void NVIC_Configuration(void);
//void delay_ms(u16 nms);
//void LED_Init(void);
//void uart2_init(u32 bound);
//void TIM2_Cap_Init(u16 arr,u16 psc);
//void TIM3RE_Cap_Init(u16 arr,u16 psc);
//void TIM4_Int_Init(u16 arr,u16 psc);
//void Dac1_Init(void);
//void Dac2_Init(void);

int main(void)
{
// 	uint8_t lcd_num[12];			//��������ַ���
	
	NVIC_Configuration();				// �����ж����ȼ�����
	delay_init();
	LED_Init();
// 	LCD_Init();
//   LCD_Clear(White );		 //д�뱳����ɫ
//   LCD_printString(5,5, "lcd test" ,Black);
	
 	TIM5_Int_Init(499,7200-1);	//��ʱ������ 7200��Ƶ 10kHz ��ʱ500��λ = 50ms
	TIM4_Int_Init(4999,72-1);	//��ʱ������ 72��Ƶ 1MHz ��ʱ5000��λ = 5ms
	TIM2_Cap_Init(0XFFFF,0);		//TIM2��72MhzƵ�ʼ���
	TIM3RE_Cap_Init(0XFFFF,0);		//TIM3��72MhzƵ�ʼ���
	uart2_init(115200);	 							//���ڳ�ʼ��Ϊ115200
// 	uart1_init(115200);	 							//���ڳ�ʼ��Ϊ115200
 	Dac1_Init();		 	//DACͨ��1��ʼ�� //PA.4 ���
 	Dac2_Init();		 	//DACͨ��2��ʼ�� //PA.5 ���
	
	//sprintf((char*)lcd_num,"LCD ID:%04d",9325);//��LCD ID��ӡ��lcd_id���顣
	
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(500);
		LED0=1;
		LED1=0;
		delay_ms(500);
		
// 		delay_ms(500);
// 		LCD_Clear(White );
// 		sprintf((char*)lcd_num,"TIM2F:%06d",getTIM2Period());
// 		LCD_printString(5,5, lcd_num ,Black);
// 		sprintf((char*)lcd_num,"TIM3P:%06d",getTIM3Frequency());
// 		LCD_printString(5,15, lcd_num ,Black);
	}
	
}
