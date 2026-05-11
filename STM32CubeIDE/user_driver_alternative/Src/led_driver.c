/**
 * @file    led_driver.c
 * @brief   LED Driver - Register-based (replaces HAL version)
 *
 * LED2 is connected to PA5 on the Nucleo-F070RB.
 */

#include "stm32f0xx_hal.h"
#include "led_driver.h"

void user_led_init(void)
{
    /* Enable GPIOA clock */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    /* PA5: Output push-pull, medium speed, no pull-up/down
     * MODER bits[11:10] = 01 -> General-purpose output */
    GPIOA->MODER   &= ~(3UL << 10);
    GPIOA->MODER   |=  (1UL << 10);

    /* Output type: push-pull (OTYPER bit5 = 0) */
    GPIOA->OTYPER  &= ~(1UL << 5);

    /* Speed: medium (OSPEEDR bits[11:10] = 01) */
    GPIOA->OSPEEDR &= ~(3UL << 10);
    GPIOA->OSPEEDR |=  (1UL << 10);

    /* No pull-up, no pull-down (PUPDR bits[11:10] = 00) */
    GPIOA->PUPDR   &= ~(3UL << 10);
}

void user_led_toggle(void)
{
    GPIOA->ODR ^= (1UL << 5);
}

void user_led_set(void)
{
    GPIOA->BSRR = (1UL << 5);                  /* Set bit via BSRR         */
}

void user_led_reset(void)
{
    GPIOA->BRR  = (1UL << 5);                  /* Reset bit via BRR        */
}
