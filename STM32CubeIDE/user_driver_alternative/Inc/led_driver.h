/**
 * @file    led_driver.h
 * @brief   LED Driver - Register-based
 *          LED2 on PA5 (Nucleo-F070RB).
 */
#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

void user_led_init(void);
void user_led_toggle(void);
void user_led_set(void);
void user_led_reset(void);

#endif
