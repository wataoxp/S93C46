/*
 * s93c46.h
 *
 *  Created on: Jan 5, 2025
 *      Author: wataoxp
 */

#ifndef INC_S93C46_H_
#define INC_S93C46_H_

#include "main.h"
#include "delay.h"

typedef enum{
	false,
	true,
}MicroWire_bool;

typedef struct{
	GPIO_TypeDef *PortCS;
	GPIO_TypeDef *PortSK;
	GPIO_TypeDef *PortDI;
	GPIO_TypeDef *PortDO;
	uint16_t CS;
	uint16_t SK;
	uint16_t DI;
	uint16_t DO;
}S93C46_Typedef;

#define ADDR_MASK 0x3F
#define SK_TIME 1
#define SK_READ_TIME 2

#define READ_CODE 0x80
#define WRITE_CODE 0x40
#define ERASE_CODE 0xC0
#define WR_ALL_CODE 0x10
#define ER_ALL_CODE 0x20
#define ENABLE_CODE 0x30
#define DISABLE_CODE 0x00

//typedef enum{
//	CS = 1 << 4,
//	SK = 1 << 5,
//	DI = 1 << 6,
//	DO = 1 << 7,
//}GPIO_Pin;

void SetHandle(S93C46_Typedef* init);
void WriteRom(uint8_t address,uint8_t code,uint16_t data);
void ReadRom(uint8_t address,uint16_t *val);
void EnableWrite(void);
void DisableWrite(void);

#endif /* INC_S93C46_H_ */

/****
 * 備考
 * ADDR_MASK
 * S93C46Aは1kbit(128byte)でその構成は64word*16bit。
 * つまり2バイトのページが64つあるということ。
 * そしてページは0~63で64つなので、最大の指定値が0x3F
 *
 * SK_READ_TIME
 * 同期クロック。データシートP5よりVCCが3.3Vのとき、これは最大で500KHｚなので1us秒あれば良い。
 * しかしこの電源電圧のとき、ROMの出力(DO)の最大遅延が1usなので念のため1us余分にSKのHigh時間を取っている。
 *
 * Verify
 * ROMの書き込み処理中にCSをHighにすることで今BUSYなのかチェックする。
 * DOがLowを出力しているならBUSYなのでLowの間待つ
 *
 * ThreeWire
 * ROMのDOを抵抗(10k~100k)経由でDIピンに接続する。
 * ReadRomで読み込み先アドレスを指定(Write)した後、GPIO_initを呼びDIをinputに切り替える。
 * ピン数が3本になる代わり、Verify()が使えなくなる。
 *
 * たぶんVerify()の度にGPIOを切り替えれば問題はないけど頻繁に設定を変えることにどうしても抵抗がある。100kΩくらい
 ****/
