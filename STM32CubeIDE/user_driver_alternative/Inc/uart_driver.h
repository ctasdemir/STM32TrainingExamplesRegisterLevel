/**
 * @file    uart_driver.h
 * @brief   UART Driver - Register-based
 *          USART2, PA2(TX)/PA3(RX), 8N1, 9600 baud, interrupt-driven ring buffer.
 */
#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

#include <stdint.h>

void    UART_Init(void);
void    UART_send_byte(uint8_t data);
void    UART_send_byte_array(uint8_t *buffer, uint32_t size);
int32_t UART_read_byte(void);
int     UART_bytes_to_read(void);

#endif
