#ifndef __TIMER14_DRIVER_H
#define __TIMER14_DRIVER_H

#include <stdint.h>


void timer14_init(void);

void timer14_enable(void);
void timer14_disable(void);

void timer14_capture_set_period(uint32_t ms);

#endif
