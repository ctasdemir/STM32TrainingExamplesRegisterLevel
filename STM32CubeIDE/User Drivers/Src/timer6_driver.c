
#include "stm32f0xx_hal.h"
#include "timer6_driver.h"



void timer6_init(void)
{	
	// Enable TIM6 Clock
	__HAL_RCC_TIM6_CLK_ENABLE();
	
	// Timer clock = 48 mhz / 48000 = 1000 Hz (1 ms period)
	TIM6->PSC = 47999;
	
	// Reload in every 100 ms
	TIM6->ARR = 499;
	
	// Enable Timer Update Interrupt
	TIM6->DIER |= TIM_DIER_UIE;

	// Enable TIM6 Interrupt on NVIC
	NVIC_EnableIRQ(TIM6_IRQn);
	NVIC_SetPriority(TIM6_IRQn,2);
}

// Set period (ms)
void timer6_set_period(uint16_t period)
{
	TIM6->ARR = period-1;
}

uint16_t timer6_get_counter_value(void)
{
	uint16_t cnt = TIM6->CNT;
	
	return cnt;
}

void timer6_enable(void)
{
	TIM6->CR1 |= TIM_CR1_CEN;
}

void timer6_disable(void)
{
	TIM6->CR1 &= ~(TIM_CR1_CEN);	
}

// Timer6 Interrupt Request Handler
void TIM6_IRQHandler(void)
{
	TIM6->SR &=~(TIM_SR_UIF);
	
	GPIOA->ODR ^= GPIO_PIN_5;
}

