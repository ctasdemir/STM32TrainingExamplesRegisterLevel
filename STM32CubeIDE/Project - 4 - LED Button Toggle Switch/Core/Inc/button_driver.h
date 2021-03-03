#ifndef __BUTTON_DRIVER_H
#define __BUTTON_DRIVER_H

#include <stdint.h>


#define BUTTON_ON (1)
#define BUTTON_OFF (0)

void button_init(void);
int32_t button_get_state(void);






#endif
