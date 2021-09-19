#include "uart.h"
#include "rcc.h"
#include "gpio.h"



#define GPIOEN                    (1U<<3)
#define UART_TX                   (1U<<8)
#define UART_RX                   (1U<<9)
#define GPIO_ALTERNATE_MODE        0x2

#define USART3_EN                 (1U<<18)
#define UART_DATAWIDTH_8B         0x00000000U    // 8bit word length : start bit , 8bit data bits
#define UART_PARITY_NONE          0x00000000U    // parity control disable
#define UART_STOPBIT_1            0x00000000U    // 1 stop bit



static void uart_write(USART_TypeDef *USARTx, uint8_t value);
static void set_uart_tranfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection);

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static void uart_enable(USART_TypeDef *USARTx);
static void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);





int __io_putchar(int ch)
{
	uart_write(USART3, ch);

	return ch;
}



uint8_t uart_read(USART_TypeDef *USARTx)
{
	while(!(USARTx -> ISR & USART_ISR_RXNE)){};
	return (READ_BIT(USARTx->RDR, USART_RDR_RDR) & 0xFFU);
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



void uart3_rxtx_init(void)
{

  // pd8 -> tx
  // pd9 -> rx



  /******Configure Tx Pin********/

  // 1. enable clock
  set_ahb1_periph_clock(GPIOEN);
  // 2. pd8 mode to alternate function
  set_pin_mod(GPIOD, UART_TX, GPIO_ALTERNATE_MODE);
  // 3. set alternate function to UART
  GPIOD->AFR[1] |= (1U<<0);
  GPIOD->AFR[1] |= (1U<<1);
  GPIOD->AFR[1] |= (1U<<2);
  GPIOD->AFR[1] &=~ (1U<<3);


  /******Configure Rx Pin********/
  set_pin_mod(GPIOD, UART_RX, GPIO_ALTERNATE_MODE);

  GPIOD->AFR[1] |= (1U<<4);
  GPIOD->AFR[1] |= (1U<<5);
  GPIOD->AFR[1] |= (1U<<6);
  GPIOD->AFR[1] &=~ (1U<<7);


  // enable to USART3 clock
  set_apb1_periph_clock(USART3_EN);


  // configure USART parameters
  config_uart_parameters(USART3, UART_DATAWIDTH_8B, UART_PARITY_NONE, UART_STOPBIT_1);
  set_uart_tranfer_direction(USART3, (USART_CR1_TE | USART_CR1_RE));

  // set baurate
  uart_set_baudrate(USART3, 16000000, 115200);

  // enable usart

  /* SET_BIT(USART3->CR1, USART_CR1_UE);
   * USART3->CR1 |= USART_CR1_UE;
   */

  uart_enable(USART3);

}



static void set_uart_tranfer_direction(USART_TypeDef *USARTx, uint32_t TransferDirection)
{
	MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);
}



static void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1, USART_CR1_UE);
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx -> BRR = compute_uart_div(PeriphClk, BaudRate);
}


static void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
	MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);
	MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}


static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return (PeriphClk + (BaudRate/2U)) / BaudRate;
}
