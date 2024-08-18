#include<stdio.h>
#include"key.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/gpio.h"

#define GPIO_KEY 0

void key_init(void)
{
    gpio_config_t key_conf;
    key_conf.intr_type = GPIO_INTR_DISABLE;
    key_conf.mode = GPIO_MODE_INPUT;
    key_conf.pin_bit_mask = 1ULL << GPIO_KEY;
    key_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    key_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&key_conf);
}

unsigned char ScanKey(void)
{   
    unsigned char KeyVal = 0;
    if(gpio_get_level(GPIO_KEY) == 0)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        if(gpio_get_level(GPIO_KEY) == 0)
        {
            KeyVal = 1;
            while(!gpio_get_level(GPIO_KEY))
            {
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
    }
    return KeyVal;   
}