/**
 * @file    uart_driver.c
 * @brief   UART Driver - Register-based (replaces HAL version)
 *
 * Peripheral : USART2
 * Pins       : PA2 = TX (AF1), PA3 = RX (AF1)
 * Config     : 8N1, 9600 baud @ 48 MHz  ->  BRR = 5000
 * Buffers    : 256-byte circular ring buffers for TX and RX
 *
 * printf() is retargeted to UART via __io_putchar (GCC) / fputc (Keil).
 */

#include "stm32f0xx_hal.h"
#include "uart_driver.h"
#include <stdio.h>

#define BUFFER_SIZE  256U

typedef struct
{
    uint8_t  buf[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
} RingBuf_t;

static volatile RingBuf_t txBuf;
static volatile RingBuf_t rxBuf;


void UART_Init(void)
{
    /* -----------------------------------------------------------------------
     * 1. Clocks
     * --------------------------------------------------------------------- */
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;        /* GPIOA (AHB)              */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;      /* USART2 (APB1)            */

    /* -----------------------------------------------------------------------
     * 2. GPIO: PA2 = USART2_TX, PA3 = USART2_RX  (Alternate Function 1)
     * --------------------------------------------------------------------- */
    /* Mode: Alternate function (MODER = 10) for PA2 and PA3 */
    GPIOA->MODER &= ~((3UL << 4) | (3UL << 6));
    GPIOA->MODER |=  ((2UL << 4) | (2UL << 6));

    /* Output type: push-pull (OTYPER bit = 0) */
    GPIOA->OTYPER &= ~((1UL << 2) | (1UL << 3));

    /* Speed: high */
    GPIOA->OSPEEDR |= (3UL << 4) | (3UL << 6);

    /* Pull: pull-up */
    GPIOA->PUPDR &= ~((3UL << 4) | (3UL << 6));
    GPIOA->PUPDR |=  (1UL << 4) | (1UL << 6);

    /* AF1 for PA2 (AFRL bits[11:8]) and PA3 (AFRL bits[15:12]) */
    GPIOA->AFR[0] &= ~((0xFUL << 8) | (0xFUL << 12));
    GPIOA->AFR[0] |=  (1UL << 8) | (1UL << 12);

    /* -----------------------------------------------------------------------
     * 3. USART2 configuration
     *    BRR = F_CLK / baud = 48 000 000 / 9600 = 5000
     * --------------------------------------------------------------------- */
    USART2->BRR = 5000U;
    USART2->CR2 = 0U;                           /* 1 stop bit (default)     */
    USART2->CR3 = 0U;                           /* No flow control, no DMA  */

    /* CR1: 8-bit, no parity, TX+RX+RXNE-interrupt enabled, then UART on   */
    USART2->CR1 = USART_CR1_TE    |             /* Transmit enable          */
                  USART_CR1_RE    |             /* Receive enable           */
                  USART_CR1_RXNEIE |            /* RX-not-empty interrupt   */
                  USART_CR1_UE;                 /* USART enable             */

    /* -----------------------------------------------------------------------
     * 4. NVIC
     * --------------------------------------------------------------------- */
    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}


/* ---------------------------------------------------------------------------
 * Public API
 * ------------------------------------------------------------------------- */

void UART_send_byte(uint8_t data)
{
    uint32_t next = (txBuf.head + 1U) % BUFFER_SIZE;
    while (next == txBuf.tail);                 /* Block if TX buffer full  */
    txBuf.buf[txBuf.head] = data;
    txBuf.head = next;
    USART2->CR1 |= USART_CR1_TXEIE;            /* Enable TXE interrupt     */
}

void UART_send_byte_array(uint8_t *buffer, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
        UART_send_byte(buffer[i]);
}

int32_t UART_read_byte(void)
{
    if (rxBuf.head == rxBuf.tail)
        return -1;
    uint8_t byte  = rxBuf.buf[rxBuf.tail];
    rxBuf.tail = (rxBuf.tail + 1U) % BUFFER_SIZE;
    return (int32_t)byte;
}

int UART_bytes_to_read(void)
{
    return (int)((rxBuf.head - rxBuf.tail + BUFFER_SIZE) % BUFFER_SIZE);
}


/* ---------------------------------------------------------------------------
 * USART2 interrupt handler
 * ------------------------------------------------------------------------- */

void USART2_IRQHandler(void)
{
    uint32_t isr = USART2->ISR;
    uint32_t cr1 = USART2->CR1;

    /* --- RX: received data register not empty --- */
    if ((isr & USART_ISR_RXNE) && (cr1 & USART_CR1_RXNEIE))
    {
        uint8_t  data = (uint8_t)USART2->RDR;   /* Reading RDR clears RXNE  */
        uint32_t next = (rxBuf.head + 1U) % BUFFER_SIZE;
        if (next != rxBuf.tail)                 /* Drop byte if buffer full */
        {
            rxBuf.buf[rxBuf.head] = data;
            rxBuf.head = next;
        }
        return;
    }

    /* --- TX: transmit data register empty --- */
    if ((isr & USART_ISR_TXE) && (cr1 & USART_CR1_TXEIE))
    {
        if (txBuf.head != txBuf.tail)
        {
            USART2->TDR = txBuf.buf[txBuf.tail];
            txBuf.tail  = (txBuf.tail + 1U) % BUFFER_SIZE;
        }
        else
        {
            USART2->CR1 &= ~USART_CR1_TXEIE;   /* No more data, disable    */
        }
    }
}


/* ---------------------------------------------------------------------------
 * printf retargeting
 * ------------------------------------------------------------------------- */

#ifdef __GNUC__
int __io_putchar(int ch)
{
    UART_send_byte((uint8_t)ch);
    return ch;
}
#else
int fputc(int ch, FILE *f)
{
    UART_send_byte((uint8_t)ch);
    return ch;
}
#endif
