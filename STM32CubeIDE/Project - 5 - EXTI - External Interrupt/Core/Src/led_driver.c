#include "led_driver.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal.h"




void user_led_init()
{
	//LED2 ==>  GPIOA - 5. pin
	
	// Enable Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();	
	
	// Select Mode
	GPIOA->MODER   &= ~((3UL << 10)); // zero bits
  GPIOA->MODER   |=  ((1UL << 10)); // set 01 (output)
	
	// Select Output Type	
  GPIOA->OTYPER  &= ~((1UL <<5)); // 0 - Push - pull output
	
	// Select Speed	
  GPIOA->OSPEEDR &= ~((3UL << 10)); // Zero bits
  GPIOA->OSPEEDR |=  ((1UL << 10)); // 01 Medium Speed
	
	// Pull-up pull-down	
  GPIOA->PUPDR   &= ~((3UL << 10)); // No pull-up, no pull-down
	
}


void user_led_toggle()
{
	GPIOA->ODR ^= GPIO_PIN_5;
}


void user_led_set()
{
	GPIOA->BSRR = GPIO_PIN_5;
}

void user_led_reset()
{
	GPIOA->BRR = GPIO_PIN_5;
}

