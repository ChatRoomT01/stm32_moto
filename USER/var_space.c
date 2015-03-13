#include "var_space.h"

#define DataLen 10	//���ڷ��ͱ��ĳ���
#define DacLen 5			//DAC���ձ��ĳ���
#define TestLen 9

uint8_t getDataLen(void);
uint8_t getDacLen(void);

void setSendState(uint8_t state);
uint8_t getSendState(void);

void setTxData(uint8_t data, uint8_t n);
uint8_t getTxData(uint8_t n);

void setTIM2Period(uint32_t capcnt);
uint16_t getTIM2Period(void);

void setTIM3Period(uint32_t capcnt);
uint16_t getTIM3Period(void);

void addTIM2Counter(void);
void clearTIM2Counter(void);
void setTIM2Frequency(void);
uint16_t getTIM2Frequency(void);

void addTIM3Counter(void);
void clearTIM3Counter(void);
void setTIM3Frequency(void);
uint16_t getTIM3Frequency(void);

//����״̬ 1�����η���  2����������
uint8_t sendState = 0;
//������������
uint8_t TxData[DataLen] = {0};
//TIM2����
uint16_t TIM2Period = 0;
//TIM3����
uint16_t TIM3Period = 0;
//TIM2Ƶ�ʼ�����
uint16_t TIM2Counter = 0;
//TIM3Ƶ�ʼ�����
uint16_t TIM3Counter = 0;
//TIM2Ƶ��
uint16_t TIM2Frequency = 0;
//TIM3Ƶ��
uint16_t TIM3Frequency = 0;

//��������
uint32_t TestData = 0;

//��ȡ�������ݳ���
uint8_t getDataLen(void)
{
	return DataLen;
}

/***********************************************************/
//��ȡDAC���ݳ���
uint8_t getDacLen(void)
{
	return DacLen;
}

/***********************************************************/
//����״̬
void setSendState(uint8_t state)
{
	sendState = state;
}


uint8_t getSendState(void)
{
	return sendState;
}

/***********************************************************/
//��������
void setTxData(uint8_t data, uint8_t n)
{
	if(n<DataLen){
		TxData[n] = data;
	}
}

uint8_t getTxData(uint8_t n)
{
	if(n<DataLen){
		return TxData[n];
	}
	else return 0x55;
}

/***********************************************************/
//TIM2��������
void setTIM2Period(uint32_t capcnt)
{
 	TIM2Period = (72000000-1) / capcnt; //����Ƶ��
}
//��Ƶ �����ڷ�
uint16_t getTIM2Period(void)
{
	return TIM2Period;
}

/***********************************************************/
//TIM3��������
void setTIM3Period(uint32_t capcnt)
{
 	TIM3Period = (72000000-1) / capcnt; //����Ƶ��
}
//��Ƶ �����ڷ�
uint16_t getTIM3Period(void)
{
	return TIM3Period;
}

/***********************************************************/
//TIM2����Ƶ��
void addTIM2Counter(void)
{
 	TIM2Counter ++; //����Ƶ��
}

void clearTIM2Counter(void)
{
	TIM2Counter = 0; //���������
}

void setTIM2Frequency(void)
{
 	TIM2Frequency = TIM2Counter * 20;
	TIM2Counter = 0; //���������
}
//��Ƶ ��Ƶ�ʷ�
uint16_t getTIM2Frequency(void)
{
	return TIM2Frequency;
}

/***********************************************************/
//TIM3����Ƶ��
void addTIM3Counter(void)
{
 	TIM3Counter ++; //����Ƶ��
}

void clearTIM3Counter(void)
{
	TIM3Counter = 0; //���������
}

void setTIM3Frequency(void)
{
 	TIM3Frequency = TIM3Counter * 20;
	TIM3Counter = 0; //���������
}
//��Ƶ ��Ƶ�ʷ�
uint16_t getTIM3Frequency(void)
{
	return TIM3Frequency;
}

