/*
 * gpio.c
 *
 *  Created on: Jan 7, 2025
 *      Author: wataoxp
 */

#include "gpio.h"

void GPIO_init(GPIO_TypeDef *GPIOx,uint32_t pin,uint32_t mode)
{
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_GPIO_ResetOutputPin(GPIOx, pin);
	if(mode == LL_GPIO_MODE_OUTPUT)
	{
		LL_GPIO_SetPinSpeed(GPIOx, pin, LL_GPIO_SPEED_FREQ_LOW);
		LL_GPIO_SetOutputPin(GPIOx, pin);
	}
	LL_GPIO_SetPinPull(GPIOx, pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinMode(GPIOx, pin, mode);
}

