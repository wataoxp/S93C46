# S93C46

## 概要
セイコー(現エイブリック？)製のEEPROM、S93C46ADP用のプログラムです。
このROMはSPIと似て非なる形式(MicroWire)での制御になりますので、GPIOの操作で通信しています。
(ROMから見て)データ入力(DI)と出力(DO)を1本にすることもできます。s93c46.cの"ThreeWire"の宣言で切り替えます。

他のMCUで使う場合はs93c46.h内にあるenum GPIO_Pinの数値を使うGPIOのピン番号に合わせてください。
またポートA以外を使う際にはs93c46.c内の編集も必要になります。
例:PA7→ポートAの7番ピン

## Requirement
* STM32CubeIDE
* STM32G031F6P6(Cortex-M0+)
* Clang

## Description
Edited File
* main.c
* s93c46.c
* s93c46.h
* delay.c
* delay.h
* gpio.c
* gpio.h

## Licence
[MIT](https://github.com/wataoxp/Radio/blob/main/LICENSE)


