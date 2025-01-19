/*
 * gpio.c
 *
 *  Created on: Jan 12, 2025
 *      Author: wataoxp
 */

#include "gpio.h"

GPIO_Code GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *InitStruct)
{
	if((InitStruct->PinPos == Pin13) || (InitStruct->PinPos == Pin14))
	{
		if(GPIOx == GPIOA)
		{
			return init_Failed;
		}
	}
	if(InitStruct->Mode == LL_GPIO_MODE_OUTPUT || InitStruct->Mode == LL_GPIO_MODE_ALTERNATE)
	{
		WRITE_REG(GPIOx->BRR,1 << InitStruct->PinPos);
		GPIO_SetPinSpeed(GPIOx, InitStruct);
		GPIO_SetOutputPinType(GPIOx, InitStruct);
	}
	GPIO_SetPinPull(GPIOx, InitStruct);
	GPIO_SetPinMode(GPIOx, InitStruct);

	return init_Success;
}

