/*
 * gpio.h
 *
 *  Created on: Jan 12, 2025
 *      Author: wataoxp
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stdint.h>
#include "main.h"
//#include "stm32c011xx.h"
//#include "stm32c0xx_ll_bus.h"
//#include "stm32c0xx_ll_gpio.h"

typedef enum{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7,
	Pin8,
	Pin9,
	Pin10,
	Pin11,
	Pin12,
	Pin13,
	Pin14,
	Pin15,
}GPIO_Pin;

typedef enum{
	init_Success,
	init_Failed,
}GPIO_Code;

typedef struct{
	uint32_t PinPos;
	uint32_t Mode;
	uint32_t Speed;
	uint32_t OutputType;
	uint32_t Pull;
	uint32_t Alternate;
}GPIO_InitTypedef;

static inline void GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *init)
{
	MODIFY_REG(GPIOx->OSPEEDR,GPIO_OSPEEDR_OSPEED0 << (init->PinPos * 2),(init->Speed << (init->PinPos * 2)));
}
static inline void GPIO_SetPinPull(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *init)
{
	MODIFY_REG(GPIOx->PUPDR,GPIO_PUPDR_PUPD0 << (init->PinPos * 2),(init->Pull << (init->PinPos * 2)));
}
static inline void GPIO_SetPinMode(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *init)
{
	MODIFY_REG(GPIOx->MODER,GPIO_MODER_MODE0 << (init->PinPos * 2),(init->Mode << (init->PinPos * 2)));
}
static inline void GPIO_SetOutputPinType(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *init)
{
	MODIFY_REG(GPIOx->OTYPER,(1 << init->PinPos),(1 << init->PinPos) * init->OutputType);
}

GPIO_Code GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *InitStruct);


#endif /* INC_GPIO_H_ */
