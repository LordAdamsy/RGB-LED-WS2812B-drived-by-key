#include <stdio.h>
#include "led.h"
#include "key.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/gpio.h"
#include"esp_log.h"
#include "led_strip.h"

void app_main(void)
{
    char led_state = 0;
    int count = 0;
    led_strip_handle_t led_strip;
    led_strip = led_init();
    key_init();
    while(count <= 10)
    {
        if(ScanKey())
        {
            led_reverse(led_state, count, led_strip);
            led_state = !led_state;
            vTaskDelay(10 / portTICK_PERIOD_MS);
            count++;
        }
    }
}