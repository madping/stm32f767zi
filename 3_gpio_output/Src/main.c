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

  //RCC_AHB1EN_R |= GPIOB_CLK_EN;
  RCC->AHB1ENR |= GPIOB_CLK_EN;

  //GPIOB_MODE_R |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;
  GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

  while(1)
  {
    // all led
    //GPIOB_OD_R |= USER_LED1 | USER_LED2 | USER_LED3;
      GPIOB->ODR |= USER_LED1 | USER_LED2 | USER_LED3;


    //toggle led
    //GPIOB_OD_R ^= USER_LED1 | USER_LED2 | USER_LED3;

    //GPIOB->ODR ^= USER_LED1 | USER_LED2 | USER_LED3;

    //for(int i=0; i<1000000; i++){}

  }
}
