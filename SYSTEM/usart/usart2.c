#include "usart2.h"
#include "var_space.h"
#include "math.h"

//extern uint32_t TestData;

void Dac1_Set_Vol(u16 vol);
void Dac2_Set_Vol(u16 vol);
uint16_t pretreatment0(void);
uint16_t pretreatment1(void);

//��ʼ��IO ����2 
//bound:������
void uart2_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	//devin:������USART2����ӳ�䣬�ϸ�����ߵ��۵����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);   /*��ӳ��ָ�����GPIO����*/
	
	//USART2_TXUSART2_TX   PD.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //PD.5
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ��PD.5
   
	//USART2_RX	  PD.6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PD.6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD.6

	//USART2 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_Even;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���ռĴ����������ж�
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);//���ͼĴ����տ����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}

uint8_t loopCount = 0;
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};   //16�����ַ���

//����16λ16����
void send16B(uint16_t dat0, uint16_t dat1, uint8_t n)
{
	switch (n)
	{
		case 0: 
			USART_SendData(USART2, 'P');	//���͵�һ������
			break;
		case 1: 
			USART_SendData(USART2, HexTable[(dat0>>12)&0x0f]);
			break;
		case 2: 
			USART_SendData(USART2, HexTable[(dat0>>8)&0x0f]);
			break;
		case 3: 
			USART_SendData(USART2, HexTable[(dat0>>4)&0x0f]);
			break;
		case 4: 
			USART_SendData(USART2, HexTable[(dat0)&0x0f]);
			break;
		case 5: 
			USART_SendData(USART2, 'Q');	//���͵ڶ�������
			break;
		case 6: 
			USART_SendData(USART2, HexTable[(dat1>>12)&0x0f]);
			break;
		case 7: 
			USART_SendData(USART2, HexTable[(dat1>>8)&0x0f]);
			break;
		case 8: 
			USART_SendData(USART2, HexTable[(dat1>>4)&0x0f]);
			break;
		case 9: 
			USART_SendData(USART2, HexTable[(dat1)&0x0f]);
			break;
		default:
			break;
	}
}

//����32λ16����
void send32B(uint32_t dat, uint8_t n)
{
	switch (n)
	{
		case 0: 
			USART_SendData(USART2, 'P');
		case 1: 
			USART_SendData(USART2, HexTable[(dat>>28)&0x0f]);
			break;
		case 2: 
			USART_SendData(USART2, HexTable[(dat>>24)&0x0f]);
			break;
		case 3: 
			USART_SendData(USART2, HexTable[(dat>>20)&0x0f]);
			break;
		case 4: 
			USART_SendData(USART2, HexTable[(dat>>16)&0x0f]);
			break;
		case 5: 
			USART_SendData(USART2, HexTable[(dat>>12)&0x0f]);
			break;
		case 6: 
			USART_SendData(USART2, HexTable[(dat>>8)&0x0f]);
			break;
		case 7: 
			USART_SendData(USART2, HexTable[(dat>>4)&0x0f]);
			break;
		case 8: 
			USART_SendData(USART2, HexTable[(dat)&0x0f]);
			break;
		default:
			break;
	}
}

//uint8_t DacChannel = 0;	//DACͨ��
//uint8_t DacStack[4] = {0};
//uint16_t DacValue =0;		//DAC����ֵ
//int8_t BitCounter = 0;		//�����±�λ����ֵ
uint16_t SendData0 = 0; //�ȽϹ���Ҫ���͵�����0
uint16_t SendData1 = 0; //�ȽϹ���Ҫ���͵�����1
//uint16_t PreData0 = 0; //ǰ������0
//uint16_t PreData1 = 0; //ǰ������1
uint16_t R[20]={165,330,495,660,825,990,1155,1320,1485,1650,1815,1980,2145,2310,2475,2640,2805,2970,3135,3300}; //DAC�����
#define StackLen 16
uint16_t DataStack0[StackLen] = {0}; //�˲�������
uint8_t StackCursor0 = 0; //�˲��������α�
uint16_t DataStack1[StackLen] = {0}; //�˲�������
uint8_t StackCursor1 = 0; //�˲��������α�
uint8_t counter; //�ۼӼ�����
uint32_t temp = 0; //�ۼ�����
uint16_t ave = 0; //�˲�ƽ��ֵ

void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	uint8_t Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���ռĴ������ж�)
	{
		Res =USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ������� 
		if(Res<=0x14 && Res >0)
		{
			Dac1_Set_Vol(R[Res - 0x01]); //�趨DACֵ;
		}
		else if(Res>0x20 && Res<=0x34)
		{
			Dac2_Set_Vol(R[Res - 0x21]); //�趨DACֵ;
		}
		else if (Res==0)
		{
			Dac1_Set_Vol(0); //�ر�DAC1
		}
		else if (Res==0x20)
		{
			Dac2_Set_Vol(0); //�ر�DAC2
		}
	}
	
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET) //�����ж�(���ͼĴ������ж�)
	{
		if(loopCount < getDataLen()) //���ڷ���
		{
			send16B(SendData0, SendData1, loopCount);
			loopCount++;
		}
		else //�������
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			loopCount = 0;
			SendData0 = getTIM2Period();	//���˲�
			SendData1 = getTIM3Frequency();
//			DataStack0[StackCursor0] = getTIM2Period();	//���˲�
//			SendData0 = pretreatment0(); //Ԥ����
//			DataStack1[StackCursor1] = getTIM3Frequency();
//			SendData1 = pretreatment1(); //Ԥ����
		}
	}
	
} 

uint16_t pretreatment0(void)
{
	temp = 0;
	ave = 0;
	for(counter=0; counter<StackLen; counter++)
	{
		temp = temp+DataStack0[counter];
	}
	StackCursor0++;
	StackCursor0 = (StackCursor0 % StackLen); //�α�ѭ���Լ�
	ave = temp /StackLen;
	return ave; //��λ����ȡƽ��
}

uint16_t pretreatment1(void)
{
	temp = 0;
	ave = 0;
	for(counter=0; counter<StackLen; counter++)
	{
		temp = temp+DataStack1[counter];
	}										   
	StackCursor1++;
	StackCursor1 = (StackCursor1 % StackLen); //�α�ѭ���Լ�
	ave = temp /StackLen;
	return ave; //��λ����ȡƽ��
}

