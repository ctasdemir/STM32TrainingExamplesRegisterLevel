/**
 * @file    adc_sequence_driver.c
 * @brief   ADC Sequence Driver - Register-based (replaces HAL version)
 *
 * Peripheral : ADC1, Channels 0/1/4/8/17
 * Pins       : PA0 (CH0), PA1 (CH1), PA4 (CH4), PB0 (CH8), VREF (CH17)
 * Resolution : 12-bit, right-aligned
 * Mode       : Continuous scan, forward direction (CH0 -> CH17)
 * Clock      : HSI14 (14 MHz dedicated ADC clock)
 * Sampling   : 71.5 ADC clock cycles (SMP = 110b)
 * Trigger    : EOC interrupt collects each result; EOS resets the index
 */

#include "stm32f0xx.h"
#include "adc_squence_driver.h"

volatile int32_t adc_result[5] = {0};
static int32_t adc_index = 0;

void adc_driver_init(void)
{
    /* -----------------------------------------------------------------------
     * 1. GPIO clocks (AHB)
     * --------------------------------------------------------------------- */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

    /* PA0, PA1, PA4 = Analog (MODER = 11b each) */
    GPIOA->MODER |= (3UL << (0U * 2U)) |
                    (3UL << (1U * 2U)) |
                    (3UL << (4U * 2U));

    /* PB0 = Analog */
    GPIOB->MODER |= (3UL << (0U * 2U));

    /* -----------------------------------------------------------------------
     * 2. ADC1 clock (APB2) + HSI14 dedicated ADC oscillator
     * --------------------------------------------------------------------- */
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
    RCC->CR2     |= RCC_CR2_HSI14ON;
    while (!(RCC->CR2 & RCC_CR2_HSI14RDY));

    /* -----------------------------------------------------------------------
     * 3. Calibration (ADC must be disabled first)
     * --------------------------------------------------------------------- */
    if (ADC1->CR & ADC_CR_ADEN)
    {
        ADC1->CR |= ADC_CR_ADDIS;
        while (ADC1->CR & ADC_CR_ADEN);
    }
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);

    /* -----------------------------------------------------------------------
     * 4. Configure ADC
     *    CFGR1: 12-bit (RES=00), right-aligned (ALIGN=0),
     *           CONT=1 (continuous), OVRMOD=1, SW trigger,
     *           SCANDIR=0 (forward: lowest channel number first)
     * --------------------------------------------------------------------- */
    ADC1->CFGR1 = ADC_CFGR1_CONT | ADC_CFGR1_OVRMOD;

    /* Sampling time: 71.5 ADC clock cycles (SMP = 110b) */
    ADC1->SMPR = ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1;

    /* Enable internal voltage reference for CH17 */
    ADC->CCR |= ADC_CCR_VREFEN;

    /* Select channels 0, 1, 4, 8, 17 */
    ADC1->CHSELR = ADC_CHSELR_CHSEL0  |
                   ADC_CHSELR_CHSEL1  |
                   ADC_CHSELR_CHSEL4  |
                   ADC_CHSELR_CHSEL8  |
                   ADC_CHSELR_CHSEL17;

    /* -----------------------------------------------------------------------
     * 5. Enable ADC and wait for ready flag
     * --------------------------------------------------------------------- */
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

    /* -----------------------------------------------------------------------
     * 6. Interrupt: End-of-Conversion (EOC)
     * --------------------------------------------------------------------- */
    ADC1->IER |= ADC_IER_EOCIE;
    NVIC_SetPriority(ADC1_IRQn, 0);
    NVIC_EnableIRQ(ADC1_IRQn);

    /* -----------------------------------------------------------------------
     * 7. Start continuous conversions
     * --------------------------------------------------------------------- */
    ADC1->CR |= ADC_CR_ADSTART;
}

void adc_start_conversion(void)
{
    if (!(ADC1->CR & ADC_CR_ADSTART))
    {
        ADC1->CR |= ADC_CR_ADSTART;
    }
}

void adc_print_results(void)
{
    printf("CH0=%d CH1=%d CH4=%d CH8=%d VREF=%d\r\n",
           (int)adc_result[0], (int)adc_result[1],
           (int)adc_result[2], (int)adc_result[3],
           (int)adc_result[4]);
}

void ADC1_IRQHandler(void)
{
    if ((ADC1->ISR & ADC_ISR_EOC) && (ADC1->IER & ADC_IER_EOCIE))
    {
        if (adc_index < 5)
        {
            adc_result[adc_index++] = ADC1->DR;  /* reading DR clears EOC */
        }
        else
        {
            (void)ADC1->DR;  /* discard if index out of range */
        }

        if (ADC1->ISR & ADC_ISR_EOS)
        {
            adc_index = 0;
            ADC1->ISR = ADC_ISR_EOS;  /* clear EOS by writing 1 */
        }
    }
}
