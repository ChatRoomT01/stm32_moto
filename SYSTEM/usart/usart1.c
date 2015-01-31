#include "usart1.h"
#include "var_space.h"

//extern uint32_t TestData;

void Dac1_Set_Vol(u16 vol);
void Dac2_Set_Vol(u16 vol);

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

	//Usart1 NVIC 配置

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//接收寄存器满开启中断
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//发送寄存器空开启中断
	USART_Cmd(USART1, ENABLE);                    //使能串口 

}

uint8_t loopCount = 0;
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};   //16进制字符表

//发送16位16进制
void send16B(uint16_t dat0, uint16_t dat1, uint8_t n)
{
	switch (n)
	{
		case 0: 
			USART_SendData(USART1, 'P');	//发送第一组数据
			break;
		case 1: 
			USART_SendData(USART1, HexTable[(dat0>>12)&0x0f]);
			break;
		case 2: 
			USART_SendData(USART1, HexTable[(dat0>>8)&0x0f]);
			break;
		case 3: 
			USART_SendData(USART1, HexTable[(dat0>>4)&0x0f]);
			break;
		case 4: 
			USART_SendData(USART1, HexTable[(dat0)&0x0f]);
			break;
		case 5: 
			USART_SendData(USART1, 'Q');	//发送第二组数据
			break;
		case 6: 
			USART_SendData(USART1, HexTable[(dat1>>12)&0x0f]);
			break;
		case 7: 
			USART_SendData(USART1, HexTable[(dat1>>8)&0x0f]);
			break;
		case 8: 
			USART_SendData(USART1, HexTable[(dat1>>4)&0x0f]);
			break;
		case 9: 
			USART_SendData(USART1, HexTable[(dat1)&0x0f]);
			break;
		default:
			break;
	}
}

//发送32位16进制
void send32B(uint32_t dat, uint8_t n)
{
	switch (n)
	{
		case 0: 
			USART_SendData(USART1, 'P');
		case 1: 
			USART_SendData(USART1, HexTable[(dat>>28)&0x0f]);
			break;
		case 2: 
			USART_SendData(USART1, HexTable[(dat>>24)&0x0f]);
			break;
		case 3: 
			USART_SendData(USART1, HexTable[(dat>>20)&0x0f]);
			break;
		case 4: 
			USART_SendData(USART1, HexTable[(dat>>16)&0x0f]);
			break;
		case 5: 
			USART_SendData(USART1, HexTable[(dat>>12)&0x0f]);
			break;
		case 6: 
			USART_SendData(USART1, HexTable[(dat>>8)&0x0f]);
			break;
		case 7: 
			USART_SendData(USART1, HexTable[(dat>>4)&0x0f]);
			break;
		case 8: 
			USART_SendData(USART1, HexTable[(dat)&0x0f]);
			break;
		default:
			break;
	}
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	uint8_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收寄存器满中断)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据 
		if(Res != 0x00)
		{
			switch (Res)
			{
				case 0xA1:
					setSendState(1);	//单次发送
					TIM_Cmd(TIM4, DISABLE);  //取消TIM4定时
					USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
					break;
				case 0xA2:
					setSendState(2);	//连续发送
					TIM_Cmd(TIM4, ENABLE);  //使能TIM4定时
					break;
				case 0xC1:
					Dac1_Set_Vol(1100);	//1100代表1.1v
					break;
				case 0xC2:
					Dac2_Set_Vol(2200);	//2200代表2.2v
					break;
				default:
					setSendState(0);
					break;
			}
		}
	}
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) //发送中断(发送寄存器空中断)
	{
		if(loopCount < getDataLen()) //正在发送
		{
			send16B(getTIM2Frequency(), getTIM3Frequency(), loopCount);
			loopCount++;
		}
		else //发送完成
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
			loopCount = 0;
		}
	}
	
} 


