/*
 * uart.h
 *
 *  Created on: 2021. 9. 12.
 *      Author: Administrator
 */

#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include <stdio.h>
#include "stm32f7xx.h"


void uart3_tx_init(void);
void uart3_rxtx_init(void);

uint8_t uart_read(USART_TypeDef *USARTx);

#endif /* UART_H_ */
