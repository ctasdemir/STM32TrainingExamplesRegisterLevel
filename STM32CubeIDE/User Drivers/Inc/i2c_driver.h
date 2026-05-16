#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "stm32f0xx_hal.h"
#include <stdint.h>

/*
 * I2C1 Master Driver — register-level, polling, STM32F070RBTx
 *
 * Pins : PB6 = SCL (AF1), PB7 = SDA (AF1), open-drain
 * Clock: assumes 48 MHz PCLK1 (HSI x PLL6)  → SM 100 kHz
 *
 * Return convention: 0 = OK, -1 = error (NACK or timeout)
 */

void   I2C1_Init    (void);

/* Raw write/read — dev_addr is the 7-bit address (not shifted) */
int8_t I2C1_Write   (uint8_t dev_addr, uint8_t *data, uint8_t len);
int8_t I2C1_Read    (uint8_t dev_addr, uint8_t *data, uint8_t len);

/* Register-addressed helpers — write reg then data in one transaction;
   read uses a repeated START between the register write and data read.  */
int8_t I2C1_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);
int8_t I2C1_ReadReg (uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

#endif /* I2C_DRIVER_H */
