#include <stdio.h>
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/rmt_tx.h"
#include "led_strip.h"

#define GPIO_LED 48

led_strip_handle_t led_init(void)
{
    led_strip_handle_t led_strip;

    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_LED,
        .max_leds = 1,
    };

    led_strip_rmt_config_t strip_rmt_config = {
        .resolution_hz = 40 * 1e6,
        .flags.with_dma = 0,
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &strip_rmt_config, &led_strip));

    return led_strip;
}

void led_reverse(char led_state, int count, led_strip_handle_t led_strip)
{
    if(count <= 9)
    {
        if (led_state)
        {
            led_strip_set_pixel(led_strip, 0, 0, 0, 0);
            led_strip_refresh(led_strip);
            printf("LED OFF\n");
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        else
        {
            led_strip_set_pixel(led_strip, 0, 15, 9, 12);
            led_strip_refresh(led_strip);
            printf("LED ON\n");
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
    else
    {
        led_strip_clear(led_strip);
        led_strip_refresh(led_strip);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}