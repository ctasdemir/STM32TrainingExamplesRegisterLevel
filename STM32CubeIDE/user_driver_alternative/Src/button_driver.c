/**
 * @file    button_driver.c
 * @brief   Button Driver - Register-based (replaces HAL version)
 *
 * User button is connected to PC13 (active-low) on the Nucleo-F070RB.
 * IDR[13] = 1 -> not pressed (BUTTON_OFF)
 * IDR[13] = 0 -> pressed     (BUTTON_ON)
 */

#include "stm32f0xx_hal.h"
#include "button_driver.h"

void button_init(void)
{
    /* Enable GPIOC clock */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* PC13: Input mode (MODER bits[27:26] = 00) */
    GPIOC->MODER   &= ~(3UL << 26);

    /* Output type: push-pull (default, not relevant for input) */
    GPIOC->OTYPER  &= ~(1UL << 13);

    /* Speed: low (OSPEEDR bits[27:26] = 00) */
    GPIOC->OSPEEDR &= ~(3UL << 26);

    /* No pull-up, no pull-down (PUPDR bits[27:26] = 00) */
    GPIOC->PUPDR   &= ~(3UL << 26);
}

int32_t button_get_state(void)
{
    /* Active-low: IDR[13]=0 means button pressed */
    return (GPIOC->IDR & (1UL << 13)) ? BUTTON_OFF : BUTTON_ON;
}
