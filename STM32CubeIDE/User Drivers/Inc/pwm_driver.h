#ifndef __PWM_DRIVER_H
#define __PWM_DRIVER_H

#include <stdint.h>

typedef enum CHANNELS{
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
}Channels_e;

void pwm_init(void);
void pwm_enable(void);
void pwm_disable(void);
void pwm_set_duty_cycle(uint32_t duty, Channels_e channel);
#endif
