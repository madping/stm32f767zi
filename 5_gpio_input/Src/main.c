#include "stm32f7xx.h"

#define GPIOB_CLK_EN        (1U<<1)
#define GPIOC_CLK_EN        (1U<<2)

#define USER_LED1_MODER     (1U<<0)
#define USER_LED2_MODER     (1U<<14)
#define USER_LED3_MODER     (1U<<28)

#define USER_LED1           (1U<<0)
#define USER_LED2           (1U<<7)
#define USER_LED3           (1U<<14)

#define PIN_13              (1U<<13)
#define BTN_PIN             PIN_13


int main(void)
{

  RCC->AHB1ENR |= GPIOB_CLK_EN;
  RCC->AHB1ENR |= GPIOC_CLK_EN;

  GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;


  GPIOC->MODER &=~ (1U<<26);  //0으로 초기화
  GPIOC->MODER &=~ (1U<<27);

  while(1)
  {


    if(GPIOC->IDR &= BTN_PIN){

    //ON
    GPIOB->BSRR |= (1U<<0)|(1U<<7)|(1U<<14);

    }else{

    //OFF
    GPIOB->BSRR |= (1U<<16)|(1U<<23)|(1U<<30);
    }

  }
}
