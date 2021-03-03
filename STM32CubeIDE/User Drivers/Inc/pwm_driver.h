#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H

#include <stdint.h>


void pwm_init(void);
void pwm_enable(void);
void pwm_disable(void);
void pwm_set_duty_cycle(uint32_t duty, uint32_t channel);
#endif
