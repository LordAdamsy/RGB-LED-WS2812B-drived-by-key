#include "led_strip.h"

#ifndef __LED__
#define __LED__
led_strip_handle_t led_init(void);
void led_reverse(char led_state, int count, led_strip_handle_t led_strip);
#endif