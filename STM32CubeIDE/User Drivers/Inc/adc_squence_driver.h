/**
 * @file    adc_squence_driver.h
 * @brief   ADC Sequence Driver - Register-based
 *          ADC1, Channels 0/1/4/8/17 (PA0/PA1/PA4/PB0/VREF),
 *          12-bit, continuous scan, EOC interrupt.
 */
#ifndef __ADC_SEQUENCE_DRIVER_H
#define __ADC_SEQUENCE_DRIVER_H

#include <stdint.h>

extern volatile int32_t adc_result[5];

void    adc_driver_init(void);
void    adc_start_conversion(void);
void    adc_print_results(void);

#endif /* __ADC_SEQUENCE_DRIVER_H */
