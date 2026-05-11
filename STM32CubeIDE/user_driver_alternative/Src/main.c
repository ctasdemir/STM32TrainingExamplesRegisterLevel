/**
 * @file    main.c
 * @brief   ADC Single Conversion with Interrupt - Register-based
 *
 * Hardware (Nucleo-F070RB):
 *   PA0  -> ADC1 Channel 0 (analog input)
 *   PA5  -> LED2 (toggle every 100 ms)
 *   PA2  -> USART2 TX  (prints ADC value via printf)
 *   PA3  -> USART2 RX
 *   PC13 -> User button (unused here, driver initialised for completeness)
 *
 * Clock:
 *   HSI (8 MHz)  /PREDIV(1)  *PLL(x6)  =  48 MHz SYSCLK
 *
 * ADC flow:
 *   adc_driver_init() -> configures ADC1 + starts first single conversion
 *   ADC1_IRQHandler   -> reads DR, sets adc_value / adc_ready, restarts ADC
 *   main loop         -> prints value when adc_ready == 1
 */

#include "stm32f0xx_hal.h"
#include "uart_driver.h"
#include "led_driver.h"
#include "button_driver.h"
#include "adc_driver.h"
#include <stdio.h>

/* -------------------------------------------------------------------------
 * Globals
 * ----------------------------------------------------------------------- */
volatile uint32_t sys_tick  = 0;   /* 1 ms tick incremented by SysTick ISR */
volatile int      adc_value = 0;
volatile int      adc_ready = 0;

/* -------------------------------------------------------------------------
 * Private function prototypes
 * ----------------------------------------------------------------------- */
static void SystemClock_Config(void);
static void SysTick_Init(void);
void        delay_ms(uint32_t ms);

/* =========================================================================
 * main
 * ======================================================================= */
int main(void)
{
    SystemClock_Config();   /* 48 MHz via PLL                               */
    SysTick_Init();         /* 1 ms system tick                             */

    UART_Init();
    user_led_init();
    button_init();
    adc_driver_init();      /* Configures ADC1 and starts first conversion  */

    while (1)
    {
        user_led_toggle();

        if (adc_ready == 1)
        {
            adc_ready = 0;
            printf("ADC val == %d\r\n", adc_value);
        }

        delay_ms(100);
    }
}

/* =========================================================================
 * ADC1 Interrupt Handler
 *   - EOC fires after each single conversion
 *   - Reading DR clears the EOC flag
 *   - ADSTART is re-set to start the next single conversion
 * ======================================================================= */
void ADC1_IRQHandler(void)
{
    if ((ADC1->ISR & ADC_ISR_EOC) && (ADC1->IER & ADC_IER_EOCIE))
    {
        adc_value = (int)ADC1->DR;      /* Reading DR clears EOC flag       */
        adc_ready = 1;
        ADC1->CR |= ADC_CR_ADSTART;    /* Restart next single conversion   */
    }
}

/* =========================================================================
 * SystemClock_Config
 *   Source : HSI (8 MHz internal oscillator)
 *   PREDIV : /1  (RCC_CFGR2 = 0)
 *   PLLMUL : x6  (bits[21:18] = 0100b = 4)
 *   Result : 8 MHz / 1 * 6 = 48 MHz
 *   AHB/APB: both /1 (default)
 *   Flash  : 1 wait state (required above 24 MHz on F070)
 * ======================================================================= */
static void SystemClock_Config(void)
{
    /* 1. Enable HSI oscillator */
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    /* 2. Flash: 1 wait state for 48 MHz (LATENCY bit 0 = 1) */
    FLASH->ACR |= FLASH_ACR_LATENCY;

    /* 3. PREDIV = divide-by-1 (bits[3:0] = 0000) */
    RCC->CFGR2 = 0x00000000U;

    /* 4. PLL configuration
     *    PLLSRC bits[16:15] = 01  -> HSI / PREDIV
     *    PLLMUL bits[21:18] = 0100 -> x6
     *    HPRE   bits[7:4]   = 0000 -> AHB  /1 (default)
     *    PPRE   bits[10:8]  = 000  -> APB1 /1 (default)                   */
    RCC->CFGR &= ~(RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC |
                   RCC_CFGR_HPRE   | RCC_CFGR_PPRE);
    RCC->CFGR |= (uint32_t)((4UL << 18) |  /* PLLMUL = x6 (encoding = 4)  */
                             (1UL << 15));  /* PLLSRC = HSI/PREDIV         */

    /* 5. Enable PLL */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    /* 6. Switch SYSCLK to PLL (SW bits[1:0] = 10) */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    /* 7. Update CMSIS global so HAL_GetTick / delay_ms are correct */
    SystemCoreClock = 48000000UL;
}

/* =========================================================================
 * SysTick_Init
 *   Configures SysTick for a 1 ms interrupt at 48 MHz.
 *   Reload = 48 000 000 / 1000 - 1 = 47 999
 * ======================================================================= */
static void SysTick_Init(void)
{
    SysTick->LOAD = 48000UL - 1UL;
    SysTick->VAL  = 0UL;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |   /* CPU clock (not /8)   */
                    SysTick_CTRL_TICKINT_Msk    |   /* Enable SysTick IRQ   */
                    SysTick_CTRL_ENABLE_Msk;        /* Start counter        */
}

/* =========================================================================
 * delay_ms
 *   Busy-waits using the sys_tick counter updated in SysTick_Handler.
 * ======================================================================= */
void delay_ms(uint32_t ms)
{
    uint32_t start = sys_tick;
    while ((sys_tick - start) < ms);
}
