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
void setTIM2Frequency(uint32_t capcnt);
uint16_t getTIM2Frequency(void);
void setTIM3Frequency(uint32_t capcnt);
uint16_t getTIM3Frequency(void);

//����״̬ 1�����η���  2����������
uint8_t sendState = 0;
//������������
uint8_t TxData[DataLen] = {0};
// //ѭ������
// uint8_t loopCount = 5;
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

//��ȡDAC���ݳ���
uint8_t getDacLen(void)
{
	return DacLen;
}

//����״̬
void setSendState(uint8_t state)
{
	sendState = state;
}


uint8_t getSendState(void)
{
	return sendState;
}

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

//TIM2����Ƶ��
void setTIM2Frequency(uint32_t capcnt)
{
 	TIM2Frequency = 72000000 / capcnt; //����Ƶ��
}

uint16_t getTIM2Frequency(void)
{
	return TIM2Frequency;
}

//TIM3����Ƶ��
void setTIM3Frequency(uint32_t capcnt)
{
 	TIM3Frequency = 72000000 / capcnt; //����Ƶ��
}

uint16_t getTIM3Frequency(void)
{
	return TIM3Frequency;
}
