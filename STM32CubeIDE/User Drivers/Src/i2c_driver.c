#include "i2c_driver.h"

#define I2C_TIMEOUT 100000U

/* --------------------------------------------------------------------------
 * Helper: wait for a flag, return -1 on timeout or NACK
 * -------------------------------------------------------------------------- */
static int8_t wait_flag(uint32_t flag)
{
    uint32_t t = I2C_TIMEOUT;
    while (!(I2C1->ISR & flag))
    {
        if (I2C1->ISR & I2C_ISR_NACKF)
        {
            I2C1->ICR = I2C_ICR_NACKCF | I2C_ICR_STOPCF;
            return -1;
        }
        if (--t == 0) return -1;
    }
    return 0;
}

static int8_t wait_stop(void)
{
    uint32_t t = I2C_TIMEOUT;
    while (!(I2C1->ISR & I2C_ISR_STOPF))
        if (--t == 0) return -1;
    I2C1->ICR = I2C_ICR_STOPCF;
    return 0;
}

static int8_t wait_idle(void)
{
    uint32_t t = I2C_TIMEOUT;
    while (I2C1->ISR & I2C_ISR_BUSY)
        if (--t == 0) return -1;
    return 0;
}

/* --------------------------------------------------------------------------
 * I2C1_Init
 *
 * PB6 = SCL, PB7 = SDA, AF1, open-drain
 * TIMINGR: PRESC=11, SCLDEL=4, SDADEL=2, SCLH=15, SCLL=19
 *   tPRESC = 250 ns, tSCLL = 5000 ns, tSCLH = 4000 ns  → ~111 kHz
 * -------------------------------------------------------------------------- */
void I2C1_Init(void)
{
    /* Clocks */
    RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* PB6, PB7: Alternate function mode */
    GPIOB->MODER  &= ~((3UL << 12) | (3UL << 14));
    GPIOB->MODER  |=  (2UL << 12)  | (2UL << 14);

    /* Open-drain */
    GPIOB->OTYPER |= (1U << 6) | (1U << 7);

    /* High speed */
    GPIOB->OSPEEDR |= (3UL << 12) | (3UL << 14);

    /* No pull */
    GPIOB->PUPDR  &= ~((3UL << 12) | (3UL << 14));

    /* AF1 on PB6 and PB7 */
    GPIOB->AFR[0] &= ~((0xFUL << 24) | (0xFUL << 28));
    GPIOB->AFR[0] |=  (1UL << 24) | (1UL << 28);

    /* Disable I2C1 before writing TIMINGR */
    I2C1->CR1 &= ~I2C_CR1_PE;

    I2C1->TIMINGR = (0xBUL << 28) |  /* PRESC  = 11 */
                    (4UL   << 20) |  /* SCLDEL =  4 */
                    (2UL   << 16) |  /* SDADEL =  2 */
                    (0xFUL <<  8) |  /* SCLH   = 15 */
                     0x13UL;         /* SCLL   = 19 */

    I2C1->CR1 |= I2C_CR1_PE;
}

/* --------------------------------------------------------------------------
 * I2C1_Write — send len bytes to dev_addr
 * -------------------------------------------------------------------------- */
int8_t I2C1_Write(uint8_t dev_addr, uint8_t *data, uint8_t len)
{
    if (wait_idle() != 0) return -1;

    I2C1->CR2 = ((uint32_t)(dev_addr << 1) & I2C_CR2_SADD) |
                ((uint32_t)len << I2C_CR2_NBYTES_Pos)       |
                I2C_CR2_AUTOEND                              |
                I2C_CR2_START;

    for (uint8_t i = 0; i < len; i++)
    {
        if (wait_flag(I2C_ISR_TXIS) != 0) return -1;
        I2C1->TXDR = data[i];
    }

    return wait_stop();
}

/* --------------------------------------------------------------------------
 * I2C1_Read — receive len bytes from dev_addr
 * -------------------------------------------------------------------------- */
int8_t I2C1_Read(uint8_t dev_addr, uint8_t *data, uint8_t len)
{
    if (wait_idle() != 0) return -1;

    I2C1->CR2 = ((uint32_t)(dev_addr << 1) & I2C_CR2_SADD) |
                ((uint32_t)len << I2C_CR2_NBYTES_Pos)       |
                I2C_CR2_AUTOEND                              |
                I2C_CR2_RD_WRN                              |
                I2C_CR2_START;

    for (uint8_t i = 0; i < len; i++)
    {
        if (wait_flag(I2C_ISR_RXNE) != 0) return -1;
        data[i] = (uint8_t)I2C1->RXDR;
    }

    return wait_stop();
}

/* --------------------------------------------------------------------------
 * I2C1_WriteReg — write [reg_addr, data...] in a single transaction
 * -------------------------------------------------------------------------- */
int8_t I2C1_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    if (wait_idle() != 0) return -1;

    /* reg_addr byte + data bytes sent as one transfer */
    uint8_t total = 1u + len;

    I2C1->CR2 = ((uint32_t)(dev_addr << 1) & I2C_CR2_SADD) |
                ((uint32_t)total << I2C_CR2_NBYTES_Pos)     |
                I2C_CR2_AUTOEND                              |
                I2C_CR2_START;

    if (wait_flag(I2C_ISR_TXIS) != 0) return -1;
    I2C1->TXDR = reg_addr;

    for (uint8_t i = 0; i < len; i++)
    {
        if (wait_flag(I2C_ISR_TXIS) != 0) return -1;
        I2C1->TXDR = data[i];
    }

    return wait_stop();
}

/* --------------------------------------------------------------------------
 * I2C1_ReadReg — write reg_addr, repeated START, read len bytes
 * -------------------------------------------------------------------------- */
int8_t I2C1_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    if (wait_idle() != 0) return -1;

    /* Phase 1: write register address, SOFTEND (no STOP — wait TC) */
    I2C1->CR2 = ((uint32_t)(dev_addr << 1) & I2C_CR2_SADD) |
                (1UL << I2C_CR2_NBYTES_Pos)                 |
                I2C_CR2_START;  /* no AUTOEND → SOFTEND */

    if (wait_flag(I2C_ISR_TXIS) != 0) return -1;
    I2C1->TXDR = reg_addr;

    /* Wait for Transfer Complete (bus held, no STOP) */
    uint32_t t = I2C_TIMEOUT;
    while (!(I2C1->ISR & I2C_ISR_TC))
        if (--t == 0) return -1;

    /* Phase 2: repeated START + read */
    I2C1->CR2 = ((uint32_t)(dev_addr << 1) & I2C_CR2_SADD) |
                ((uint32_t)len << I2C_CR2_NBYTES_Pos)       |
                I2C_CR2_AUTOEND                              |
                I2C_CR2_RD_WRN                              |
                I2C_CR2_START;

    for (uint8_t i = 0; i < len; i++)
    {
        if (wait_flag(I2C_ISR_RXNE) != 0) return -1;
        data[i] = (uint8_t)I2C1->RXDR;
    }

    return wait_stop();
}
