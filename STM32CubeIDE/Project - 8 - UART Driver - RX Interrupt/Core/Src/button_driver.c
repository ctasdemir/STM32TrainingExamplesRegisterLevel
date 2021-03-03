/**
  ******************************************************************************
  * @file    button_driver.c 
  * @author  
  * @version 
  * @date    
  * @brief   Button Driver Module
  *******************************************************************************/
#include "button_driver.h"
#include "stm32f070xb.h"
#include "stm32f0xx_hal.h"


void button_init()
{
	//BUTTON ==>  GPIOC - 13. pin
	
	// Enable Clock
	__HAL_RCC_GPIOC_CLK_ENABLE();	
	
	// Select Mode: Input
	// Bit 26: 0
	// Bit 27: 0
	GPIOC->MODER   &= ~(3UL << 26);  // set 00 ==> Input
	
	// Select Output Type	
	// Bit 13: 0
  GPIOC->OTYPER  &= ~(1UL <<13);   // 0 ==> Push pull
	
	// Select Speed	
	// Bit 26: 0
	// Bit 27: 0
  GPIOC->OSPEEDR &= ~(3UL << 26);  // 00 ==> Low speed
	
	// Pull-up pull-down	
	// Bit 26: 0
	// Bit 27: 0  
  GPIOC->PUPDR   &= ~(3UL << 26);  // 00 ==> // No pull-up, no pull-down
	
}

int32_t button_get_state(void)
{
	//BUTTON ==>  GPIOC - 13. pin
	if( ((GPIOC->IDR & (1<<13)) != 0 ))
	{
		return BUTTON_OFF;
	}
	else
	{
		return BUTTON_ON;
	}	
}
