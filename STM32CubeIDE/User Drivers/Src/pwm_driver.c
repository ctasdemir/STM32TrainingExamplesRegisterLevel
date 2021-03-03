
#include "stm32f0xx_hal.h"
#include "pwm_driver.h"


void pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// PB4 - TIMER3 - CH1 - D5
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// PC7 - TIMER3 - CH2 - D9
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Alternate = GPIO_AF0_TIM3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	TIM3->PSC = 47; // Timer clock = 48 mhz / 48 = 1 MHz
	TIM3->ARR = 10;  // period 10 us ==> 100 KHz
	TIM3->CCR1 = 1;
	TIM3->CCR2 = 2;

	// CH-1 PWM MODE 
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

	// CH-2 PWM MODE 
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;

	// Enable OC1REF and OC2REF OUTPUTS
	TIM3->CCER |= TIM_CCER_CC1E;
	TIM3->CCER |= TIM_CCER_CC2E;

	// Enable Timer
	TIM3->CR1 |= TIM_CR1_CEN;
}


void pwm_enable(void)
{
	TIM3->CR1 |= TIM_CR1_CEN;
	TIM3->EGR |= TIM_EGR_UG;
}

void pwm_disable(void)
{
	TIM3->CR1 &= ~(TIM_CR1_CEN);	
}


void pwm_set_duty_cycle(uint32_t duty, uint32_t channel)
{
	switch(channel)
	{
		case 1:
			TIM3->CCR1 = duty;  
	
			break;
		
		case 2:
			TIM3->CCR2 = duty; 		
			break;
	}
}

