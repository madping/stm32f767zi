#include <stdint.h>
#include <stdio.h>
#include "stm32f7xx.h"

#define GPIOEN                    (1U<<3)
#define UART_TX                   (1U<<8)
#define GPIO_ALTERNATE_MODE        0x2

#define USART3_EN                 (1U<<18)
#define UART_DATAWIDTH_8B         0x00000000U    // 8bit word length : start bit , 8bit data bits
#define UART_PARITY_NONE          0x00000000U    // parity control disable
#define UART_STOPBIT_1            0x00000000U    // 1 stop bit


void set_ahb1_periph_clock(uint32_t perihs);
void set_pin_mod(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);
void set_apb1_periph_clock(uint32_t perihs);
void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart_enable(USART_TypeDef *USARTx);
void uart_write(USART_TypeDef *USARTx, uint8_t value);
void set_uart_tranfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection);
void uart3_tx_init(void);


uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
int __io_putchar(int ch);





int main(void)
{
  int x;
  uart3_tx_init();

  while(1)
  {
	  //uart_write(USART3, 'H');
      printf("hello han.....\n\r");

	  for(int i=0; i<9000; i++)
	  {
		  x++;
	  }
  }


}



int __io_putchar(int ch)
{
	uart_write(USART3, ch);

	return ch;
}



void uart_write(USART_TypeDef *USARTx, uint8_t value)
{
	// make sure transmit data resister is empty

	//while(!((USARTx->ISR & USART_ISR_TXE) == USART_ISR_TXE)){};
	while(!(USARTx->ISR & USART_ISR_TXE)){};


	// write value into transmit data resister
	USARTx->TDR = value;
}


void uart3_tx_init(void)
{
  // 1. enable clock
  set_ahb1_periph_clock(GPIOEN);
  // 2. pd8 mode to alternate function
  set_pin_mod(GPIOD, UART_TX, GPIO_ALTERNATE_MODE);
  // 3. set alternate function to UART
  GPIOD->AFR[1] |= (1U<<0);
  GPIOD->AFR[1] |= (1U<<1);
  GPIOD->AFR[1] |= (1U<<2);
  GPIOD->AFR[1] &=~ (1U<<3);


  // enable to USART3 clock
  set_apb1_periph_clock(USART3_EN);


  // configure USART parameters
  config_uart_parameters(USART3, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBIT_1);
  set_uart_tranfer_direction(USART3, USART_CR1_TE);

  // set baurate
  uart_set_baudrate(USART3, 16000000, 115200);

  // enable usart

  /* SET_BIT(USART3->CR1, USART_CR1_UE);
   * USART3->CR1 |= USART_CR1_UE;
   */

  uart_enable(USART3);

}



void set_uart_tranfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection)
{
	MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);
}



void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1, USART_CR1_UE);
}


void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx -> BRR = compute_uart_div(PeriphClk, BaudRate);
}


void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
	MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);
	MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}


void set_ahb1_periph_clock(uint32_t perihs)
{
  SET_BIT(RCC->AHB1ENR, perihs);
  //RCC->AHB1ENR |= preihs;

}


void set_ahb2_periph_clock(uint32_t perihs)
{
  SET_BIT(RCC->AHB2ENR, perihs);

}


void set_apb1_periph_clock(uint32_t perihs)
{
  SET_BIT(RCC->APB1ENR, perihs);

}


void set_apb2_periph_clock(uint32_t perihs)
{
  SET_BIT(RCC->APB2ENR, perihs);

}



void set_pin_mod(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  //clear
 // GPIOD -> MODER &=~ (1U<<16);
 // GPIOD -> MODER &=~ (1U<<17);
  //set
 // GPIOD -> MODER |= (1U<<17);



  /* 0x3  = 0b 11
   * POSITION_VAL(1U<<8)
   *
   * (1U<<8) = 0000 0000 0000 0000 0000 0001 0000 0000
   * rbit = 0000 0000 1000 0000 0000 0000 0000 0000
   * clz = 8
   * POSITION_VAL(1U<<8) *2 = 16
   * 0x3 << 16 = (1U<<16) | (1U<<17)
   * CLEAR((1U<<16) | (1U<<17)) ==> &=~((1U<<16) | (1U<<17))
   *
   * Mode = 0b 10 = 0x2
   * 2 << 16 ==> bit16 = 0, bit17 = 1
   *
   * */

  MODIFY_REG(GPIOx->MODER, (0x3<<(POSITION_VAL(Pin)*2U)), (Mode<<POSITION_VAL(Pin)*2U));


}


uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return (PeriphClk + (BaudRate/2U)) / BaudRate;
}
