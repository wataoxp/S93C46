# S93C46

## 概要
セイコー製のEEPROM、S93C46ADP用のプログラムです。

このROMはSPIと似て非なる形式(MicroWire)での制御になりますので、GPIOの操作で通信しています。

(ROMから見て)データ入力(DI)と出力(DO)を1本にすることもできます。s93c46.cの"ThreeWire"の宣言で切り替えます。

## 説明
GPIOの設定はgpio.cのGPIO_Initで行っています。

GPIOの設定を行った後、8ページ分データを書き込み、書き込んだデータを読み取るだけのプログラムです。

## Requirement
* STM32CubeIDE
* STM32C011F4P6(Cortex-M0+)
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


