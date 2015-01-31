#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart2.h"
#include "timer.h"
#include "capture2.h"
#include "capture3re.h"
#include "var_space.h"
#include "dac.h"

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
	NVIC_Configuration();				// �����ж����ȼ�����
	delay_init();
	LED_Init();
	TIM4_Int_Init(4999,72);	//��ʱ������ 72��Ƶ 1MHz ��ʱ5000��λ = 5ms
	TIM5_Int_Init(4999,7200);	//��ʱ������ 72��Ƶ 1MHz ��ʱ5000��λ = 5ms
	TIM2_Cap_Init(0XFFFF,0);		//TIM2��72MhzƵ�ʼ���
	TIM3RE_Cap_Init(0XFFFF,0);		//TIM3��72MhzƵ�ʼ���
	uart2_init(115200);	 							//���ڳ�ʼ��Ϊ115200
 	Dac1_Init();		 	//DACͨ��1��ʼ�� //PA.4 ���
 	Dac2_Init();		 	//DACͨ��2��ʼ�� //PA.5 ���
	
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(500);
		LED0=1;
		LED1=0;
		delay_ms(500);
	}
	
}
