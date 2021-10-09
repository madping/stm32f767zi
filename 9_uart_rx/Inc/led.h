/*
 * led.h
 *
 *  Created on: 2021. 9. 19.
 *      Author: Administrator
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define USER_LED1 (1U<<O)
#define USER_LED2 (1U<<7)
#define USER_LED3 (1U<<14)

#define GREEN_LED USER_LED1
#define BLUE_LED  USER_LED2
#define RED_LED   USER_LED3

#define GPIOB_CLK_EN (1U<<1)


typedef uint32_t ledType;

#endif /* LED_H_ */
