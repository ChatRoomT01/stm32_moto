#include "capture2.h"

//��ʱ��2ͨ��1���벶������
//TIM2_CH2 PA1

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ��TIM2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIOCʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;  //PA1 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //PA1 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA1 ����
	
	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2 ,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
	TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��2
 
}

uint16_t  TIM2CH1_CAPTURE_CNT=0;	//��������������
uint16_t	TIM2CH1_CAPTURE_VAL;			//��ǰ���벶��ֵ
void setTIM2Frequency(uint32_t capcnt);
 
//��ʱ��2�жϷ������	 
void TIM2_IRQHandler(void)
{ 
	//�ж��Ƿ�Ϊ�����ж�
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		TIM2CH1_CAPTURE_CNT++;	//�����������
		TIM2CH1_CAPTURE_VAL=0XFFFF;
	}
	
	//�ж��Ƿ�Ϊ�����ж�
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET) //�ж��Ƿ�Ϊ�����ж�
	{
		TIM2CH1_CAPTURE_VAL= TIM_GetCapture2(TIM2);	//��ȡ��ǰ����ֵ
		setTIM2Frequency(TIM2CH1_CAPTURE_VAL + TIM2CH1_CAPTURE_CNT*65535);	//���²�������
		
		TIM2CH1_CAPTURE_CNT = 0; //�����¸������أ�ֹͣ����
		TIM2CH1_CAPTURE_VAL = 0;	//�������׼���´β�׽����
		TIM_SetCounter(TIM2,0);
	}
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
 
}
