#ifndef __SERVO_DRIVER_H
#define __SERVO_DRIVER_H

#include <stdint.h>


void servo_init(void);

void servo_enable(void);
void servo_disable(void);

void servo_set_duty_cycle(uint32_t duty, uint32_t channel);

#endif
