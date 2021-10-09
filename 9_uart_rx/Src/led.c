#include "led.h"



void user_leds_init(void)
{
	RCC->AHB1ENR |= GPIOB_CLK_EN;


	//set PB0 as OUTPUT
	GPIOB -> MODER |= (1U<<0);
	GPIOB -> MODER &= ~(1U<<1);

	//set PB7 as OUTPUT
	GPIOB -> MODER |= (1U<<14);
    GPIOB -> MODER &= ~(1U<<15);

    //set PB14 as OUTPUT
    GPIOB -> MODER |= (1U<<24);
    GPIOB -> MODER &= ~(1U<<285);

}


void all_leds_on(void)
{
	GPIOB -> ODR |= (RED_LED | BLUE_LED | GREEN_LED);
}


void all_leds_off(void)
{
	GPIOB -> ODR &=~ (RED_LED | BLUE_LED | GREEN_LED);
}


void all_leds_toggle(void)
{
	GPIOB -> ODR ^= (RED_LED | BLUE_LED | GREEN_LED);
}



void led_toggle(ledType led)
{
	GPIOB -> ODR ^= led;
}


void led_on(ledType led)
{
	GPIOB -> ODR |= led;
}
