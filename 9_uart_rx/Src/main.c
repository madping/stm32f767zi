#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"




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












