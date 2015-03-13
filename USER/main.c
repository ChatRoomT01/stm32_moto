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
// 	uint8_t lcd_num[12];			//存放数字字符串
	
	NVIC_Configuration();				// 设置中断优先级分组
	delay_init();
	LED_Init();
// 	LCD_Init();
//   LCD_Clear(White );		 //写入背景颜色
//   LCD_printString(5,5, "lcd test" ,Black);
	
 	TIM5_Int_Init(499,7200-1);	//定时器设置 7200分频 10kHz 定时500单位 = 50ms
	TIM4_Int_Init(4999,72-1);	//定时器设置 72分频 1MHz 定时5000单位 = 5ms
	TIM2_Cap_Init(0XFFFF,0);		//TIM2以72Mhz频率计数
	TIM3RE_Cap_Init(0XFFFF,0);		//TIM3以72Mhz频率计数
	uart2_init(115200);	 							//串口初始化为115200
// 	uart1_init(115200);	 							//串口初始化为115200
 	Dac1_Init();		 	//DAC通道1初始化 //PA.4 输出
 	Dac2_Init();		 	//DAC通道2初始化 //PA.5 输出
	
	//sprintf((char*)lcd_num,"LCD ID:%04d",9325);//将LCD ID打印到lcd_id数组。
	
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
