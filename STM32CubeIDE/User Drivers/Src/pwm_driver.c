
#include "stm32f0xx_hal.h"
#include "pwm_driver.h"


static void pwm_pin_configure();

void pwm_init(void)
{
	pwm_pin_configure();

	TIM3->PSC = 23; // Timer clock = 48 mhz / 24 = 2Mhz
	TIM3->ARR = 99;  // Period ==> (2 Mhz / 100) = 20 Khz
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;

	// CH-1 PWM MODE 
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

	// CH-2 PWM MODE 
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;

	// CH-3 PWM MODE
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE;

	// CH-4 PWM MODE
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE;

	// Enable OC1REF and OC2REF OUTPUTS
	TIM3->CCER |= TIM_CCER_CC1E;
	TIM3->CCER |= TIM_CCER_CC2E;
	TIM3->CCER |= TIM_CCER_CC3E;
	TIM3->CCER |= TIM_CCER_CC4E;
}

void pwm_enable(void)
{
	// Enable Timer
	TIM3->CR1 |= TIM_CR1_CEN;
	TIM3->EGR |= TIM_EGR_UG;
}

void pwm_disable(void)
{
	// Disable Timer
	TIM3->CR1 &= ~(TIM_CR1_CEN);	
}

void pwm_set_duty_cycle(uint32_t duty, Channels_e channel)
{
	switch (channel) {
	case CHANNEL1:
		TIM3->CCR1 = duty;
		break;

	case CHANNEL2:
		TIM3->CCR2 = duty;
		break;

	case CHANNEL3:
		TIM3->CCR3 = duty;
		break;

	case CHANNEL4:
		TIM3->CCR4 = duty;
		break;
	}
}

static void pwm_pin_configure()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// PB4 - TIMER3 - CH1 - D5
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// PB5 - TIMER3 - CH2 - D4
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// PB0 - TIMER3 - CH3 - A3
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// PB1 - TIMER3 - CH4
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

