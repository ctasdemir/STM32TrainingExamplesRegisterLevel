
#ifndef __BUTTON_DRIVER_H
#define __BUTTON_DRIVER_H
#include <stdint.h>

#define BUTTON_ON 0
#define BUTTON_OFF 1

void button_init(void);
uint32_t button_get_state(void);

#endif
