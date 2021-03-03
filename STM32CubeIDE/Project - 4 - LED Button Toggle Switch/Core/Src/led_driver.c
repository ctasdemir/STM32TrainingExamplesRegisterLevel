#include "stm32f070xb.h"
#include "stm32f0xx_hal.h"


void user_led_init()
{
	//LED2 ==>  GPIOA - 5. pin
	
	// Enable Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();	
	
	// Select Mode
	// BIT 10: 1
	// BIT 11: 0
	GPIOA->MODER   &= ~(1 << 11); // Bit 11 : 0
  GPIOA->MODER   |=  (1 << 10); // Bit 10 : 1
	
	
	// Select Output Type	
	// Bit 5 : 0
  GPIOA->OTYPER  &= ~(1<<5); // 0 - Push - pull output
	
	// Select Speed	
	// Bit 10: 1
	// Bit 11: 0
  GPIOA->OSPEEDR &= ~(1 << 11); // Bit 11: 0
  GPIOA->OSPEEDR |=  (1 << 10); // Bit 10: 1
	
	// Pull-up pull-down
  // Bit 10 : 0 
  // Bit 11 :	0
  GPIOA->PUPDR   &= ~(1 << 11); // No pull-up, no pull-down	
	GPIOA->PUPDR   &= ~(1 << 10); // No pull-up, no pull-down	
}


void user_led_toggle()
{
	GPIOA->ODR ^= (1<<5);
}


void user_led_set()
{
	// Bit 5 : 1
	GPIOA->BSRR = (1<<5);
}

void user_led_reset()
{
	// Bit 5 : 1
	GPIOA->BRR = (1<<5);
}


