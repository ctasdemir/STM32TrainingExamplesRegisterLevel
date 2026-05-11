/**
 * @file    stm32f0xx_it.c
 * @brief   Cortex-M0 exception and peripheral interrupt handlers.
 *
 * SysTick_Handler increments sys_tick (defined in main.c) which is used
 * by delay_ms().  HAL_IncTick() is NOT called because we are not using HAL.
 */

#include "stm32f0xx_hal.h"
#include "stm32f0xx_it.h"

extern volatile uint32_t sys_tick;  /* Defined in main.c */

/* -------------------------------------------------------------------------
 * Cortex-M0 Core Exception Handlers
 * ----------------------------------------------------------------------- */

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    while (1);
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

/* -------------------------------------------------------------------------
 * SysTick Handler  (1 ms tick)
 * ----------------------------------------------------------------------- */
void SysTick_Handler(void)
{
    sys_tick++;
}
