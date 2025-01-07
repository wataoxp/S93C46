/*
 * gpio.h
 *
 *  Created on: Jan 7, 2025
 *      Author: Hippe
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//#include "main.h"
#include "stm32g031xx.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_gpio.h"
#include <stdint.h>

void GPIO_init(GPIO_TypeDef *GPIOx,uint32_t pin,uint32_t mode);


#endif /* INC_GPIO_H_ */
