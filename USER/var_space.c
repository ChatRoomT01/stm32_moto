#include "var_space.h"

#define DataLen 10	//串口发送报文长度
#define DacLen 5			//DAC接收报文长度
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

//发送状态 1：单次发送  2：连续发送
uint8_t sendState = 0;
//发送数据数组
uint8_t TxData[DataLen] = {0};
// //循环次数
// uint8_t loopCount = 5;
//TIM2频率
uint16_t TIM2Frequency = 0;
//TIM3频率
uint16_t TIM3Frequency = 0;

//测试数据
uint32_t TestData = 0;

//获取发送数据长度
uint8_t getDataLen(void)
{
	return DataLen;
}

//获取DAC数据长度
uint8_t getDacLen(void)
{
	return DacLen;
}

//发送状态
void setSendState(uint8_t state)
{
	sendState = state;
}


uint8_t getSendState(void)
{
	return sendState;
}

//发送数组
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

//TIM2捕获频率
void setTIM2Frequency(uint32_t capcnt)
{
 	TIM2Frequency = 72000000 / capcnt; //计数频率
}

uint16_t getTIM2Frequency(void)
{
	return TIM2Frequency;
}

//TIM3捕获频率
void setTIM3Frequency(uint32_t capcnt)
{
 	TIM3Frequency = 72000000 / capcnt; //计数频率
}

uint16_t getTIM3Frequency(void)
{
	return TIM3Frequency;
}
