/*
 * s93c46a.c
 *
 *  Created on: Jan 5, 2025
 *      Author: wataoxp
 */
#include "s93c46.h"
#include "delay.h"
#include "gpio.h"

//#define ThreeWire

static void SendBit(uint8_t bit);
static void SendOpCode(uint8_t code);
static void WriteAddress(uint8_t add);
static void WriteData(uint16_t data);
static uint16_t ReadData(void);

static inline void DummyClock(void)
{
	WRITE_REG(GPIOA->BRR,DI);
	WRITE_REG(GPIOA->BSRR,SK);
	Delay(SK_TIME);
	WRITE_REG(GPIOA->BRR,SK);
	Delay(SK_TIME);
}
static inline void StartBit(void)		//CSをHiにした後、DIをHiにすることでスタートビットになる。
{
	SendBit(true);
}
static inline void EnableChip(void)
{
	WRITE_REG(GPIOA->BSRR,CS);
}
static inline void DisableChip(void)
{
	WRITE_REG(GPIOA->BRR,CS);
}
static void SendBit(uint8_t bit)
{
	WRITE_REG(GPIOA->BSRR,(bit << DI_SHIFT));		//データをセット
	Delay(SK_TIME);
	WRITE_REG(GPIOA->BSRR,SK);						//MX_GPIO_Initですべてのピンは初期状態がLow
	Delay(SK_TIME);
	WRITE_REG(GPIOA->BRR,DI);						//アイドル時はDI、SK共にLowにする
	WRITE_REG(GPIOA->BRR,SK);
}
static void SendOpCode(uint8_t code)
{
	for(int8_t i = 7; i >= 0; i--)
	{
		SendBit((code >> i) & 0x01);
	}
}
static uint16_t ReadData(void)
{
	uint16_t ret;

#ifdef ThreeWire
	for(uint8_t i = 0; i < 16; i++)
	{
		ret <<= 1;
		Delay(SK_TIME);
		WRITE_REG(GPIOA->BSRR,SK);
		Delay(SK_READ_TIME);

		ret |= (GPIOA->IDR & DI) >> DI_SHIFT;
		WRITE_REG(GPIOA->BRR,SK);
	}
#else
	for(uint8_t i = 0; i < 16; i++)
	{
		ret <<= 1;
		Delay(SK_TIME);
		WRITE_REG(GPIOA->BSRR,SK);
		Delay(SK_READ_TIME);

		ret |= (GPIOA->IDR & DO) >> DO_SHIFT;
		WRITE_REG(GPIOA->BRR,SK);
	}
#endif
	return ret;
}
static void WriteAddress(uint8_t add)			//いずれもMSBから送信
{
	for(int8_t i = 7; i >= 0; i--)
	{
		SendBit((add >> i) & 0x01);
	}
}
static void WriteData(uint16_t data)
{
	for(int8_t i = 15; i >= 0; i--)
	{
		SendBit((data >> i) & 0x0001);
	}
}
void WriteRom(uint8_t address,uint16_t data)
{
	EnableChip();
	StartBit();
	WriteAddress(address | WRITE_CODE);			//オペコード2ビット+アドレス
	WriteData(data);
	DisableChip();
}

void ReadRom(uint8_t address,uint16_t *val)
{
	EnableChip();
	StartBit();
	WriteAddress(address | READ_CODE);
	GPIO_init(GPIOA, DI, LL_GPIO_MODE_INPUT);
	*val = ReadData();
	DisableChip();
	GPIO_init(GPIOA, DI, LL_GPIO_MODE_OUTPUT);
}
void EnableWrite(void)
{
	Init1usTick();			//SysTickを1usカウントに切り替える
	EnableChip();
	//DummyClock();
	StartBit();
	SendOpCode(ENABLE_CODE);
	DisableChip();
}
void DisableWrite(void)
{
	EnableChip();
	StartBit();
	SendOpCode(DISABLE_CODE);
	DisableChip();
	DeInit1usTick();		//SysTickを1msカウントに戻す
}
void Verify(void)
{
	Delay(1);			//tCDS wait
#ifdef ThreeWire
	Delay(5000);
#else
	EnableChip();

	while(!(GPIOA->IDR & DO));		//Check Busy
#endif
}
