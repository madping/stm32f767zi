/*
 * gpio.h
 *
 *  Created on: 2021. 9. 12.
 *      Author: Administrator
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32f7xx.h"


void set_pin_mod(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);

#endif /* GPIO_H_ */
