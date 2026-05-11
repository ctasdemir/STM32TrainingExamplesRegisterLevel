/**
 * @file    adc_int_driver.c
 * @brief   ADC Driver - Register-based (replaces HAL version)
 *
 * Peripheral : ADC1, Channel 0 (PA0)
 * Resolution : 12-bit, right-aligned
 * Trigger    : Software (single conversion, restarted from ADC1_IRQHandler)
 * Clock      : HSI14 (14 MHz dedicated ADC clock)
 * Sampling   : 71.5 ADC clock cycles  (SMP = 110b)
 *
 * ADC1_IRQHandler is defined in main.c because it accesses adc_value / adc_ready
 * which live there.
 */

#include "stm32f0xx_hal.h"
#include "adc_driver.h"

void adc_driver_init(void)
{
    /* -----------------------------------------------------------------------
     * 1. GPIO: PA0 -> analog input
     * --------------------------------------------------------------------- */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          /* GPIOA clock (AHB)        */
    GPIOA->MODER |= (3UL << 0);                 /* PA0 = Analog (MODER=11)  */

    /* -----------------------------------------------------------------------
     * 2. Clocks: ADC1 (APB2) + HSI14 dedicated ADC oscillator
     * --------------------------------------------------------------------- */
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;          /* ADC1 clock               */
    RCC->CR2     |= RCC_CR2_HSI14ON;            /* Enable HSI14             */
    while (!(RCC->CR2 & RCC_CR2_HSI14RDY));     /* Wait until ready         */

    /* -----------------------------------------------------------------------
     * 3. Calibration (ADC must be disabled first)
     * --------------------------------------------------------------------- */
    if (ADC1->CR & ADC_CR_ADEN)
    {
        ADC1->CR |= ADC_CR_ADDIS;
        while (ADC1->CR & ADC_CR_ADEN);         /* Wait for ADEN = 0        */
    }
    ADC1->CR |= ADC_CR_ADCAL;                   /* Start calibration        */
    while (ADC1->CR & ADC_CR_ADCAL);            /* Wait for completion      */

    /* -----------------------------------------------------------------------
     * 4. Configure ADC
     *    CFGR1: 12-bit (RES=00), right-aligned (ALIGN=0),
     *           CONT=0  (single conversion, SW-restarted each IRQ),
     *           OVRMOD=1 (overwrite DR on overrun),
     *           EXTEN=00 + EXTSEL=000 (software trigger)
     * --------------------------------------------------------------------- */
    ADC1->CFGR1 = ADC_CFGR1_OVRMOD;            /* Single-conv, SW trigger  */

    /* Sampling time: 71.5 ADC clock cycles (SMP = 110b = 6) */
    ADC1->SMPR = ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1;

    /* Select channel 0 (PA0) */
    ADC1->CHSELR = ADC_CHSELR_CHSEL0;

    /* -----------------------------------------------------------------------
     * 5. Enable ADC and wait for ready flag
     * --------------------------------------------------------------------- */
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));       /* Wait for ADRDY           */

    /* -----------------------------------------------------------------------
     * 6. Interrupt: End-of-Conversion (EOC)
     * --------------------------------------------------------------------- */
    ADC1->IER |= ADC_IER_EOCIE;
    NVIC_SetPriority(ADC1_IRQn, 1);
    NVIC_EnableIRQ(ADC1_IRQn);

    /* -----------------------------------------------------------------------
     * 7. Start first conversion
     * --------------------------------------------------------------------- */
    ADC1->CR |= ADC_CR_ADSTART;
}
