// green PB0
// blue  PB7
// red   PB14

#define PERIPH_BASE         0x40000000UL
#define AHB1_OFFSET         0x00020000UL
#define AHB1PERIPH_BASE     PERIPH_BASE + AHB1_OFFSET            //0x40020000
#define GPIOB_OFFSET        0x400UL
#define GPIOB_BASE          AHB1PERIPH_BASE + GPIOB_OFFSET       //0x40020400

#define RCC_OFFSET          0x3800UL
#define RCC_BASE            AHB1PERIPH_BASE + RCC_OFFSET         //0x40023800
#define AHB1EN_R_OFFSET     0x30UL

#define RCC_AHB1EN_R        (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET)) //0x40023830

#define MODER_OFFSET        0x000UL
#define GPIOB_MODE_R        (*(volatile unsigned int *)(GPIOB_BASE + MODER_OFFSET))  //0x40020400

#define ODR_OFFSET          0x14UL
#define GPIOB_OD_R          (*(volatile unsigned int *)(GPIOB_BASE + ODR_OFFSET))

#define GPIOB_CLK_EN        (1U<<1)

#define USER_LED1_MODER     (1U<<0)
#define USER_LED2_MODER     (1U<<14)
#define USER_LED3_MODER     (1U<<28)

#define USER_LED1           (1U<<0)
#define USER_LED2           (1U<<7)
#define USER_LED3           (1U<<14)


int main(void)
{

  RCC_AHB1EN_R |= GPIOB_CLK_EN;
  GPIOB_MODE_R |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

  while(1)
  {
    // all led
    //GPIOB_OD_R |= USER_LED1 | USER_LED2 | USER_LED3;

    //toggle led
    GPIOB_OD_R ^= USER_LED1 | USER_LED2 | USER_LED3;

    for(int i=0; i<1000000; i++){}

  }
}
