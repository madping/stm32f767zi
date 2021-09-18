#include "stm32f7xx.h"


#define GPIOB_CLK_EN        (1U<<1)

#define USER_LED1_MODER     (1U<<0)
#define USER_LED2_MODER     (1U<<14)
#define USER_LED3_MODER     (1U<<28)

#define USER_LED1           (1U<<0)
#define USER_LED2           (1U<<7)
#define USER_LED3           (1U<<14)



int main(void)
{

  RCC->AHB1ENR |= GPIOB_CLK_EN;
  GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

  while(1)
  {
    // all led
    //GPIOB->ODR |= USER_LED1 | USER_LED2 | USER_LED3;


    //toggle led
    //GPIOB->ODR ^= USER_LED1 | USER_LED2 | USER_LED3;

    GPIOB->BSRR |= (1U<<0)|(1U<<7)|(1U<<14);
    for(int i=0; i<1000000; i++){}
    GPIOB->BSRR |= (1U<<16)|(1U<<23)|(1U<<30);
    for(int i=0; i<1000000; i++){}

  }
}
